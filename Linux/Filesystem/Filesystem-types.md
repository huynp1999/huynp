Filesystem types
Có nhiều dạng file hệ thống trong Linux, mỗi loại sẽ được áp dụng với từng mục đích riêng biệt. Tùy theo nhu cầu và mục đích của người sử dụng mà sẽ áp dụng những phương pháp cần thiết.

Ext (Extended file system) là định dạng file hệ thống đầu tiên được thiết kế dành riêng cho Linux. Có tổng cộng 4 phiên bản và mỗi phiên bản lại có 1 tính năng nổi bật:
- ext2: không cung cấp khả năng ghi nhật ký (các bản ghi thay đổi đối với một phân vùng được lưu vào nhật ký để cải thiện khả năng khôi phục nếu xảy ra sự cố)
- ext3: cung cấp khả năng nhật ký nhưng đã bị xóa bỏ từ kernel Linux 4.3
- ext4: cung cấp khả năng nhật ký và đang phổ biến nhất hiện nay
- swap: không thực sự là 1 dạng file hệ thống, bởi cơ chế hoạt động khá khác biệt. Được sử dụng dưới dạng bộ nhớ ảo và được dùng bởi kernel để ghi thay đổi vào ổ cứng. Thông thường, nó chỉ được sử dụng khi hệ thống thiếu hụt bộ nhớ RAM.
- XFS,Btrfs,JFS

Hoặc một số loại của Windows như: ntfs, vfat

