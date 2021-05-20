# Logging basics
Tất cả những hoạt động từ kernel đến user đều được Linux ghi vào nhật ký. Từ đó cho phép người dùng quan sát tất cả các sự kiện diễn ra trên hệ thống.

## System logs
Linux có một danh mục riêng để chứa các log (bản ghi nhật ký) là `/var/log`. Thư mục này chứa tất cả log của hệ điều hành, dịch vụ (service), và các ứng dụng chạy trong hệ thống.

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/log1.png)

Một số các system log quan trọng nằm ở:
- `var/log/syslog` ghi lại hoạt động của toàn bộ hệ thống
  - `var/log/messages` đối với các hệ thống trên nền Red Hat như CentOS
- `/var/log/auth.log` ghi lại những sự kiện liên quan đến bảo mật hệ thống như login, hoạt động của root user
  - `/var/log/secure` đối với CentOS
- `/var/log/kern.log` ghi lại các sự kiện của kernel về lỗi, cảnh báo,... cần thiết cho việc khắc phục sự cố kernel

Các ứng dụng cũng có thể ghi log tại thư mục này, ví dụ như với NGINX server sẽ ghi log tại `/var/log/nginx`, hay với Apache server sẽ ghi tại `/var/log/apache2`

## Syslog
Syslog là một tiêu chuẩn dành cho việc tạo và truyền các file log. Có thể hiểu syslog theo những nghĩa sau:
- #### Dịch vụ syslog:
  - Nơi tiếp nhận và xư lý các bản tin syslog. Nó lắng nghe các sự kiện thông qua một socket được tạo ở `/dev/log`, các ứng dựng có thể ghi log từ nơi này. 
  - **Syslogd** là một daemon phổ biến dùng để quản lý và ghi log, tuy nhiên ở các distro Linux hiện hành, **syslogd** đã được thay thế bởi phiên bản đầy đủ hơn như **rsyslog** or **syslog-ng**
- #### Giao thức syslog:
  - Là giao thức truyền tải chỉ địch cách truyền log qua hệ thống mạng.
  - Đồng thời cũng là một định dạng dữ liệu để xác định cấu trúc bản tin.
- #### Bản tin syslog:
  - Là những log tuân thủ theo [định dạng bản tin syslog](https://datatracker.ietf.org/doc/html/rfc5424#section-6).
  - Nhờ đó mà header và nội dung trong log được tiêu chuẩn hóa giống nhau.

### Định dạng và các trường của syslog
Header tiêu chuẩn của syslog đi kèm với một số trường mặc định:
- `timestamp` là thời gian và ngày tháng năm mà bản tin được ghi
- `hostname` tên của host hoặc hệ thống đã gửi bản tin
- `app-name` tên của ứng dụng

Với định dạng mặc định sẽ dễ dàng dể quan sát và phân tích hơn, tuy nhiên vẫn có thể tùy chỉnh các trường xuất hiện theo mục đính của người dùng bằng **rsyslog**.

# Syslog
Syslog là giao thức dùng để xử lí các file log trong Linux. File log có thể ở trong chính máy đó hoặc di chuyển sang 1 máy khác.
Đặc điểm:
- Syslog có thể gửi qua UDP hoặc TCP.
- Các dữ liệu log được gửi dưới dạng cleartext.
- Syslog mặc định dùng cổng 514.

Syslog là 1 giao thức và được sử dụng bởi dịch vụ **Rsyslog**

### Rsylog
The **r**ocket-fast **sys**tem for **log** processing là một phần mềm mã nguồn mở sử dụng trên Linux dùng để chuyển tiếp các log message đến một địa chỉ trên mạng (log receiver, log server). Nó thực hiện giao thức syslog cơ bản, đặc biệt là sử dụng TCP cho việc truyền tải log từ client tới server. Hiện nay rsyslog là phần mềm được cài đặt sẵn trên hầu hết các distro Linux

- Ở những bản distro Linux hiện đại (như Ubuntu, CentOS hoặc RHEL), máy chủ syslog mặc định được sử dụng là rsyslog.
- Rsyslog là một sự phát triển của syslog, cung cấp các khả năng như các module có thể cấu hình, được liên kết với nhiều mục tiêu khác nhau (ví dụ chuyển tiếp nhật ký Apache đến một máy chủ từ xa).
- Rsyslog cũng cung cấp tính năng lọc riêng, cho phép người dùng tùy chỉnh định dạng của log.

### Ví dụ
Định dạng mặc định của syslog có tên là `RSYSLOG_TraditionalFileFormat`, người dùng có thể tự tùy chỉnh các trường xuất hiện như sau:

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/rsyslog2.png)

Các trường được tùy chỉnh bao gồm:
- `%pri%` cho thấy mức độ cần thiết hoặc nghiêm trọng của sự kiện
- `%HOSTNAME%` tên của host hoặc hệ thống đã gửi bản tin
- `%app-name%` tên của ứng dụng
- `%msg%` nội dung bản tin được gửi tới `syslog`

Sau khi cấu hình lại `/etc/rsyslog.conf` cần phải khởi động lại service: `sudo systemctl restart rsyslog.service`

Kết quả khi vào xem file `/var/log/syslog` sẽ đúng theo format mà người dùng đưa ra.

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/rsyslog1.png)

So với trước khi thay đổi định dạng:

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/rsyslog3.png)

