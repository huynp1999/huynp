# Logging basics
Tất cả những hoạt động từ kernel đến user đều được Linux ghi vào nhật ký. Từ đó cho phép người dùng quan sát tất cả các sự kiện diễn ra trên hệ thống.

## System logs
Linux có một danh mục riêng để chứa các log (bản ghi nhật ký) là `/var/log`. Thư mục này chứa tất cả log của hệ điều hành, dịch vụ (service), và các ứng dụng chạy trong hệ thống.


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
- `priority` cho thấy mức độ cần thiết hoặc nghiêm trọng của sự kiện

Với định dạng mặc định sẽ dễ dàng dể quan sát và phân tích hơn, tuy nhiên vẫn có thể tùy chỉnh các trường xuất hiện theo mục đính của người dùng.
