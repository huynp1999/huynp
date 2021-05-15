# Boot process
![Alt](https://user-images.githubusercontent.com/83684068/117920279-cf185f00-b318-11eb-9927-1f2c8338d2cc.png)
1. System Startup
Đây là bước đầu tiên của quá trình khởi động , ở bước này BIOS thực hiện kiểm tra tính sẵn sàng phần cứng (POST) nhằm kiểm tra thông số và trạng thái của các phần cứng máy tính như bộ nhớ, CPU,... Nếu quá trình POST kết thúc thành công, BIOS sẽ tìm kiếm và boot 1 hệ điều hành được chứa trong các thiết bị lưu trữ như HHD, SSD, CD/DVD, USB.
2. MBR Loading
MBR (Master Boot Record) được lưu trữ tại sector đầu tiên của 1 thiết bị lưu trữ dữ liệu, ví dụ như `/dev/hda` hoặc `/dev/sda`. MBR rất nhỏ nhưng chứ đầy đủ các thông tin, vị trí về boot loader (với Linux là GRUB loader), các thông tin về partition và sửa lỗi (magic number).
3. GRUB Loader
Sau khi xác định vị trí sẽ thực hiện load Boot Loader vào bộ nhớ và đọc thông tin cấu hình sau đó hiển thị **GRUB boot menu** để user lựa chọn. Nếu user không chọn OS thì sau khoảng thời gian được định sẵn , GRUB sẽ load default kernel vào memory để khởi động .
4. Kernel
Kernel của hệ điều hành sẽ được nạp vào trong RAM. Khi kernel hoạt động thì việc đầu tiên sẽ là thực thi quá trình **INIT** .
5. Run levels (INIT)
Là tiến trình đầu tiên khi khởi động một hệ điều hành với PID 1 - có tên chung là init. 

Gồm có 7 level vận hành tiêu chuẩn trong hệ thống linux:

0. Halt: tắt máy
1. Single user mode: chỉ duy nhất một user được phép kết nối hệ thống
2. Multi-user, without NFS: đa người dùng, không hỗ trợ networking
3. Full multi-user mode: đa người dùng, hỗ trợ networking
4. Unused
5. X11: sử dụng GUI desktop
6. Reboot: khởi động lại hệ thống

## Systemd
Từng có những phần mềm init phổ biến như SysV, Upstart nhưng gần đây đã thay thế bằng systemd với tốc độ vận hành cao, chức năng đa dạng hơn nhưng vẫn có các target tương tự:

1. poweroff.target
2. rescue.target
3. multi-user.target
4. unused
5. graphic.target
6. reboot.target

Kiểm tra default target (được kích hoạt khi boot)
```
$ systemctl get-default 
graphical.target
```

Set default:

`systemctl set-default multi-user.target`

Chuyển đổi run level khi hệ thống đang hoạt động:

`systemctl isolate graphical.target`

Ngoài ra systemd còn có thể thao tác với các dịch vụ:

`systemctl enable named.service`
