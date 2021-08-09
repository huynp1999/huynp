## ceph-mon
Ceph monitor chịu trách nhiệm giám sát tình trạng của toàn hệ thống.
Nó hoạt động như các daemon duy trì sự kết nối trong cluster bằng cách chứa các thông tin cơ bản về cluster, tình trạng các node lưu trữ và thông tin cấu hình cluster.
Ceph-mon thực hiện điều này bằng cách duy trì các bản sao của cluster map. Các cluster map này bao gồm monitor, OSD, PG, CRUSH và MDS map.

Thông qua việc truy xuất cluster map của một ceph-mon, client có thể xác định vị trí của tất cả các ceph-mon và ceph-osd còn lại.
Việc kết nối với ceph-mon cũng là cần thiết để client có thể đọc hoặc ghi vào ceph-osd.Từ các bản sao hiện tại của cluster map và thuật toán CRUSH, ứng dụng client có thể tính toán vị trí cho bất kỳ object nào và giao tiếp trực tiếp với ceph-osd đó.
Đây là một tính năng quan trọng liên quan tới hiệu suất và khả năng mở rộng cao của Ceph.

Ngoài ra, ceph-mon cũng cung cấp các dịch vụ xác thực và ghi log.
Ceph-mon sẽ ghi tất cả các thay đổi vào một bản PAXOS duy nhất và PAXOS sẽ ghi các thay đổi vào kho key-value đảm bảo tính nhất quán tốt nhất.
Ceph-mon tận dụng snapshot và trình vòng lặp để thực hiện đồng bộ hóa trên toàn kho lưu trữ.

<img src="https://user-images.githubusercontent.com/83684068/128659461-df3007a9-2fb3-45ad-9548-e24a5c827135.png" alt="drawing" width="600"/>

## Cluster map
- **Monitor map**: map này lưu giữ thông tin về các node monitor, gồm CEPH Cluster ID, monitor hostname, địa chỉ IP và số port. Nó cũng giữ epoch (phiên bản map tại một thời điểm) hiện tại để tạo map và thông tin về lần thay đổi map cuối cùng. Kiểm tra monitor map:

      ceph mon dump

- **OSD map**: map này lưu giữ các trường như cluster ID, epoch cho việc tạo map OSD và lần thay đổi cuối., và thông tin liên quan đến pool như tên, ID, loại, mức nhân bản và PG. Nó cũng lưu các thông tin OSD như tình trạng, trọng số, thông tin host OSD. Kiểm tra OSD map:

      ceph osd dump

- **PG map**: map này lưu giữ các phiên bản của PG (thành phần quản lý các object trong ceph), timestamp, bản OSD map cuối cùng, tỉ lệ đầy và gần đầy dung lượng. Nó cũng lưu các ID của PG, object count, tình trạng hoạt động và srub (hoạt động kiểm tra tính nhất quán của dữ liệu lưu trữ). Kiểm tra PG map:

      ceph pg dump

- **CRUSH map**: map này lưu các thông tin của các thiết bị lưu trữ trong Cluster, các rule cho tưng vùng lưu trữ. Kiểm tra CRUSH map bằng lệnh:

      ceph osd crush dump

- **MDS map**: lưu thông tin về thời gian tạo và chỉnh sửa, dữ liệu và metadata pool ID, cluster MDS count, tình trạng hoạt động của MDS, epoch của MDS map hiện tại. Kiểm tra MDS map:

      ceph mds dump

## Vai trò
Vai trò của monitor là cập nhật cluster map tới client cũng như các node trong cluster, chứ không phải lưu và phục vụ dữ liệu tới client.
Client và các node trong cluster sẽ định kì kiểm tra tới monitor để lấy được cluster map gần nhất.

Monitor là một lightweight daemon không yêu cầu nhiều tài nguyên tính toán. Các node monitor nên có không gian ổ đĩa đủ lớn để lưu cluster logs (OSD log, MDS log và monitor log). Một Ceph cluster điển hình thường có nhiều hơn một node monitor và số lượng node monitor nên là số lẻ để đạt được hiểu quả tốt nhất (minimum 1, recommend 3). Vì trong một quorum, hơn một nửa số lượng monitor node cần được đảm bảo sẵn sàng để tránh rơi vào trạng thái "split-brain". Một monitor node sẽ là leader, và các node còn lại sẽ đưa đưa lên làm leader nếu node ban đầu bị lỗi.

Monitor daemon vẫn có thể chạy cùng trên OSD node và sẽ cần trang bị nhiều CPU, RAM và ổ cứng hơn để lưu monitor logs. Nhưng đối với các hệ thống lớn, nên sử dụng các node monitor chuyên dụng. Với các rack, switch và nguồn điện riêng biệt.
