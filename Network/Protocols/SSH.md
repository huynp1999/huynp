# SSH Secure Shell
Là giao thức điều khiển từ xa cho phép người dùng kiểm soát và chỉnh sửa Remote Server từ xa qua Internet.

Vượt trội hơn trình Telnet về tính bảo mật được đảm bảo trong suốt phiên giao tiếp
- Để làm được như vậy, SSH triển khai 1 số kỹ thuật mã hoá với dữ liệu tại từng thời điểm khác nhau của phiên làm việc như [mã hóa đối xứng, bất đối xứng](https://github.com/huynp1999/huynp/blob/master/Network/Protocols/HTTP/Encryption-algorithms.md) và hàng băm

## Đặc điểm
Các tính chất được SSH cung cấp:
- **Riêng tư (Privacy)**: dữ liệu được mã hóa
- **Toàn vẹn (Integrity)**: dữ liệu toàn vẹn qua kênh truyền, không bị thay đổi
- **Xác thưc (Authentication)**: xác thực nguồn gốc giữa bên gửi và bên nhận
- **Uỷ quyền (Authorization)**: ủy quyền truy cập thông qua các tài khoản
- **Chuyển tiếp, tạo đường hầm (Tunneling)**: 3 kiểu chuyển tiếp dữ liệu qua một kênh mã hoá
   + Port forwarding: cho phép chuyển lưu lượng truy cập từ 1 port lên SSH server
   + X forwarding
   + Agent forwarding

## Cơ chế hoạt động
Giao thức SSH hoạt động theo mô hình client-server để xác thực (authenticate) và mã hoá (encrypt data).

Một session của SSH được thành lập qua 2 bước:
1. Thỏa thuận và thiết lập phiên mã hoã để bảo vệ thông tin sẽ được truyền
- Tại đây, 2 bên thương lượng một session key sử dụng thuật toán symmetrical encryption (AES)
- Session key này sẽ được vận chuyển bảo mật nhờ mã hoá bằng public key của Server được gửi đi

![image](https://user-images.githubusercontent.com/83684068/120099907-38e19700-c168-11eb-8533-0e2927e6f2a6.png)

2. Xác thực tài khoản người dùng truy cập
- Ở giai đoạn này liên quan đến việc xác nhận và uỷ quyền truy cập cho người dùng.
- Hai phương pháp chính để xác thực là password hoặc key pair
   - Password: mật khẩu sẽ được mã hoá và gửi lên server, tương đối khó bị đánh cắp nhưng yêu cầu độ phức tạp cao
   - Key pair: server sẽ nhận một ID đặc trưng từ client và dựa vào đây để xác thực bằng public key và MD5 hash

![image](https://user-images.githubusercontent.com/83684068/120099881-1485ba80-c168-11eb-9ff9-2f9bdd34b751.png)

## Cấu hình
Các thông tin cấu hình SSH hệ thống được lưu trữ tại `/etc/ssh/`, còn các thông tin cấu hình của riêng từng user thì tại `~/.ssh/`

Một số file cấu hình đáng quan tâm tại `~/.ssh/`:
- `~/.ssh/config` chứa thông tin về remote host như hostname, login name, thiết lập nén, tuỳ chỉnh port,...
- `~/.ssh/id_rsa` khoá RSA private dùng để xác thực
- `~/.ssh/id_rsa.pub` khoá RSA public dùng để gửi cho remote server

Còn trong `/etc/ssh` chứa file cấu hình `/etc/ssh/sshd_config`, dành cho hệ thống SSH. Trong này gồm nhiều các trường tuỳ chỉnh cho phiên kết nối SSH:
   - `PermitRootLogin [no/yes/with-out password]` không, hoặc cho phép truy cập SSH vào user root
   - `PasswordAuthentication [no/yes]` bật tắt tính năng xác thực mật khẩu
   - `Port 4444` thay đổi port mà sshd chạy
   - `AllowUsers [user1] [user2]` uỷ quyền truy cập tuỳ theo user, theo group sẽ là `AllowGroups`

Lưu ý: mỗi khi tuỳ chỉnh các trường này cần phải `service ssh restart`.

### Command

Cú pháp: `ssh [option] [user]@[host] [command]`
- `-p` port
- `-l` login name
   - `ssh –p 22 –l huynp@192.168.50.9`

Tạo key `ssh-keygen`
- `-t rsa` tạo public và private key theo thuật toán RSA 
- `-p` đổi passphrase

Copy keypair đã được tạo lên server

    ssh-copy-id  -i [file_name]  username@ip_address
    
![image](https://user-images.githubusercontent.com/83684068/120129446-2f027700-c1ee-11eb-8c51-e7b211a82c0a.png)
    
### Tiện ích kèm theo
Hai câu lệnh `scp` và `rsync` thường được dùng khi làm việc giữa local và remote server. Cả hai đều có chức năng copy và thay thế, nhưng `rsync` sử dụng thêm một số thuật toán phụ, nhằm tối ưu quy trình hoạt động
- Ví dụ như `rsync` sẽ bỏ qua những file trùng, thay vì copy đè. Như vậy chỉ những file khác biệt mới đc truyền, giảm lưu lượng cho đường truyền dẫn
- `rsync` cũng có nhiều option hơn ví dụ như lên lịch trình (tương tự `cron`), tiếp tục phiên bị ngắt quãng (option -p)
- Xem thêm các option tại [đây](https://github.com/huynp1999/huynp/blob/master/Linux/Utility/Rsync.md)

![image](https://user-images.githubusercontent.com/83684068/120129467-39bd0c00-c1ee-11eb-9439-782ff53d0cc8.png)

