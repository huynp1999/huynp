# Directory tree
Filesystem là cách mà hệ thống lưu trữ và khai thác tài nguyên, cho phép người dùng truy cập dễ dàng và an toàn khi cần thiết.
Pseudo filesystem là một cấu trúc được tạo bởi các file ảo, không có thật (pseudo). Cấu trúc file này đại diện cho các tài nguyên thật và thuộc tính của chúng. Khi tổ chức phần cứng theo cách này, làm cho việc tương tác với phần cứng trông giống như một phần mềm.

Cấu trúc này được sắp xếp theo cây thư mục, với thư mục root nằm ở trên cùng (/).
![Alt](https://blogd.net/linux/tong-quan-ve-filesystem-tren-linux/img/minh-hoa-cho-filesystem.png)

## /
Cung cấp mount point cho các file system khác.
## /dev
Thư mục /dev chứa các file đại diện cho các thiết bị ví dụ như:
- /dev/sda là ổ cứng
- /dev/mouse là chuột
## /sys
Thư mục /sys chứa file sysfs là nơi cung cấp thông tin về các kernel module, thiết bị phần cứng cũng như giao tiếp với driver của các thiết bi.

Một số thư mục con gồm:
- /sys/devices/: đại diện cho cây phân cấp các thiết bị trong kernel.
- /sys/block/: chứa một liên kết tượng trưng cho mỗi thiết bị được kết nối vào hệ thống, tương ứng với /sys/devices/
- /sys/class/: thư mục con này chứ một lớp các thư mục con khác dành cho các thiết bị đã được đăng ký với hệ thống. Ví dụ /sys/class/printer chứa liên kết tới máy in.

## /bin
Thư mục /bin chứa các chương trình thực thi, hay còn gọi là các binaries (nhị phân). Chúng là chương trình hệ thống chủ yếu, ví dụ như `ls` là chương trình nằm tại thư mục này.
## /sbin
Thư mục /sbin chứa các file nhị phân hệ thống. Hầu hết các file ở đây dùng để quản trị hệ thống. (superuser-bin).
## /etc
Thư mục /etc chứa nhiều file thông tin cấu hình Linux, ví dụ như `passwd` nằm trong thư mục này, cũng như fstab và danh sách các file system cần nạp vào khi khởi động máy. Ngoài ra thư mục còn chứa các script khởi động cho Linux như danh sách các host kèm địa chỉ IP.
## /var
Thư mục /var lưu trữ các file có thể thay đổi kích thước theo thời gian. Nhiều file đăng nhập hệ thống (system log file) thường nằm trong thư mục này, ví dụ như /var/spool dùng để chứa dữ liệu tin tức, thư tín mới nhận được hoặc đang chờ gửi đi nơi khác.
## /usr
Thư mục /usr và các thư mục con quan trọng cho hệ thống Linux, bởi chứa đựng những chương trình cần thiết nhất cho hệ thống. Những thư mục cấp dưới của /usr chứa các gói phần mềm lớn người dùng đã cài đặt, ví dụ như /usr/lib chứa các thư viện để chương trình sử dụng.
Trong nhiều trường hợp, thư mục /usr được phân vùng ra làm một file system riêng rẽ.
