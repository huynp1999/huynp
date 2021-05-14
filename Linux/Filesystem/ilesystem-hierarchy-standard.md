# Filesystem Hierarchy Standard (FHS)
Là một tiêu chuẩn thiết kế thư mục trong các bản phân phối Linux. FHS được tạo ra và duy trì bởi Linux Foundation.

Pseudo filesystem là một cấu trúc được tạo bởi các file ảo, không có thật (pseudo). Cấu trúc file này đại diện cho các tài nguyên thật và thuộc tính của chúng. Khi tổ chức phần cứng theo cách này, làm cho việc tương tác với phần cứng trông giống như một phần mềm.

Hai thuộc tính file:
- shareable hoặc unshareable
  - shareable: là những file được lưu ở host, có thể truy cập từ host khác ví dụ như trong folder `/home`
  - unshareable: là những file được phải nằm trên hệ thống riêng của chúng, ví dụ như trong foler `/etc`
- variable hoặc static
  - variable: là những file được thay đổi bởi người dùng hoặc các tiến trình
  - static: là những file cần quyền superuser để can thiệp, ví dụ như `/etc`, `/usr`
  - 
Kiến trúc này được sắp xếp theo cây thư mục, với thư mục root nằm ở trên cùng (/).
![Alt](https://i.imgur.com/gtuIBzE.png)

### /
Cung cấp mount point cho các file system khác.
### /boot
Chứa tất cả các files cần thiết cho quá trình boot hệ thống. Những chương trình cần thiết cho việc boot loader sẽ được đặt ở `/sbin`
### /dev
Chứa các file đại diện cho các thiết bị ví dụ như:
- `/dev/sda`  ổ cứng
- `/dev/mouse`  chuột
- `/dev/null` là một nơi sẽ xóa mọi dữ liệu được ghi vào nó (blackhole), nhưng vẫn thông báo ghi thành công
### /sys
Chứa file sysfs là nơi cung cấp thông tin về các kernel module, thiết bị phần cứng cũng như giao tiếp với driver của các thiết bi.

Một số thư mục con gồm:
- /sys/devices/: đại diện cho cây phân cấp các thiết bị trong kernel
- /sys/block/: chứa một liên kết tượng trưng cho mỗi thiết bị được kết nối vào hệ thống, tương ứng với /sys/devices/
- /sys/class/: thư mục con này chứ một lớp các thư mục con khác dành cho các thiết bị đã được đăng ký với hệ thống. Ví dụ /sys/class/printer chứa liên kết tới máy in.
### /bin
Thư mục /bin chứa các chương trình thực thi, hay còn gọi là các binaries (nhị phân). Chúng là chương trình thiết yếu được sử dụng bởi admin hoặc user thường, như `ls`,`pwd`,...
### /sbin
Chứa các file nhị phân hệ thống giống `/bin`. Nhưng các file ở đây thường dành cho superuser. (superuser-bin).
### /etc
Chứa nhiều file config dùng để điều khiển hoạt động của một chương trình nào đó, ví dụ như của NGINX, cũng như fstab và danh sách các file system cần nạp vào khi khởi động máy. Ngoài ra thư mục còn chứa các script khởi động cho Linux như danh sách các host kèm địa chỉ IP.
- `/etc/motd` tin nhắn khi user login
- `/etc/passwd` file password
- `/etc/protocols` danh sách giao thức IP
### /home
Chứa các file cá nhân của từng user.
### /lib 
Chứa các thư viện cần thiết cho việc boot, cũng như để thực thi các câu lệnh trong `/bin` và `/sbin`.
### /media
Là nơi mount các thiết bị media như floppy (ổ đĩa mềm), cdrom (ổ đĩa CD),...
### /mnt 
Chứa các filesystems được mount tạm thời.
### /opt 
Thư mục dùng để cài đặt gói cho các phần mềm. Các phần mềm được cài đặt ở đây là optional, thường không được cài đặt trực tiếp từ packages management của distro.
### /root
Giống như `/home` nhưng dành cho user root.
### /run
Chứa thông tin về các tiến trình đang chạy, ví dụ như các file `.pid`, `.sock`.
### /srv 
Chứa data được cung cấp ra bên ngoài hệ thống. Có thể là data hoặc scripts dành cho web servers, data được cung cấp bởi FTP server.
### /tmp 
Chứa các file tạm thời, được sinh ra bởi các chương trình đã và đang chạy.Khi reboot sẽ bị xóa, khác với `/var/tmp` reboot sẽ không mất.
### /var
Chứa variable files, tức những file mà sẽ liên tục thay đổi kích thước trong quá trình vận hành hệ thống, chẳng hạn như những file logs, lock, email tạm thời,...
FHS cũng đưa ra những quy chuẩn cho thư mục bên dưới `/var`
- `/var/opt` chứa variable data dành cho các phần mềm được cài đặt trong `/opt`
- `/var/run` symbolic link trỏ đến /run
### /usr
Là thư mục quan trọng thứ hai của một hệ thống Linux, bởi chứa đựng những chương trình cần thiết nhất cho hệ thống. Những thư mục cấp dưới của `/usr` cũng phải theo quy chuẩn của FHS tương tự như `/`.
- `/usr/lib` chứa các thư viện để chương trình sử dụng
- `/usr/local` là một phiên bản thu nhỏ của `/usr` dành cho các phần mềm tự build, tự cài không theo distro
- `/usr/bin/` và `/usr/sbin` dành cho những binary file không cần thiết khi khắc phục sự cố (như ở `/bin` và `/sbin`). Các phần mềm thuộc distro cũng được cài đặt tại đây
Trong nhiều trường hợp, thư mục /usr được phân vùng ra làm một filesystem riêng rẽ.
