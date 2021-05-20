Tmux và Byobu là những loại terminal multiplexer. Cả hai đều có chức năng chính là cho phép tiếp cục các session sau khi bị ngắt quãng như mất mạng, tắt nguồn,... Phù hợp với những người dùng quản trị các server, hệ thống trong liên tục hàng giờ.

# Tmux
Cài đặt: `sudo apt-get install tmux`

Các cú pháp với session:
- `tmux`    tạo một session mới
- `tmux a`  attach session mới
- `tmux new -s s_name`  tạo một session mới kèm theo tên gọi:
- `tmux a -t s_name`    attach session đã được đặt tên:
- `tmux ls` danh sách các sessions
- `tmux kill-session -t s_name` xoá một session:

Khi tạo một session xong, prefix tuỳ chọn cửa sổ là tổ hợp `Ctrl+b`, tương tự như `Esc` trong Vim

Các cú pháp với cửa sổ:
- `Ctrl+b c`    tạo một cửa sổ mới
- `Ctrl+b w`    xem danh sách cửa sổ hiện tại
- `Ctrl+b n/p`　chuyển đến cửa sổ tiếp theo hoặc trước đó
- `Ctrl+b f`　  tìm kiếm cửa sổ
- `Ctrl+b ,`　  đặt/Đổi tên cho cửa sổ
- `Ctrl+b &`　  đóng cửa sổ

Cú pháp với các panel
- `Ctrl+b %`    chia đôi màn hình theo chiều dọc
- `Ctrl+b "`    chia đôi màn hình theo chiều ngang (hoặc `Ctrl+b :split-window`)
- `Ctrl+b o/<phím mũi tên>` di chuyển giữa các panel
- `Ctrl+b q`    hiện số thứ tự trên
- `Ctrl+b x`    xoá panel

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/tmux.png)
# Byobu
Cài đặt: `sudo apt-get install byobu`
Tạo một session mới: `byobu`

Các cú pháp chính với cửa sổ:

- `Shift+F1`  xem các phím tắt chức năng
- `F2`        tạo một cửa sổ mới
- `Ctrl-a k`  đóng cửa sổ đang dòng
- `F8`        đặt tên cửa sổ
- `F3/F4`     chuyển tới cửa sổ trước hoặc sau (hoặc `Alt+Right Arrow` và `Alt+Left Arrow`)
- `Ctrl+F2`   chia đôi màn hình theo chiều dọc
- `Shift+F2`  chia đôi màn hình theo chiều ngang

Các cú pháp với panel
- `Shift+Up Arrow và Shift+Down Arrow` di chuyển giữa các panel
- `Ctrl+F6`   xoá panel đang dùng
- `shift-F5`  hợp nhất các panel thành một

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/byobu1.png)
