# Disk partition
Có chức năng chia một ổ cứng vật lý thành nhiều ổ logic con. Đơn giản hóa việc quán lý và chia sẻ tài nguyên
Có 3 partition mặc định chính:
1. root (ký hiệu /): chứa file hệ thống
2. boot: dành cho khởi động
3. swap: tương tự như RAM và thường được đặt gấp đôi dung lượng RAM thật

Đôi khi /var, /home cũng cần phân vùng nhằm tránh trường hợp quá tải chèn lên những phân vùng khác.
Việc phân vùng ổ cứng thường được làm trên một hệ thống mới cài đặt. Việc tùy chỉnh và quản lý các partition được hỗ trợ thông qua các phần mềm như GNU Parted, fdisk,...

## Tạo phân vùng
Fdisk là một công cụ command line được sử dụng để phân chia phân vùng ổ đĩa trên linux/unix.
Tạo một partition: (ví dụ ở đây tạo /dev/sda3p1 từ phân vùng của root là /dev/sda3)
1. Trước tiên kiểm tra phân vùng trên một đĩa cụ thể:
```
$ sudo fdisk -l /dev/sda3
Disk /dev/sda3: 21,9 GiB, 23457693696 bytes, 45815808 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 4096 bytes
I/O size (minimum/optimal): 4096 bytes / 4096 bytes
```
2. Tiến hành phân vùng /dev/sda3
```
$ sudo fdisk /dev/sda3
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.
Device does not contain a recognized partition table.
Created a new DOS disklabel with disk identifier 0x11119dd8.
```
3. Chọn n để tạo một partition mới
```
command (m for help): n
Partition type
   p   primary (0 primary, 0 extended, 4 free)
   e   extended (container for logical partitions)
Select (default p): p
Partition number (1-4, default 1): 
First sector (2048-45815807, default 2048): 
Last sector, +sectors or +size{K,M,G,T,P} (2048-45815807, default 45815807): +2G                 

Created a new partition 1 of type 'Linux' and of size 2 GiB.
```
- `p`:dành cho phân vùng chính
- `e`:dành cho phân vùng mở rộng
4. Kiểm tra lại /dev/sda3 sẽ xuất hiện phân vùng đã được tạo thành công:
```
Device      Boot Start     End Sectors Size Id Type
/dev/sda3p1       2048 4196351 4194304   2G 83 Linux
```

## Xóa phân vùng
```
$ sudo fdisk /dev/sda3
command (m for help): d
Selected partition 1
Partition 1 has been deleted.
Command (m for help): w

The partition table has been altered.
The kernel still uses the old partitions. The new table will be used at the next reboot. 
Syncing disks.
```
