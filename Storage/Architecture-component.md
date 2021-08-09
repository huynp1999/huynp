## Mô hình kiến trúc Ceph
<img src="https://user-images.githubusercontent.com/83684068/126732638-4d549bb7-c5ad-4d02-93a2-36adf1ecead4.png" alt="drawing" width="400"/>

### 1. RADOS (Reliable Autonomic Distributed Object Store)
- Là nền tảng và là thành phần trung tâm của Ceph storage cluster. RADOS cung cấp tất cả các tính năng quan trọng giữa các node trong Ceph, bao gồm distributed storage, high availability, reliablity, migration, no single point of failure, self-healing, self-managing...
- Khi Ceph cluster nhận được yêu cầu write từ phía client, trước tiên thuật toán CRUSH tính toán và quyết định vị trí dữ liệu nên lưu trữ trong cluster. Thông tin này sau đó được truyền tới RADOS layer để xử lí tiếp. Dựa vào các ruleset của CRUSH, RADOS phân phối dữ liệu tới tất cả các node trong cluster dưới định dạng các object. Cuối cùng, các object này được lưu trong các OSD.
- RADOS đảm bảo dữ liệu luôn tin cậy. Tại cùng một thời điểm, RADOS mô phỏng (replicate) các object, tạo ra và lưu các bản sao của chúng trong các failure zone phân tán. RADOS cũng đảm bảo các object luôn trong trạng thái nhất quán. Nếu không sẽ thực hiện recover trên các bản sao object còn lại. Những hoạt động này đều được thực hiện tự động và trong suốt với người dùng.

### 2. OSD (Object Storage Device)
- Là nơi lưu trữ và truy xuất dữ liệu thực (actual data) dưới dạng các object trong các ổ đĩa vật lí trên mỗi node của cluster. Một Ceph cluster bao gồm nhiều OSD và mỗi OSD deamon được gắn với một ổ đĩa vật lí.
- Khi có hành động đọc ghi, client trước tiên cần yêu cầu một cluster map từ monitors, và về sau client sẽ trực tiếp tương tác với các OSD để thực hiện các tương tác mà không cần sự can thiệp của monitor. Điều này khiến qúa trình trao đổi dữ liệu diễn ra nhanh hơn, client có thế lưu trực tiếp tới OSD mà không cần bất kì lớp xử lí dữ liệu trung gian nào. 
- Như đã nói ở phần trên, tính năng replicate mỗi object trên các node trong cluster giúp luồng dữ liệu có tính sẵn sàng cao và khả năng chống lỗi. Mỗi object trong OSD có một bản primary copy và một số secondary copy được phân bố đều trên các OSD khác. Mỗi OSD vừa đóng vai trò là primary OSD của một số object này, vừa có thể là secondary OSD của một số object khác. Khi ổ cứng xảy ra lỗi, OSD daemon sẽ so sánh với các OSD khác để thực hiện hành động recovery. Trong thời gian này, secondary OSD giữ bản sao của object bị lỗi sẽ được đẩy lên làm primary, đồng thời các bản sao mới sẽ được tạo trong qúa trình recover.

### 3. MONs (Ceph monitors)
- Chịu trách nhiệm theo dõi trạng thái của toàn bộ cluster, bằng cách duy trì thông tin mỗi thành phần cluster map riêng biệt, bao gồm OSD, MON, PG, CRUSH và MDS map. Tất cả các node trong cluster gửi thông tin về cho monitor node khi có thay đổi trạng thái. Monitor node không có nhiệm vụ lưu trữ dữ liệu, đây là nhiệm vụ của OSD.
    - **Monitor map:** Lưu thông tin end-to-end của node monitor như Ceph cluster ID, monitor hostname, địa chỉ IP và port, thời điểm thay đổi cuối cùng. Check monitor map `# ceph mon dump`
    - **OSD map:** Lưu các thông tin chung như cluster ID, thời điểm OSD map được tạo và last-changed. Các thông tin của pool như pool name, pool ID, type, placement group. Nó cũng lưu thông tin của OSD như count, state, weight, last clean interval... Check OSD map: `# ceph osd dump`
    - **PG map:** Lưu PG version, time stamp, last OSD map epoch, full ratio và chi tiết của mỗi placement group như PG id, state của PG... Check PG map: `# ceph pg dump` 
    - **CRUSH map:** Lưu thông tin về các storage devices, failure domain (host, rack, row, room, device) và các quy tắc khi lưu trữ dữ liệu. Check CRUSH map: `# ceph osd crush dump`
    - **MDS map:** Lưu thông tin về MDS map epoch, map creation và modification time, data and metadata pool ID, cluster MDS count, MDS state. Check MDS map: `# ceph mds dump`
