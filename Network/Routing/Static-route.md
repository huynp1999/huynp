# Routing
Routing là quá trình chọn lựa các đường đi trên một mạng máy tính để gửi dữ liệu qua đó,thông qua các nút trung gian là các bộ định tuyến router.
- Trong đó khi một router nhận gói tin, sẽ gỡ bỏ phần header lớp 2 để tìm địa chỉ đích thuộc lớp 3 thì Router sẽ gỡ bỏ phần header lớp 2 để tìm địa chỉ đích thuộc lớp 3, từ đó rà xoát trong Routing Table cho mạng chứa địa chỉ đích.
- Bảng định tuyến (Routing Table) là bảng chứa tất cả những đường đi tốt nhất đến một địa chỉ đích nào đó tính từ router.
- Khi cần chuyển tiếp một gói tin, router sẽ xem địa chỉ đích của gói tin, sau đó tra bảng định tuyến và chuyển gói tin đi theo một giao thức định tuyến (Routing Protocol) được cấu trình trước.

Bảng định tuyến của mỗi giao thức định tuyến là khác nhau, nhưng vẫn có những thông tin chung như:
- Địa chỉ đích và subnetmask của mạng, mạng con hoặc hệ thống.
- Địa chỉ IP của router chặng kế tiếp phải đến (next hop).
- Khoảng cách đến đích (ví dụ: số lượng chặng để đến đích).
- Thời gian (tính theo giây) từ khi Router cập nhật lần cuối.

### Phân loại giao thức định tuyến
Giao thức định tuyến là ngôn ngữ giao tiếp giữa các router. Một giao thức định tuyến cho phép các router chia sẻ thông tin về các network, rồi sử dụng các thông tin này để xây dựng và duy trì bảng định tuyến.

![Alt](https://ccna88.files.wordpress.com/2018/06/bai-5-hinh1.jpg)

Định tuyến được phân chia thành 2 loại cơ bản:
- Định tuyến tĩnh: Việc xây dựng bảng định tuyến được thực hiện bằng tay bởi người quản trị.
- Định tuyến động: Việc xây dựng, duy trì và cập nhật trạng thái của bảng định tuyến được thực hiện tự động bởi router.

Các loại định tuyến này được xây được trên 2 thuật toán để chọn đường đi:
- Distance vector: quan tâm đến khoảng cách và chọn đường đi ngắn nhất 
- Link State: quan tâm đến chất lượng và chọn đường đi tốt nhất

### Định tuyến tĩnh
- #### **Ưu điểm:**
  - Cấu hình dễ dàng và nhanh chóng
  - Hỗ trợ ở tất cả các thiết bị định tuyến và router
  - Ít hao tốn tài nguyên mạng và CPU xử lý trên router
  - Thường sử dụng ở các hệ thống mạng doanh nghiệp nhỏ, ít có sự thay đổi về cấu trúc, người quản trị toàn quyền kiểm soát điều khiển bảng định tuyến và có thể giảm bớt băng thông trong hệ thống.

- #### **Nhược điểm:**
  - Độ phức tạp tăng lên khi kích thước hệ thống mạng tăng
  - Không thích hợp với những hệ thống mạng lớn vì không thể thích ứng các thay đổi trong hệ thống mạng
  - Khả năng cập nhật đường đi bị hạn chế, nguy cơ tràn băng thông rất cao.

#### Cáu hình định tuyến tĩnh
Cú pháp: `ip route [destination_subnet] [subnetmask] [IP_next_hop|output_int] [AD]`

Trong đó:
- destination_subnet: địa chỉ IP mạng đích
- subnetmask: subnetmask của mạng đích
- IP_next_hop: địa chỉ IP của trạm kế tiếp trên đường đi.
- output_interface: cổng ra trên router.
- AD: chỉ số về độ ưu tiên của đường đi, thường dùng cho backup
