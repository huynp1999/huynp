# Ceph Storage
Ceph là phần mềm mã nguồn mở miễn phí, cung cấp giải pháp lưu trữ dữ liệu phân tán, ổn định, tin cậy và dễ dàng mở rộng trong tương lai.
Dữ liệu được hỗ trợ lưu trữ ở dạng đối tương (Object), khối (Block) hay tệp (File) trong cùng một nền tảng duy nhất.
Nền tảng storage này được xây dựng bằng phần mềm (software defined) và triển khai trên các máy chủ phổ thông.

CEPH được sử dụng để thay thế việc lưu trữ dữ liệu trên các máy chủ, sao lưu dữ liệu, tạo ra một khu vực lưu trữan toàn, cho phép triển khai các dịch vụ HA (high availability).

## Mô hình kiến trúc Ceph
<img src="https://user-images.githubusercontent.com/83684068/126732638-4d549bb7-c5ad-4d02-93a2-36adf1ecead4.png" alt="drawing" width="400"/>

**1. RADOS (Reliable Autonomic Distributed Object Store):**
- Là nền tảng và là thành phần trung tâm của Ceph storage cluster. RADOS cung cấp tất cả các tính năng quan trọng giữa các node trong Ceph, bao gồm distributed storage, high availability, reliablity, migration, no single point of failure, self-healing, self-managing...
- Khi Ceph cluster nhận được yêu cầu write từ phía client, trước tiên thuật toán CRUSH tính toán và quyết định vị trí dữ liệu nên lưu trữ trong cluster. Thông tin này sau đó được truyền tới RADOS layer để xử lí tiếp. Dựa vào các ruleset của CRUSH, RADOS phân phối dữ liệu tới tất cả các node trong cluster dưới định dạng các object. Cuối cùng, các object này được lưu trong các OSD.
- RADOS đảm bảo dữ liệu luôn tin cậy. Tại cùng một thời điểm, RADOS mô phỏng (replicate) các object, tạo ra và lưu các bản sao của chúng trong các failure zone phân tán. RADOS cũng đảm bảo các object luôn trong trạng thái nhất quán. Nếu không sẽ thực hiện recover trên các bản sao object còn lại. Những Hoạt động này đều được thực hiện tự động và trong suốt với người dùng.

**2. OSD (Object Storage Device):**
- Là nơi lưu trữ và truy xuất dữ liệu thực (actual data) trong các ổ đĩa vật lí trên mỗi node của cluster. Một Ceph cluster bao gồm nhiều OSD và mỗi OSD deamon được gắn với một ổ đĩa vật lí.
- Gỉa sử, khi có hành động read hoặc write, client trước tiên cần yêu cầu một cluster map từ monitors, và về sau client sẽ trực tiếp tương tác với các OSD để thực hiện các tương tác mà không cần sự can thiệp của monitor. Điều này khiến qúa trình trao đổi dữ liệu diễn ra nhanh hơn, client có thế lưu trực tiếp tới OSD mà không cần bất kì lớp xử lí dữ liệu trung gian nào. 
- Như đã nói ở phần trên, tính ăng replicate mỗi object trên các node trong cluster giúp chúng luồng dữ liệu có tính sẵn sàng cao và khả năng chống lỗi. Mỗi object trong OSD có một bản primary copy và một số secondary copy được phân bố đều trên các OSD khác. Mỗi OSD vừa đóng vai trò là primary OSD của một số object này, vừa có thể là secondary OSD của một số object khác. Bình thường các secondary OSD nằm dưới sự điều khiển của primary OSD, tuy nhiên chúng vẫn có khả năng trở thành primary OSD.

**3. MONs (Ceph monitors):** theo dõi trạng thái của toàn bộ cluster bằng cách duy trì thông tin mỗi thành phần cluster map riêng biệ, bao gồm OSD, MON, PG, CRUSH và MDS map. Tất cả các node trong cluster gửi thông tin về cho monitor node khi có thay đổi trạng thái. Monitor node không có nhiệm vụ lưu trữ dữ liệu, đây là nhiệm vụ của OSD.

**4. librados:** là một thư viện cung cấp các API truy cập tới RADOS, các ngôn ngữ được API hỗ trợ là PHP, Ruby, Java, C và C++. Nó cung cấp một native interface tới Ceph storage cluster, RADOS và các services khác như RBD, RGW VÀ CephFS.

**5. RBD (RADOS block device):** cung cấp giai pháp lưu trữ block storage, có khả năng mapped, formated và mounted như là một ổ đĩa tới server. RDB được trang bị các tính năng lưu trữ dành cho doanh nghiệp như thin provisioning và snapshot. RBD cũng tích hợp với KVM, mang lại việc lưu trữ ảo hóa không giới hạn tới KVM chạy trên Ceph client của người dùng.

**6. RGW (RADOS gateway)** hay còn gọi là Ceph Object Gateway, cung cấp tiêu chuẩn RESTful API, tương thích với Amazon S3 (Simple Storage Service) và Openstack Object Storage API (Swift). RGW cũng hỗ trợ dịch vụ xác thực Openstack Keystone.