- Vai trò của monitor là cập nhật cluster map tới client cũng như các node trong cluster, chứ không phải lưu và phục vụ dữ liệu tới client. Client và các node trong cluster sẽ định kì kiểm tra tới monitor để lấy được cluster map gần nhất.  không lưu và phục vụ dữ liệu tới client
- Monitor là một lightweight daemon và yêu cầu nhiều tài nguyên. Các node monitor nên có không gian ổ đĩa đủ lớn để lưu cluster logs (OSD log, MDS log và monitor log). Một Ceph cluster điển hình thường có nhiều hơn một node monitor và số lượng node monitor nên là số lẻ để đạt được hiểu quả tốt nhất (minimum 1, recommend 3). Vì trong một quorum, hơn một nửa số lượng monitor node cần được đảm bảo sẵn sàng để tránh rơi vào trạng thái "split-brain". Một monitor node sẽ là leader, và các node còn lại sẽ đưa đưa lên làm leader nếu node ban đầu bị lỗi.
- Monitor daemon vẫn có thể chạy cùng trên OSD node và sẽ cần trang bị nhiều CPU, RAM và ổ cứng hơn để lưu monitor logs. Nhưng đối với các hệ thống lớn, nên sử dụng các node monitor chuyên dụng. Với các rack, switch và nguồn điện riêng biệt.

### 4. librados
- Là một thư viện cung cấp các API truy cập tới RADOS, các ngôn ngữ được API hỗ trợ là PHP, Ruby, Java, C và C++. Nó cung cấp một native interface tới Ceph storage cluster, RADOS và các services khác như RBD, RGW VÀ CephFS.

### 5. RBD (RADOS block device)
- Là thành phần cung cấp block storage, có khả năng mapped, formated và mounted như là một ổ đĩa tới server. RDB được trang bị các tính năng lưu trữ dành cho doanh nghiệp như thin provisioning và snapshot. Ceph RBD driver được tích hợp với Linux kenel và hỗ trợ QEMU/KVM, cho phép truy cập tới Cẹph block device một cách liền mạch.

![image](https://user-images.githubusercontent.com/83684068/126738607-97e40bb2-2c39-4ac8-a852-c26f254a4030.png)

- Ceph cũng được tích hợp chặt chẽ với các nền tảng đám mây như Openstack. Các service Cinder và Glance sử dụng Ceph như backend để lưu trữ virtual machine volume và OS images. Các image và volume này được hỗ trợ thin provisioned giúp giảm một lượng đáng kể không gian lưu trữ trong Openstack.

### 6. RGW (RADOS gateway)
- Là một object storage ínterface được xây dựng dựa trên librados. Ceph Object hỗ trợ 2 ínterface:
  - S3-compatible: cung cấp chức năng lưu trữ đối tượng với một interface tương thích với đa số RESTful API của Amazon S3.
  - Swift-compatible: cung cấp chức năng object storage với một interface tương thích với đa số Openstack Swift API.

![image](https://user-images.githubusercontent.com/83684068/126739026-024aff26-ab6e-4139-9b85-a64c248fdbb0.png)

- Cả S3 và Swift API chia sẻ phần chung bên trong Ceph Cluster, vì thế có thể ghi data từ 1 API và đọc data từ 1 API khác. Để tăng tốc xử lý, nó sử dụng memory để cache metadata. Bên cạnh S3 và Swift API, app có thể bỏ qua RADOS gateway mà sử dụng trực tiếp thông quan librados.

### 7. MDS (Ceph Metadata Server)
- Ceph MDS tập trung phục vụ Metadata, còn data được phục vụ bởi OSD. MDS là một yêu cầu riêng của Ceph Filesystem, và dành cho một số loại block storage; object storage không yêu cầu dịch vụ MDS. Hoạt động của MDS thông qua cache layer, vì thế hiệu suất đọc ghi sẽ bị giảm.
- MDS không lưu trữ local data, ít cần thiết trong 1 số trường hợp. Nếu tiến trình MDS lỗi, ta có thể chạy lại thông qua truy cập cluster. Tiến trình metadata server được cấu hình chủ động hoặc bị động. Node MDS chính sẽ trở thành active, phần còn lại sẽ chuyển sang chế độ passive. Khi primary MDS xảy ra lỗi, node tiếp theo sẽ được chuyển lên.

### 8. Ceph Filesystem
- CephFS cung cấp POSIX-compliant filesystem nằm trên RADOS. Nó sử dụng tiến trình MDS để quản trị metadata, tách biệt metadata khởi data, giảm phức tạp, nâng cao tính bảo đảm. CephFS thừa hưởng 1 số tính năng từ RADOS và cung cấp tính năng cân bằng động cho data.

![image](https://github.com/lacoski/khoa-luan/blob/master/Ceph/PIC/ceph-arch-4.png)

- libcephfs libraries nắm vai trò quan trọng, hỗ trợ thực thi client. Tương thích tốt với Linux kernel driver, vì thế client có thể sử dụng filesystem để mount thông qua mount cmd. Nó tương thích với SAMBA, hỗ trợ CIFS và SMB. CephFS mở rộng hỗ trợ file systems trong user space (FUSE) thông quan cephfuse modules. Nó cũng cho phép app tương tác trực tiếp, với RADOS cluster sẽ sử dụng libcephfs libraries.
