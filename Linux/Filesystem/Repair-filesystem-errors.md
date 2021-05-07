# fsck
fsck (file system consistency check) là một tiện ích hệ thống, được sử dụng khi các file hệ thông gặp sự cố, không thể truy cập hoặc boot thành công.

Các lựa chọn sử dụng tùy theo từng trường hợp:
- `-A` dùng để kiểm tra tất cả các file hệ thống. Danh sách này được lấy từ /etc/fstab.
- `-C` hiện quá trình hoạt động.
- `-l` khóa thiết bị không cho các ứng dụng sử dụng phân vùng khi đang check.
- `-M` không check các file đã được mount.
- `-N` show những _khả năng_ có thể thực thi.
- `-P` check các file cùng lúc, gồm cả root.
- `-R` không check file hệ thống của root, dùng với ‘-A‘.
- `-r` thống kê các thiết bị đã được check.
- `-t` Chỉ ra một các loại file riêng cần check.
- `-V` show các việc đã hoàn thành.

Với cú pháp: `fsck [option] [partition]`

ví dụ: `fsck -AR` để check toàn bộ file hệ thống trừ root 

