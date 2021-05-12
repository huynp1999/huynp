# Quản lý tiến trình

## ps
Dùng để xem thông tin của các tiến trình đang chạy trong hệ thống.
Tiện ích ps sẽ đọc thông tin tiến trình từ một file ảo nằm trong thư mục /proc, kết hợp với một số tuỳ chọn để người dùng dễ dàng quan sát.

Cú pháp: `ps [option]`

Các cột thông tin:
- PID  – ID đặc trưng cho tiến trình
  - PPID - PID của tiến trình cha
- TTY  – thông tin terminal người dùng đăng nhập
- TIME – lượng thời gian tiến trình đó sử dụng CPU (nếu là 00:00:00 có nghĩa tiến trình đó không sử dụng CPU)
- CMD  – tên lệnh khởi động tiến trình

Các option:
- `ps`    show những tiến trình đang chạy ở shell hiện tại
- `-a/-e` show tất cả những tiến trình đang chạy
- `-f`    show full các thông tin
- `-u`    chọn show theo user ID 
  - Ví dụ khi khởi tạo một phiên tmux sẽ cho PPID bằng với bash đã khởi tạo nó (tiến trình cha)
  - ```
huynp     6444  6159  0 09:02 pts/1    00:00:00 bash
huynp     6452  6444  0 09:02 pts/1    00:00:00 tmux
```
- `-p 2234,1124,1294` shơw theo theo danh sách PID
  - `--ppid` show theo PPID
```
huynp@huyComputer:~$ ps -f --ppid 6444
UID        PID  PPID  C STIME TTY          TIME CMD
huynp     6452  6444  0 09:02 pts/1    00:00:00 tmux
```
- `-t` chọn show theo tty
- `-- forest` show theo cây
- `-o` show theo các cột cho trước

Ví dụ show PID 4558 theo từng cột pid,ppid,user,cmd
```
huynp@huyComputer:~$ ps -p 4558 -o pid,ppid,user,cmd
  PID  PPID USER     CMD
 4558     1 huynp    /usr/lib/firefox/firefox -new-window
```
- `-C` show theo tên của tiến trình
```
huynp@huyComputer:~$ ps -C firefox -o pid=
 4558
```
**Quản lý hiệu năng**, list những tiến trình nào sử dụng cpu hay memory nhiều nhất: `ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%cpu | head`

```
huynp@huyComputer:~$ ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head
  PID  PPID CMD                         %MEM %CPU
 4558     1 /usr/lib/firefox/firefox -n 12.5 24.2
 5104  4558 /usr/lib/firefox/firefox -c  8.7  1.1
 2686  2445 /usr/bin/gnome-shell         7.7  6.2
```
# top
Lệnh top hiển thị trạng thái hoạt động của hệ thống, và những tác vụ của kernel theo thời gian thực.

Khởi động: `top`

Phím tắt:
- `q` thoát
- `Shift+O` để sắp xếp theo từng kiểu vùng
- `z` show tất cả các tiến trình đang chạy
- `k` kill tiến trình theo PID
- `Shift+P` sắp xếp theo %cpu được các tiến trình sử dụng 

Các option:
- `-u huynp` show tiến trình theo user
- `-n 1 -b > outp.txt` lưu và đẩy kết quả hiển thị vào file

# htop 
Là một bản nâng cấp của top với nhiều cải tiến như hỗ trợ dùng chuột, hiển thị màu trực quan,...

Cài đặt:   `sudo apt-get install htop`
Khởi động: `htop`

Màn hình hiển thị của htop được chia làm 3 phần:
- Header: hiển thị các số liệu hệ thống bao gồm CPU, Ram, Swap, các tác vụ đang chạy, load average và thời gian hoạt động (Uptime)
- Body: liệt kê tất cả tiến trình đang chạy
- Footer: hiển thị các tùy chọn

Các cột thông số:
- `PID` số ID của tiến trình
- `USER` người dùng sở hữu tiến trình
- `PR` độ ưu tiên của tiến trình. Số càng thấp, ưu tiên càng cao
- `NI` giá trị nice value của tiến trình, liên quan đến độ ưu tiên
- `VIRT`  bộ nhớ ảo được sử dụng
- `RES` dung lượng RAM vật lý được sử dụng (kilobyte)
- `SHR` bộ nhớ chia sẻ mà tiến trình đang sử dụng
- `S` Tình trạng hiện tại của tiến trình
- `%CPU` tỷ lệ CPU được sử dụng 
- `%MEM` tỷ lệ RAM vật lý được sử dụng
- `TIME+` thời gian sử dụng CPU của tiến trình
- `COMMAND` tên lệnh khởi tạo tiến trình

Các phím tắt:
- `F9`    kill process
- `F7/F8` renice tiến trình
- `I`     liệt kê các tập tin được sử dụng bởi tiến trình
- `U`     chỉ hiển thị tiến trình theo một người dùng
- `F6`    sắp xếp hiện thị theo cột cho trước
- `F5`    hiển thị theo dạng cây

# Kill process
Xem các tùy chọn SIGNAL để làm việc với tiến trình: `kill -l`
Một số SIGNAL chính:
- `-9`  - SIGKILL   hard kill, xóa ngay lập tức
- `-15` - SIGTERM   soft kill, hẹn giờ xóa
- `-18` - SIGCONT   tiếp tục tiến trình
- `-19` - SIGSTOP   tạm dừng tiến trình

Ví dụ khi cần kill process, trước tiên cần tìm PID của tiến trình: `ps -a | grep firefox` và `kill -9 [PID]`
