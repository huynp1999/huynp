# SMTP (Simple Mail Transfer Protocol)
Là giao thức có nhiệm vụ chính là gửi mail, việc nhận mail hay truy xuất dữ liệu mail server sẽ được giao thức IMAP hay POP3 đảm nhiệm. SMTP Server là một máy chủ cho phép gửi email với số lượng lớn, tốc độ nhanh mà không bị giới hạn như Gmail hoặc mail đi kèm hosting.
- Hoạt động qua port 25 (TCP)
- Đối với SMPTS thì mặc định là port 465/587 dành cho TLS/SSL

## Mô hình hoạt động
![Alt](https://www.sparkpost.com/wp-content/uploads/2018/05/smtp-ports-2.png)

Sau khi phiên kết nối giữa người gửi và người nhận đã được thiết lập:
1. Trước tiên, thông báo được gửi đến một SMTP Server chỉ định, dựa vào tên miền của địa chỉ e-mail nhận (ví dụ, ‘tenemail.com’)
2. SMTP Server bắt đầu trao đổi liên lạc với một DNS Server để lấy bản ghi MX, từ đó ánh xạ ra Mail server của tên miền (ví dụ ‘mail.tenemail.com’)
3. Cuối cùng SMTP Server nguồn sẽ trao đổi thông tin trực tiếp với Mail Server đích thông qua cổng 25 của TCP
4. Nếu tên người dùng của địa chỉ e-mail nhận trùng khớp với dữ liệu của server đích, email sẽ được cho vào hàng đợi và chờ người nhận.
5. Nếu không thể liên lạc và trao đổi thông tin với server đích, giao thức SMTP cũng cung cấp cơ chế chuyển tiếp qua các mail server trung gian cho tới khi đến đích hoặc hết hạn.
