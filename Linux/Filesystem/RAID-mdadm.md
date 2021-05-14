# RAID
RAID (Redundant Arrays of Inexpensive Disks) là à một kỹ thuật ảo hóa, cho phép ghép nhiều ổ đĩa cứng vật lý thành một hệ thống bộ nhớ.
Mỗi một loại RAID kèm theo những tính năng như
- Gia tăng tốc độ đọc/ghi dữ liệu
- Độ an toàn cho dữ liệu được lưu trữ
- Dung lượng lưu trữ lớn
- Hiệu suất làm việc cao

## Các kỹ thuật trong RAID
- **Parity**: là một phương pháp tạo lại nội dung bị mất từ thông tin parity. Ứng dụng trong RAID5 và RAID6
- **Stripe**: phân phối dữ liệu ngẫu nhiên vào nhiều đĩa, như vậy sẽ không có dữ liệu đầy đủ trong một đĩa.
- **Mirroring**: tạo một bản sao của cùng một dữ liệu. Sử dụng trong RAID1 và RAID10
- **Hot spare**: là một ổ đĩa dự phòng trong máy chủ, có thể tự động thay thế và xây dựng lại các ổ đĩa bị lỗi.
- **Chunks**: là một kích thước của dữ liệu tối thiểu từ 4KB trở lên. Bằng cách xác định kích thước chunks mà có thể tăng hiệu suất I/O.

## Các chuẩn RAID
### RAID 0
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/9b/RAID_0.svg/800px-RAID_0.svg.png" alt="drawing" width="200"/>

- **Ưu điểm**: Striping phân chia khối dữ liệu và trải chúng qua các ổ cứng. Tăng hiệu quả thực thi.
- **Nhược điểm**: tiềm ẩn rủi ro về dữ liệu. Bởi dữ liệu được chia đôi lưu trên 2 ổ cứng nếu hỏng 1 trong 2 thì nguy cơ mất dữ liệu rất cao

### RAID 1
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/RAID_1.svg/800px-RAID_1.svg.png" alt="drawing" width="200"/>

- **Ưu điểm**: Mirroring đảm bảo an toàn hơn về dữ liệu do dữ liệu được ghi vào 2 ổ giống hệt nhau
- **Nhược điểm**: hiệu suất không cao và tốn kém chi phí

### RAID 10
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/RAID_10.svg/800px-RAID_10.svg.png" alt="drawing" width="400"/>

Kết hợp của RAID 1 và RAID 0 (RAID 1+0), làm cả hai công việc của Mirror và Striping.
- **Ưu điểm**: lưu trữ nhanh nhẹn và an toàn, vừa nâng cao hiệu suất mà lại đảm bảo dữ liệu không bị thất thoát khi một trong các ổ cứng bị hỏng
- **Nhược điểm**: Chi phí cao

### RAID 5
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/64/RAID_5.svg/800px-RAID_5.svg.png" alt="drawing" width="400"/>

Hoạt động theo kỹ thuật Parity. Nếu một ổ cứng bị hỏng, dữ liệu được xây dựng lại dựa trên các thông tin còn lại trên các ổ đĩa tốt còn lại. Điều này sẽ bảo vệ dữ liệu của chúng ta khi ổ đĩa bị lỗi. 
- **Ưu điểm**: nâng cao hiệu suất, an toàn dữ liệu
- **Nhược điểm**: giá thành cao, hiệu quả thực thi giảm trong quá trình phục hồi

### RAID 6
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/70/RAID_6.svg/1024px-RAID_6.svg.png" alt="drawing" width="500"/>

Hoạt động tương tự như RAID 5 với Parity, nhưng cần nhiều tài nguyên tối thiểu hơn
- **Ưu điểm**: sử dụng trong mảng lớn
- **Nhược điểm**: tốc độ, hiệu suất kém so với RAID 5

## mdadm quản lý RAID
RAID được quản lý bằng gói `mdadm` trong hầu hết các bản phân phối Linux.

Các chế độ hoạt động:
- Assemble: kết hợp những mảng đã tạo thành mảng hoạt động
- Build: tạo một mảng mới không có superblock (là một khoảng được tạo trên mỗi thiết bị, chứa thông tin về thiết bị RAID và cho phép sửa chữa việc ghép mảng) 
- Create: tạo một mảng mới có superblock
- Monitor: theo dõi sự thay đổi của một hoặc nhiều thiết bị
- Grow: thay đổi kích thước mảng 
- Manage: quản lý các thiết bị như thêm mới hoặc xóa
- Misc: xóa các superblock cũ và thu thập dữ liệu
- Auto-detect: yêu cầu kernel Linux kích hoạt các mảng


Các option:
- `-C` tạo RAID mới.
- `-l` level của RAID.
- `-n` thiết bị dành RAID (là 2 phân vùng vừa tạo)
- `-E` kiểm tra thông tin

Tạo RAID:
Trước tiên cần phải phân vùng từ những ổ cứng, ví dụ với RAID 0 cần phải có ít nhất 2 ổ cứng.

Tạo RAID 0 từ 2 phân vùng vừa tạo và kiểm tra
```
mdadm -C /dev/md0 -l raid0 -n 2 /dev/sd[b-c]1
mdadm -E /dev/sd[b-c]1
```
