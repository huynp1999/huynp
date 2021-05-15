# Systemd
Là một công cụ quản lý hệ thống của Linux và hiện là hệ thống khởi tạo mặc định trên hầu hết các distro Linux
- Chữ "d" trong "systemd" đại diện cho "daemon", chính là các tiến trình chạy ngầm (background process) trong hệ thống Linux.

Không chỉ quản lý các tiến trình ngầm, systemd là tổ hợp của một nhóm các chương trình đặc biệt dùng quản lý, vận hành và theo dõi các tiến trình khác hoạt động.

Một trong các chức năng quan trọng của systemd là khởi tạo hệ thống. 
Systemd cung cấp một chương trình đặc biệt `/sbin/init` tương đương với tiến trình đầu tiên được khởi động khi boot (PID = 1).
Cụ thể hơn, `/sbin/init` giữ vai trò kích hoạt các file cấu hình (ví dụ `/boot`) cần thiết cho hệ thống để hoàn tất công đoạn boot.

## Các tiện ích 
Là một công cụ quản lý hệ thống, systemd cung cấp những tiện ích:
- `systemctl`  quản lý trạng thái của các dịch vụ hệ thống ( bắt đầu, kết thúc, khởi tạo hoặc kiểm tra trạng thái)
- `journald`  quản lý nhật ký hoạt động của hệ thống (ghi log)
- `logind`  quản lý và theo dõi việc đăng nhập/đăng xuất của user
- `networkd`  quản lý các kết nối mạng thông qua các cấu hình mạng
- `timedated`   quản lý thời gian của thống hoặc mạng
- `udev`   quản lý các thiết bị và firmware

## Unit file
Tất cả các tiến trình được quản lý bởi systemd đều đượcình thực thi dưới dạng "daemon" hay dưới nền ,và được cấu hình bằng một file configuration gọi là **unit file** .
12 loại **unit file**:
- `service` các file quản lý hoạt động của 1 số chương trình .
- `socket` quản lý các kết nối
- `device` quản lý thiết bị
- `mount` gắn thiết bị
- `automount` tự động gắn thiết bị
- `swap` vùng không gian bộ nhớ trên đĩa cứng
- `target` quản lý tạo liên kết
- `path` quản lý các đường dẫn
- `timer` dùng cho cronjob để lập lịch
- `snapshot`  sao lưu, backup
- `slice`  dùng cho quản lý tiến trình
- `scope`  quy định không gian hoạt động

Trong đó `service` là loại thường được quan tâm nhiều nhất. Các service được cấu hình qua các file như `.service` và được quản lý qua tiện ích `systemctl`

Xem các service đã kích hoạt trong hệ thống: `systemctl -t service`
- `-t` dùng để list các unit file theo từng loại, ví dụ như service, socket,...

Các option:
- `start`  bật service
- `stop`  tắt service
- `restart`  khởi động lại service
- `reload`  load lại file cấu hình (chỉ có 1 số service được hỗ trợ như Apache,NGINX,...)
- `enable`  service được khởi động cùng hệ thống
- `disable`  service không được khởi động cùng hệ thống

(Xem thêm ví dụ về cách tạo một service tại [đây](https://github.com/huynp1999/huynp/blob/master/Linux/Software-management/Bash-startup-script.md))
## Các công cụ tương tự Systemd
Systemd mới chỉ xuất hiện từ `30-3-2010` , trước đó có 2 hệ thống khác đã từng được sử dụng :
- **Upstart**  hệ thống init phát triển bởi **Canonical** và được sử dụng trong Ubuntu Linux giai đọan đầu
- **SysV**  hệ thống init cổ điển của **Unix BSD SystemV** , được viết bằng shell script và đã quá lâu đời
