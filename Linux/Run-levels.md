# Run levels
Khi máy tính khởi động trải qua nhiều bước, kernel sẽ chạy chương trình đầu tiên với PID 1 - có tên chung là init. 

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
