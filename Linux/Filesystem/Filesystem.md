# Các dạng filesystem

Có nhiều dạng file hệ thống trong Linux, mỗi loại sẽ được áp dụng với từng mục đích riêng biệt. Tùy theo nhu cầu và mục đích của người sử dụng mà sẽ áp dụng những phương pháp cần thiết.


**Ext (Extended file system)** là định dạng file hệ thống đầu tiên được thiết kế dành riêng cho Linux. Có tổng cộng 4 phiên bản và mỗi phiên bản lại có 1 tính năng nổi bật:
- ext: là bản mở rộng của minix và được thay thế hoàn toàn bởi ext2 
- ext2: không cung cấp khả năng ghi nhật ký (các bản ghi thay đổi đối với một phân vùng được lưu vào nhật ký để cải thiện khả năng khôi phục khi xảy ra sự cố)
- ext3: thực chất là một phiên bản ext2 có cung cấp khả năng nhật ký và tương thích ngược với ext2. Đã bị xóa bỏ từ kernel Linux 4.3
- ext4: là bản nâng cấp của ext3 với nhiều tính năng được cải thiện và đang phổ biến nhất hiện nay

**Alternate filesystems** 
- swap: không thực sự là 1 dạng file hệ thống, bởi cơ chế hoạt động khá khác biệt. Được sử dụng dưới dạng bộ nhớ ảo và được dùng bởi kernel để ghi thay đổi vào ổ cứng. Thông thường, nó chỉ được sử dụng khi hệ thống thiếu hụt bộ nhớ RAM
- XFS: là một trong những dạng filesystem chính của Linux mà không thuộc ext, có hỗ trợ journaling cùng với hiệu suất và tính đồng thời cao dành cho những hệ thống file lớn. Hiện đang là dạng filesystem mặc định của Red Hat Linux
- Btrfs,JFS,BFS,...

Hoặc một số loại của Windows như: ntfs, vfat

# Tạo và quản lý filesystem
Lệnh `mfsk` được dùng cho việc tạo filesystem. Quá trình này chuẩn bị phân vùng để thực hiện lưu trữ dữ liệu.

Cú pháp: `mfsk.[types] [partition]`

Trong đó types bao gồm những kiểu lưu trữ được nêu bên trên, partition là nơi cần tạo filesystem.
