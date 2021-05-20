# Rsnapshot
Rsnapshot là một giải pháp sao lưu gọn nhẹ và đơn giản, có thể luân phiên backup các thư mục local hoặc từ các remote server.

Rsnapshot là một script được xây dựng trên nền tảng OpenSSH và rsync

Sau khi cài đặt gói `rsnapshot`, file cấu hình sẽ nằm ở `/etc/rsnapshot.conf`. Trong có cho biết thông tin chính như:

- `snapshot_root` nơi lưu trữ backup
- `cmd_ssh` đường dẫn cần cung cấp tới ssh binary
- Backup Interval
  - Với các giá trị mặc định, rsnapshot sẽ có 6 bản sao dự phòng theo giờ trước khi bắt đầu ghi đè lên cái cũ, 7 bản sao hàng ngày, 4 bản hàng tuần.
  - Các bí danh như `alpha` = `hourly`, `beta` = `daily`, `gamma` = `weekly`,...
- Verbose level
  - Tùy chọn in ra màn hình các tiến trình hoạt động
- `logfile` cung cấp các bản ghi cho việc quản lý
- Backup point
  - Gồm các điểm backup, những gì cần sao lưu từ máy của mình.
  - Ví dụ như muốn backup từ ột remote server về local: `backup root@192.168.50.9:/root/testdir /root/testdir`
