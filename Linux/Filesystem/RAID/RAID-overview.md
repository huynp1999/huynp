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

- **Ưu điểm**: Striping, phân chia khối dữ liệu và trải chúng qua các ổ cứng. Tăng hiệu quả thực thi khi mà dữ liệu được trải đều giúp truy xuất nhanh hơn.
- **Nhược điểm**: tiềm ẩn rủi ro về dữ liệu, chỉ cần một tỏng các ổ bị lỗi cũng gây ảnh hưởng tới hệ thống. Tỉ lệ mất dữ liệu càng cao khi càng có nhiều ổ cứng.

Cần tối thiểu 2 ổ. Phù hợp với những dữ liệu không quan trọng, nếu mất có thể không cần hoặc lấy lại được từ nơi khác. Loại RAID này không được khuyên dùng.
### RAID 1
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/RAID_1.svg/800px-RAID_1.svg.png" alt="drawing" width="200"/>

- **Ưu điểm**: Mirroring đảm bảo an toàn hơn về dữ liệu do dữ liệu được ghi vào 2 ổ giống hệt nhau, khi xảy ra lỗi vẫn có khả năng khôi phục miễn là vẫn còn một disk hoạt động.
- **Nhược điểm**: hiệu suất không cao và tốn kém chi phí do phải dành ra nửa dung lượng bộ nhớ cho việc sao lưu

Cần tối thiểu 2 ổ. Phù hợp với trường hợp không yêu cầu dung lượng lớn mà lại muốn đảm bảo 100% khôi phục.
### RAID 10
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/RAID_10.svg/800px-RAID_10.svg.png" alt="drawing" width="400"/>

Kết hợp của RAID 1 và RAID 0 (RAID 1+0), làm cả hai công việc của Mirror và Striping.
- **Ưu điểm**: truy suất nhanh và an toàn, vừa nâng cao hiệu suất mà lại đảm bảo dữ liệu không bị thất thoát khi một trong các ổ cứng bị hỏng
- **Nhược điểm**: chi phí cao vì cần số lượng disk nhất định để đảm bảo đủ điều kiện cho cả hai công việc, và số disk cũng phải là số chẵn

Yêu cầu tối thiểu 4 ổ và chỉ sử dụng 50% dung lượng (mirroring). Phù hợp cho database server hay những hệ thống yêu cầu tính sẵn sàng cao (high availability)

### RAID 5
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/64/RAID_5.svg/800px-RAID_5.svg.png" alt="drawing" width="400"/>

Hoạt động theo kỹ thuật Parity. Nếu một ổ cứng bị hỏng, dữ liệu được xây dựng lại dựa trên các thông tin còn lại trên các ổ đĩa tốt còn lại. Điều này sẽ bảo vệ dữ liệu của chúng ta khi ổ đĩa bị lỗi. 
- **Ưu điểm**: nâng cao hiệu suất, an toàn dữ liệu nhờ parity trải đều các disk, hỗ trợ phục hồi khi bất cứ một disk nào bị lỗi
- **Nhược điểm**: giá thành cao, hiệu suất sẽ bị giảm trong quá trình phục hồi. Nếu 2 ổ cứng bị lỗi cùng lúc thì không thể khôi phục dữ liệu, nhược điểm này được RAID 6 bù lại.

Cần tối thiểu 3 ổ, 2 ổ để striping, 1 ổ để phân phối parity.
- Phù hợp cho những fileserver, backup server, server lưu trữ,... đáp ứng hiệu suất phù hợp nhất với giá thành.
- Không phù hợp với database server vì RAID 5 không phù hợp với random write, bởi mỗi khi dữ liệu được nạp vào sẽ đồng nghĩa yêu cầu parity một lần cập nhật

Ngoài ra còn có RAID 50 (5+0), đáp ứng nhu cầu cho những hệ thống dữ liệu lớn.
### RAID 6
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/70/RAID_6.svg/1024px-RAID_6.svg.png" alt="drawing" width="500"/>

Hoạt động tương tự như RAID 5 nhưng với double Parity
- **Ưu điểm**: phù hợp với hệ thống lớn, cung cấp khả năng chịu lỗi cao kể cả khi 2 disk cùng lỗi một lúc
- **Nhược điểm**: tốc độ, hiệu suất kém so với RAID 5 do phải dành ra một dung lượng nhất định cho double parity

Cần tối thiểu 4 ổ để đáp ứng double parity.

Ngoài ra cũng có RAID 60 (6+0), có tốc độ đọc và khả năng chịu lỗi tốt hơn, nhưng lại có tốc độ ghi và hiệu quả lưu trữ thấp hơn so với RAID 50.

