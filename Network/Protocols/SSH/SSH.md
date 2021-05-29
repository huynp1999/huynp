# SSH Secure Shell
Là giao thức điều khiển từ xa cho phép người dùng kiểm soát và chỉnh sửa Remote Server từ xa qua Internet.

Vượt trội hơn trình Telnet về tính bảo mật được đảm bảo trong suốt phiên giao tiếp
- Để làm được như vậy, SSH triển khai 1 số kỹ thuật mã hoá với dữ liệu tại từng thời điểm khác nhau của phiên làm việc như [mã hóa đối xứng, bất đối xứng](https://github.com/huynp1999/huynp/blob/master/Network/Protocols/HTTP/Encryption-algorithms.md) và hàng băm


Cú pháp: `ssh [user]@[host]`

## Tính chất
Các tính chất được SSH mang đến bao gồm:
- **Riêng tư (Privacy)**: dữ liệu được mã hóa
- **Toàn vẹn (Integrity)**: dữ liệu toàn vẹn qua kênh truyền, không bị thay đổi
- **Xác thưc (Authentication)**: xác thực nguồn gốc giữa bên gửi và bên nhận
- **Uỷ quyền (Authorization)**: ủy quyền truy cập thông qua các tài khoản
- **Chuyển tiếp, tạo đường hầm (Tunneling)**: 3 kiểu chuyển tiếp dữ liệu qua một kênh mã hoá
   + Port forwarding: cho phép chuyển lưu lượng truy cập từ 1 port lên SSH server
   + X forwarding
   + Agent forwarding

