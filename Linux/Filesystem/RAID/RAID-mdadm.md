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

- **Ưu điểm**: Striping, phân chia khối dữ liệu và trải chúng qua các ổ cứng. Tăng hiệu quả thực thi.
- **Nhược điểm**: tiềm ẩn rủi ro về dữ liệu, tỉ lệ mất dữ liệu càng cao khi càng có nhiều ổ cứng.

Cần tối thiểu 2 ổ. Phù hợp với những dữ liệu không quan trọng, nếu mất có thể không cần hoặc lấy lại được từ nơi khác. Loại RAID này không được khuyên dùng.
### RAID 1
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/RAID_1.svg/800px-RAID_1.svg.png" alt="drawing" width="200"/>

- **Ưu điểm**: Mirroring đảm bảo an toàn hơn về dữ liệu do dữ liệu được ghi vào 2 ổ giống hệt nhau
- **Nhược điểm**: hiệu suất không cao và tốn kém chi phí do phải chia nửa bộ nhớ để sao lưu

Cần tối thiểu 2 ổ. Phù hợp với trường hợp không yêu cầu dung lượng lớn mà lại muốn đảm bảo 100% khôi phục.
### RAID 10
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/RAID_10.svg/800px-RAID_10.svg.png" alt="drawing" width="400"/>

Kết hợp của RAID 1 và RAID 0 (RAID 1+0), làm cả hai công việc của Mirror và Striping.
- **Ưu điểm**: lưu trữ nhanh nhẹn và an toàn, vừa nâng cao hiệu suất mà lại đảm bảo dữ liệu không bị thất thoát khi một trong các ổ cứng bị hỏng
- **Nhược điểm**: chi phí cao

Yêu cầu tối thiểu 4 ổ và và chỉ sử dụng 50% dung lượng (mirroring). Phù hợp cho database server hay những hệ thống yêu cầu tính sẵn sàng cao (high availability)

### RAID 5
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/64/RAID_5.svg/800px-RAID_5.svg.png" alt="drawing" width="400"/>

Hoạt động theo kỹ thuật Parity. Nếu một ổ cứng bị hỏng, dữ liệu được xây dựng lại dựa trên các thông tin còn lại trên các ổ đĩa tốt còn lại. Điều này sẽ bảo vệ dữ liệu của chúng ta khi ổ đĩa bị lỗi. 
- **Ưu điểm**: nâng cao hiệu suất, an toàn dữ liệu
- **Nhược điểm**: giá thành cao, hiệu quả thực thi giảm trong quá trình phục hồi. Nếu 2 ổ cứng bị lỗi cùng lúc thì không thể khôi phục dữ liệu, nhược điểm này được RAID 6 bù lại.

Cần tối thiểu 3 ổ, 2 ổ để striping, 1 ổ để phân phối parity.
- Phù hợp cho những fileserver, backup server, server lưu trữ,... đáp ứng hiệu suất phù hợp nhất với giá thành.
- Không phù hợp với database server vì RAID 5 không phù hợp với random write, bởi mỗi khi dữ liệu được nạp vào sẽ đồng nghĩa yêu cầu parity một lần cập nhật

Ngoài ra còn có RAID 50 (5+0), đáp ứng nhu cầu cho những hệ thống dữ liệu lớn.
### RAID 6
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/70/RAID_6.svg/1024px-RAID_6.svg.png" alt="drawing" width="500"/>

Hoạt động tương tự như RAID 5 nhưng với double Parity
- **Ưu điểm**: sử dụng trong mảng lớn với khả năng khôi hồi lớn
- **Nhược điểm**: tốc độ, hiệu suất kém so với RAID 5

Cần tối thiểu 4 ổ để đáp ứng double parity.

Ngoài ra cũng có RAID 60 (6+0), có tốc độ đọc và khả năng chịu lỗi tốt hơn, nhưng lại có tốc độ ghi và hiệu quả lưu trữ thấp hơn so với RAID 50.

## Tối ưu tài nguyên dựa theo số lượng disk sẵn có
Giả sử khi có 1 số luợng disk là X, thì việc lựa chọn chuẩn RAID nào sẽ tùy thuộc các điều kiện disk tối thiểu của RAID đó, cũng như các ưu điểm mà RAID đó đưa ra.

- Note: đối với những hệ thống yêu cầu IOPS cao (Input - Output operation Per Second) như mail server, mà có chẵn số lượng disk và >4, thì luôn ưu tiên sử dụng RAID 10 để cho hiệu suất tốt nhất. Vì RAID 5 và 6 sẽ yêu cầu update lại parity với mỗi một lần truy xuất dữ liệu, điều này làm tiêu tốn hiệu năng hoạt động của hệ thống nhất là khi gặp một lượng truy xuất cao.

#### X=2:
Về lý thuyết, 2 disk là đủ điều kiện để sử dụng RAID 0 và RAID 1. Tuy nhiên, một hệ thống trên thực tế sẽ luôn xảy ra sự cố bất kì lúc nào nên RAID 0 không được khuyên dùng. Vậy RAID 1 là phương án thực tế hơn, mặc dù sẽ yêu cầu tiêu tốn một nửa tải nguyên.

#### 2<X<29:
Với số lượng từ 2 disk trở lên, ngoài RAID 1 thì cũng đủ điều kiện cho RAID 5 và 6.
- RAID 5 sử dụng phương pháp parity giúp vẫn giữ được khả năng khôi phục ngang bằng với RAID 1 mà lại không bị mất quá nhiều tài nguyên cho việc sao lưu.
- RAID 6 thì được bổ sung thêm một dung lượng parity nữa tăng khả năng chịu lỗi.

Bởi RAID 5 hỗ trợ tối đa 30 ổ cứng trong một volume group nên mốc 30 là phù hợp để sử dụng tối đa hiệu năng của RAID 5 (RAID 50). Phương án này vừa cho phép khôi phục dữ liệu, tiết kiệm chi phí so với RAID 6 mà lại tối đa dung lượng sử dụng hơn so với RAID 1.

#### 30<X<60
RAID 6 cũng hỗ trợ tối đa 30 ổ cứng trong một volume group nên mốc 30 tới 60 là phù hợp dành do RAID 6 (RAID 60). Bởi khi một hệ thống sử dụng số lượng lớn các disk đồng nghĩa với việc sẽ càng cần nhiều ưu tiên cho khả năng chịu lỗi.

Các mốc số luợng sử dụng cũng được tham khảo tại [đây](https://www.netgear.com/media/WP-ReadyNAS-FlexRAID-Optimization-Guide_tcm148-56499.pdf) (17)
