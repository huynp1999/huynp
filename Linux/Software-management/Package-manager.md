# Quản lý gói
Dpkg nên được xem như một công cụ hệ thống (phần lõi), còn apt như một công cụ gần gũi hơn với người dùng. Mỗi công cụ đều có tính đặc thù riêng và làm việc cùng nhau tùy theo những các nhiệm vụ cụ thể. 

## dpkg

Là một phần mềm quản lý gói của Debian, Ubuntu và nhiều distro Linux khác. Được dùng để cài đặt và quản lý các gói riêng lẻ.

Các option:
- `-i` cài đặt hoặc update gói (.deb)
- `-r` gỡ cài đặt gói, giữ file cấu hình
- `-P` gỡ cài đặt gói, xóa file cấu hình
- `-l` list những gói đã được cài đặt

Cài đặt apache:

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/dpks1.png)
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/dpkg2.png)

## apt
Là một tiện ích dành cho cài đặt, cập nhật, xóa bỏ  và quản lý các gói cho Ubuntu, Debian và nhiều distro Linux khác.

Cú pháp: `sudo apt [option] [package]`

Các option:
- `update` cập nhật các thông tin mới nhất của các gói về máy
- `upgrade` nâng cấp toàn bộ các gói
- `install` cài đặt
- `remove` gỡ cài đặt, giữ file cấu hình
- `purge` gỡ cài đặt, xóa file cấu hình
- `list` list những gói được cài đặt và có thể nâng cấp
- `search` tìm gói xem có sẵn để cài đặt không
- `show` đưa ra thông tin về gói như kích thước, nguồn cài đặt,...

Cài đặt nginx:

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/apt1.png)
