# Cron
Cron là cách để tạo và thực hiện các tác vụ theo một lịch trình định kì ở chế độ nền.
Trong đó, Cron job là tập hợp các tác vụ cần thực hiện và crontab là nơi lưu trữ các cronjob

Trên linux cũng có sẵn một chương trình cũng có tên là crontab để chỉnh sửa và lên hẹn những hoạt động cần làm ví dụ như tự động sao lưu, đồng bộ, cập nhật dữ liệu cho website
### Crontab
Crontab (CRON TABle) là một file chứa đựng bảng biểu (schedule) của các entries được chạy.
Một cron schedule đơn giản là một text file. Mỗi người dùng có một cron schedule riêng, file này thường nằm ở `/var/spool/cron`.

Các option:
- `-e` tạo hoặc chỉnh sửa file crontab 
- `-l` hiển thị crontab đang chạy hiện tại
- `-r` xóa file crontab

Cấu trúc một lệnh crobtab thường gồm 3 phần:
- Trường thời gian: gồm 5 chỉ số thời gian để xác định một lịch trình.
- Trường user-name: Xác định tài khoản nào được phép chạy crontab này. Mặc định là user tạo ra crontab.
- Tác vụ cần thực thi: tác vụ này có thể là một hoặc nhiều lệnh. Các lệnh sẽ cách nhau bởi dấu chấm phẩy.

Các trường thời gian có thể được sử dụng như sau:

```
*     *     *     *     *     [command to be executed]
-     -     -     -     -
|     |     |     |     |
|     |     |     |     +----- day of week (0 - 6) (Sunday=0)
|     |     |     +------- month (1 - 12)
|     |     +--------- day of month (1 - 31)
|     +----------- hour (0 - 23)
+------------- min (0 - 59)
```

Ví dụ, muốn chạy môt script tên là `reb` vào 9h30 phút sáng trong ngày thứ 4 của mỗi tháng
- `30 9 4 * * ~/testdir/reb.sh`

Hoặc chạy 30 phút một lần trong mỗi ngày của mỗi tháng:
- `0,30 * * * * ~/testdir/reb.sh`

Hoặc cứ 5 tiếng chạy một lần:
- `* */5 * * * ~/testdir/reb.sh`

Hoặc có thể sử dụng các từ khóa tương đương với các trường thời gian như:
- `@reboot` chạy khi boot hệ thống
- `@hourly` chạy vào phút thứ 0 của hàng giờ, tương đương với `0 * * * *`
- ` @daily` chạy hàng ngày vào 00:00, tương đương với `0 0 * * *`
- Cứ như vậy với `@weekly`, `monthly`, `@yearly`
### at
Là một tiện ích lập lịch trình tương tự như crontab.

Cú pháp: `at [time]`

Option time ở đây có thể ví dụ:
- `now + 10 minutes` tức sau 10 phút nữa tính từ thời điểm ra hẹn, sẽ thực thi tác vụ
- `23:30 at 12:00 December 9` thực thi tác vụ vào 11 rưỡi đêm ngày 9 tháng 11
