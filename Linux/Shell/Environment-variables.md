# Biến môi trường
Biến môi trường là các đại lượng có các giá trị cụ thể. Một biến môi trường được cung cấp các giá trị đặt trước từ hệ thống và các biến khác được đặt trực tiếp bởi người dùng.

Biến môi trường là một chuỗi ký tự chứa thông tin được sử dụng bởi một hoặc nhiều ứng dụng.

## Hiển thị
Xem các biến môi hiện được thiết lập: `printenv`

Hiện thị giá trị của một biến cụ thế, ví dụ như `$HOME` hay `~`:
```
echo $HOME
/home/huynp
```

## Gán biến
Gán biến tạm thời, reboot sẽ mất: 
```
HUY=value123
echo $HUY
value123
```

Để đảm bảo các biến môi trường này tồn tại vĩnh viễn thì cần phải đặt vào file cấu hình phù hợp.
- “/etc/environment” cho các biến trên toàn hệ thống
- “/etc/profile” dành cho thiết lập các biến shell.
- “~/.bashrc” dành cho mục đích các cá nhân
