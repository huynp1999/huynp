# mdadm
Là một công cụ dùng để quản lý RAID mềm trong hầu hết các bản phân phối Linux. Gói mdadm cũng được tích hợp và sử dụng trong các distro Linux hiện tại, thay thế có các tiện cũ như raidtools2 hoặc raidtools.

Các option:
- `-C` tạo RAID mới
- `-l` level của RAID
- `-a` thêm device vào mảng có sẵn
- `-r` gỡ device khỏi mảng
- `-f` đánh dấu ổ bị lỗi
- `-n` thiết bị dành RAID (là 2 phân vùng vừa tạo)
- `-E` kiểm tra thông tin

## Thay thế và đồng bộ disk khi gặp sự cố với RAID 1
Có sẵn một mảng RAID 1, giả sử ổ cứng muốn thay thế là `/dev/vdb` (nếu một trong các ổ cứng bị lỗi kết quả sẽ hiển thị `[U_]`)

    huynp@ubuntu:~$ cat /proc/mdstat
    Personalities : [linear] [multipath] [raid0] [raid1] [raid6] [raid5] [raid4] [raid10] 
    md0 : active raid1 vdc[1] vdb[0]
          1047552 blocks super 1.2 [2/2] [UU]

Để loại bỏ một thiết bị, trước tiên nó phải được đánh dấu là bị lỗi bằng flag `-f/–fail`.

    huynp@ubuntu:~$ sudo mdadm /dev/md0 -f /dev/vdb
    mdadm: set /dev/vdb faulty in /dev/md0

Kiểm tra lại

    huynp@ubuntu:~$ cat /proc/mdstat
    Personalities : [linear] [multipath] [raid0] [raid1] [raid6] [raid5] [raid4] [raid10] 
    md0 : active raid1 vdc[1] vdb[0](F)
          1047552 blocks super 1.2 [2/1] [_U]

Gỡ thiết bị ra khỏi mảng RAID

    huynp@ubuntu:~$ sudo mdadm /dev/md0 -r /dev/vdb
    mdadm: hot removed /dev/vdb from /dev/md0

Lúc này, ổ cứng đã có thể được gỡ ra khỏi hệ thống và thay thế bằng thiết bị mới. 
Thực hiện đồng bộ hóa từ ổ cứng hiện còn lại sang ổ cứng mới gắn (Lưu ý: cần xác định chính xác ổ cứng đang có và ổ cứng mới gắn vào trước khi thực thi lệnh sau):

    sudo sfdisk -d /dev/vdc
    sudo sfdisk /dev/vdd

Hoàn thành đồng bộ hóa
    
    huynp@ubuntu:~$ cat /proc/mdstat
    Personalities : [linear] [multipath] [raid0] [raid1] [raid6] [raid5] [raid4] [raid10] 
    md0 : active raid1 vdd[2] vdc[1]
          1047552 blocks super 1.2 [2/1] [_U]
          [=====>...............]  recovery = 25.0% (262144/1047552) finish=0.4min speed=29127K/sec

    huynp@ubuntu:~$ cat /proc/mdstat
    Personalities : [linear] [multipath] [raid0] [raid1] [raid6] [raid5] [raid4] [raid10] 
    md0 : active raid1 vdd[2] vdc[1]
          1047552 blocks super 1.2 [2/2] [UU]

