# HTTP (HyperText Transfer Protocol)
Là giao thức truyền tải siêu văn bản, theo mô hình client server dành cho World Wide Web (www) để truyền tải dữ liệu dưới dạng văn bản, âm thanh, hình ảnh, video từ webserver tới web browser của người dùng và ngược lại.
Giao thức này sử dụng cổng 80 (port 80) là chủ yếu.
## Phương thức hoạt động
<img src="https://s.cystack.net/resource/home/content/15183058/http-hoat-dong-nhu-the-nao-1024x458.png" alt="drawing" width="700"/>

Khi request được gửi đến, server sẽ thực hiện một trong 3 hành động sau:
1. Server phân tích request nhận được, ánh xạ yêu cầu với file trong kho lữu trữ của server, và trả lại tập tin yêu cầu cho client.
2. Server phân tích request nhận được, ánh xạ yêu cầu vào một chương trình trên server, thực thi chương trình và trả lại kết quả của chương trình đó.
3. Request từ client không thể đáp ứng, server trả lại thông báo lỗi.

### HTTP Request
Là phương thức để chỉ ra hành động mong muốn được thực hiện trên tài nguyên đã xác định.
- #### Cấu trúc của một HTTP Request:
  - Request-line = Phương thức + URL–Request + Phiên bản HTTP.
  - Request Header: Các trường header cho phép client truyền thông tin bổ sung về yêu cầu về cả client và server.
  - Có thể không có các trường header

![Alt](https://images.viblo.asia/full/87ee0c1c-abac-4d08-973e-e8bae533cbf0.png)

- #### Một phương thức của HTTP Request
  - GET: sử dụng để lấy dữ liệu từ server
  - POST: đính kèm theo các file tải lên, thông tin khách hàng,... tới server
  - PUT: yêu cầu sửa đổi hoặc tạo dữ liệu trên server
  - DELETE: xóa bỏ tất cả các đại diện của tài nguyên được chỉ định

### HTTP Response
- #### Cấu trúc của một HTTP response:
  - Status-line = Phiên bản HTTP + Mã trạng thái + Trạng thái
  - Có thể không có các trường header

![Alt](https://images.viblo.asia/8414d386-f4e5-4b9c-aded-d3b379dc7c20.png)

- #### Mã trạng thái
  - Thông báo về kết quả khi nhận được yêu cầu và xử lí bên server cho client.
  - Các kiểu mã trạng thái:
    - 1xx: Thông tin (100 -> 101) 
      - 100 (Continue)
    - 2xx: Thành công (200 -> 206) 
      - 200 (OK), 201 (CREATED)
    - 3xx: Điều hướng web (300 -> 307)
      - `302, 301` Thông báo có sự thay đổi trong URL
      - `304` Không có thay đổi và có thể load từ cache 
    - 4xx: Lỗi phía Client (400 -> 417)
      - `403` Client không có quyền truy cập
      - `404` Server không tìm thấy địa chỉ và không thể nhận diện URL
    - 5xx: Lỗi phía Server (500 -> 505) 
      - `500` Thông báo lỗi chung, không chỉ ra cụ thể
      - `501` Server không nhận ra hoặc không thể thực thi yêu cầu


