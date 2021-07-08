# RAID Controller Card
RAID được phân ra hai loại là RAID cứng (RAID Card - Hardware RAID) và RAID mềm (Software RAID)

- **RAID mềm:** sử dụng sức mạnh tính toán của CPU. Được hỗ trợ trong hệ điều hành, không yêu cầu thiết bị disk, raid controller,... mà vẫn có thể thực hiện trên tất cả các máy, chi phí rẻ nhưng hiệu xuất thấp.
- **RAID cứng:** bao gồm các bộ xử lý và bộ nhớ riêng dành cho RAID. RAID cứng có thể có sẵn trong mainboard hoặc được tích hợp card add-in.

**RAID Card** hay **RAID Controller** là một thiết bị phần cứng có chức năng điều khiển và kết nối các ổ cứng với nhau, giúp tăng tốc độ truy xuất dữ liệu, bảo vệ an toàn dữ liệu trên ổ cứng.
Có nhiều loại card RAID Controller tương thích với chuẩn ổ cứng máy chủ, ổ cứng server thông dụng như HDD SAS, HDD SATA.

![image](https://user-images.githubusercontent.com/83684068/124863687-c1fab200-dfe1-11eb-9f59-d149bd9c868f.png)

Cụ thể hơn, RAID card hỗ trợ một số các chức năng chính như sau ( áp dụng cho RAID 1, 5, 6, 10, 50 và 60):
- **Fault Tolerance:** đảo bảm quá trình hoạt động của dữ liệu được nguyên vẹn khi có lỗi xảy ra ở ổ đĩa hoặc hệ thống
- **Consistency Check:** kiểm tra tính toàn vẹn của dữ liệu, làm được nhờ các ổ phụ (redundancy)
- **Hot Spares:** một hot spare drive sẽ được sử dụng để thay thế cho ổ cứng lỗi trong trường hợp sự cố xảy ra
- **Data Rebuild:** hỗ trợ tái dựng lại data từ drive xảy ra lỗi sang drive mới
- **Virtual Drive Read, Write Policies:** sẽ được làm rõ hơn tại phần sau
- **Drive Striping:** cho phép phân chia và lưu các khối dữ liệu tại các ổ cứng khác nhau, đảm bảo khi nhiều quá trình truy cập không bị conflict
- **Drive Mirroring:** tạo 100% sao lưu cho dữ liệu, như vậy dữ liệu sẽ được toàn vẹn khi một trong các ổ cứng xảy ra lỗi 

## Virtual Drive Read and Write Policies
Khi một ổ đĩa ảo (virtual drive) được tạo ra, cần xác định các chính sách đọc và ghi dữ liệu để từ đó chuẩn hóa các thao tác đọc và ghi dữ liệu của ổ đĩa đó. 

### Data Read Policies
RAID controller hỗ trợ các mode đọc dữ liệu sau:
- **Read-ahead mode (Rahead)**
  - Khi mode này được bật, RAID controller sẽ lưu vào cache dữ liệu phía sau của dữ liệu đang được đọc để truy cập nhanh hơn.
  - Chính sách này giảm tải số lần tìm kiếm của ổ đĩa và rút ngắn thời gian đọc.
- **Non-read-ahead (NoRahead)**
  - Khi sử dụng mode này, RAID controller sẽ không đọc trước dữ liệu.
  - Thay vào đó, nó chỉ đọc dữ liệu từ ổ đĩa ảo khi nhận được lệnh đọc dữ liệu. 

### Data Write Policies
RAID controler hỗ trợ các mode ghi dữ liệu sau:
- **Write-back**
  - Khi mode này được sử dụng, dữ liệu sẽ được ghi trực tiếp vào cache.
  - Sau đó, controller sẽ cập nhật dữ liệu từ cache vào ổ cứng.
  - Tốc độ ghi dữ liệu về tổng thể sẽ cao hơn vì ghi vào cache nhanh hơn ghi vào ổ cứng.
  - Sau khi cache nhận được tất cả dữ liệu cần truyền, controller báo hiệu cho máy chủ rằng quá trình truyền dữ liệu đã hoàn tất.
- **Write-through**
  - Khi mode này được sử dụng, RAID controller sẽ ghi dữ liệu trực tiếp vào ổ đĩa ảo mà không cần thông qua cache.
  - Sau khi hệ thống của ổ đĩa nhận được tất cả dữ liệu cần truyền, controller báo hiệu cho máy chủ rằng quá trình đã hoàn tất.
  - Nhược điểm là tốc độ ghi thấp.
- **BBU-related write-back**
  - khi không có nguồn điện trong ổ cứng, BBU hỗ trợ lưu giữ data ở cache trong vòng 72h cho tới khi hệ thống hoạt động trở lại, và dữ liệu sẽ được ghi trở lại ổ cứng.
  - Mode này liên quan đến hai trường hợp:
  - Nếu BBU của RAID controller có sẵn và hoạt động bình thường, chính sách ghi sẽ được áp dụng theo write-back mode.
  - Nếu BBU của RAID controller không có hoặc bị lỗi, chính sách ghi sẽ được áp dụng theo write-through mode. 