| Level  | Ổ cứng tối thiểu | Hiệu suất đọc/ghi | Tối đa dung lượng | Khả năng chịu lỗi  | Ứng dụng |
| -------------|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|
| RAID 0     |  2    |   Cao   |  100%    |  Không có    |   Gaming, các máy trạm làm việc với video, hình ảnh   |  
| RAID 1      |   2   |   Cao/Tb   |   50%   |   Một ổ bị lỗi   |   Các server nhỏ, kho dữ liệu quan trọng như sổ sách, kế toán  |      
| RAID 10      |   4   |   Cao/Tb   |   50%   |   Một ổ bị lỗi trong mỗi mảng   |  Database server, app server |     
| RAID 5      |    3  |   Cao/Thấp   |   67%-94%   |   Một ổ bị lỗi   | Các file server, kho lưu trữ dữ liệu     |        
| RAID 6      |    4  |   Cao/Thấp   |   50%-88%   |   Hai ổ bị lỗi   |   Các server có số lượng ổ cứng lớn, kho lưu trữ dữ liệu   |  

## Tối ưu tài nguyên dựa theo số lượng disk sẵn có
Giả sử khi có 1 số luợng disk là X, thì việc lựa chọn chuẩn RAID nào sẽ tùy thuộc các điều kiện disk tối thiểu của RAID đó, cũng như các ưu điểm mà RAID đó đưa ra.

- Note: đối với những hệ thống yêu cầu IOPS cao (Input - Output operation Per Second) như mail server, mà có chẵn số lượng disk và >4, thì luôn ưu tiên sử dụng RAID 10 để cho hiệu suất tốt nhất. Vì RAID 5 và 6 sẽ yêu cầu update lại parity với mỗi một lần truy xuất dữ liệu, điều này làm tiêu tốn hiệu năng hoạt động của hệ thống nhất là khi gặp một lượng truy xuất cao.

#### X=2
Về lý thuyết, 2 disk là đủ điều kiện để sử dụng RAID 0 và RAID 1. Tuy nhiên, một hệ thống trên thực tế sẽ luôn xảy ra sự cố bất kì lúc nào nên RAID 0 không được khuyên dùng. Vậy RAID 1 là phương án thực tế hơn, mặc dù sẽ yêu cầu tiêu tốn một nửa tải nguyên.

#### X=3
Với số lượng 3 disk, ngoài RAID 1 thì cũng đủ điều kiện cho RAID 5.
- RAID 5 sử dụng phương pháp parity giúp vẫn giữ được khả năng khôi phục ngang bằng với RAID 1 mà lại không bị mất quá nhiều tài nguyên cho việc sao lưu.

Phương án này vẫn cung cấp khả năng chịu lỗi mà lại tối đa dung lượng sử dụng hơn so với RAID 1.

#### 3<X<=6
Với số lượng từ 4 tới 6 disk, đưa ra 2 lựa chọn chính về RAID 5 và RAID 6. Nhưng để chọn ra được loại nào phù hợp với mục đích cũng như tối ưu nhất dành cho người sử dụng, cần phải xem xét các tiêu chí như sau:
- RAID 6 sử dụng phương pháp double parity, sẽ yêu cầu nhiều disk tối thiểu hơn cũng như giảm phần nào dung lượng tổng so với RAID 5
- Lợi ích bù lại sẽ tăng gấp đôi khả năng chịu lỗi so với RAID 5.
- Hiệu suất tái tạo dữ liệu khi gặp lỗi có thể sẽ cao hơn RAID 5, bởi dữ liệu sẽ được tái tạo từ 2 nguồn parity
- Hiệu suất ghi của RAID 6 bị giảm đáng kể. Mỗi khi dữ liệu được ghi vào là một lần yêu cầu update parity, điều này làm giảm hiệu suất ghi tổng của hệ thống. Tốc độ ghi càng giảm thêm khi sử dụng double parity, do cần phải update 2 parity.
- Hiệu suất đọc giữa 2 loại này là tương tự như nhau.

Như vậy, đối với dữ liệu yêu cần độ an toàn ở mức cao nhất thì sử dụng RAID 6. Còn không thì nên sử dụng RAID 5, do vẫn giữ được một mức an toàn dữ liệu nhất định mà lại bớt tốn kém chi phí hơn RAID 6.

Ngoài ra với số lượng disk cao hơn có thể tham khảo tại [đây](https://www.netgear.com/media/WP-ReadyNAS-FlexRAID-Optimization-Guide_tcm148-56499.pdf) (17)
