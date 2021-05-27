# HTTPS (HyperText Transfer Protocol Secure)
<img src="https://s.cystack.net/resource/home/content/17163019/Giao-th%E1%BB%A9c-HTTPS-01-1024x483.png" alt="drawing" width="700"/>
Là phần mở rộng bảo mật của HTTP, có sử dụng thêm chứng chỉ bảo mật SSL/TLS để thiết lập kết nối an toàn. Đây cũng là khác biệt chính với HTTP nhằm gia tăng thêm tính an toàn cho việc truyền dữ liệu giữa client và server. Để có thể sử dụng HTTPS thì cả web browser và webserver đều phải có chứng chỉ SSL/TLS.
Giao thức HTTPS mặc định sử dụng port 433, các port khác (1024 trở lên) đều có thể sử dụng miễn là cả client và server đều được thống nhất.

## SSL/TLS
SSL/TLS hoạt động dựa trên [hệ mật mã khóa công khai](https://github.com/huynp1999/huynp/blob/master/Network/Protocols/HTTP/Encryption-algorithms.md) bằng public và private key, kết hợp với session key cho mỗi phiên kết nối.

![Alt](https://www.hostinger.vn/huong-dan/wp-content/uploads/sites/10/2018/12/thiet-lap-ket-noi-an-toan-voi-server.png)

Quá trình hoạt động:
- Client gửi yêu cầu thiết lập một phiên kết nối an toàn tới server.
- Server trả về chứng chỉ số và public key của server, chứng chỉ này phát sinh bởi server và trên server giữ private key
- Client sau khi nhận chứng chỉ sẽ tạo ra yêu cầu tới CA (Certificate Authority) để chứng thực chứng chỉ.
  - **Certificate Authority** là các tổ chức uy tín cung cấp chứng chỉ số và public key, được thành lập đảm bảo được danh tính cụ thể của đối tượng được cung cấp chứng chỉ cho người dùng.
  - Có thể xem CA bằng cách ấn vào nút khóa trên thanh URL
- Client và server trao đổi 1 số thông tin để kiểm tra các key.
- Client và Server bắt đầu trao đổi dữ liệu được mã hóa.

SSL/TLS là tập hợp các thủ tục đã được chuẩn hóa để thực hiện các nhiệm vụ bảo mật sau:
- Xác thực server: client sử dụng các kĩ thuật mã hóa công khai để xác thực chứng chỉ số và public ID của server có giá trị được cấp phát bởi CA.
- Xác thực client: Cho phép phía server xác thực được client muốn kết nối, kiểm tra xem chứng chỉ số và public ID của client có được cấp phát bởi CA.
- Mã hóa kết nối: Tất cả các trao đổi giữa client và server được mã hóa trên đường truyền.

