# Ba loại cloud storage
Mỗi giải pháp lưu trữ đều đi kèm với ưu và nhược điểm riêng, và việc tìm hiểu là cần thiết để chọn ra một giải pháp phù hợp tuỳ theo các trường hợp sử dụng khác nhau.

## Object storage - Cloud storage
![image](https://user-images.githubusercontent.com/83684068/127800228-0f8ea22f-3661-47dd-b36d-13350012cdeb.png)

Loại hình lưu trữ dành cho dữ liệu nhị phân, blob và bất kỳ các loại dữ liệu phi cấu trúc.
Khi sử dụng kiểu lưu trữ này, các đối tượng dữ liệu được lưu giữ trong một kho lưu trữ duy nhất mà không có cấu trúc phân cấp hoặc lồng nhau.

Mỗi object (đối tượng) trong bộ nhớ sẽ chứa tất cả các khối dữ liệu (data block) tạo nên một file, cùng với đó là các metadata nào được liên kết.
Dữ liệu này sau đó được đặt vào một vùng lưu trữ, một không gian địa chỉ phẳng. Khi cần truy xuất dữ liệu, nó được định vị bởi một mã định danh duy nhất được gán cho đối tượng đó.

- **Ưu điểm:** Hữu ích với metadata được đính kèm vào file.
Metadata này có thể được tạo tự động hoặc do người dùng xác định, cho phép thực hiện nhiều kiểu phân tích.
Một lợi ích khác là khả năng lưu trữ dữ liệu một cách linh hoạt mà không cần quan tâm đến hệ thống phân cấp.
Điều này cho phép khả năng sử dụng tài nguyên lưu trữ ở mức tối đa cũng như việc mở rộng dễ dàng hơn bằng cách chỉ cần thêm node vào trong cụm storage.

- **Nhược điểm:** Chậm hơn so với hệ thống lưu trữ tệp hoặc khối.
Điều này làm cho nó trở thành một lựa chọn tồi cho các ứng dụng hoặc khối lượng công việc yêu cầu độ trễ thấp.

## File storage
![image](https://user-images.githubusercontent.com/83684068/127801528-f70f8e32-7ebf-4d1c-a8ca-a830a58a120d.png)

File storage là một phương pháp lưu trữ dữ liệu theo hệ thống phân cấp.
File storage là phương pháp lưu trữ tiêu chuẩn mà hầu hết người dùng quen thuộc.
Dữ liệu được lưu trữ ở định dạng giống như dữ liệu được truy xuất.
File storage được truy cập thông qua giao thức Server Message Block (SMB) trên Windows hoặc giao thức Network File System (NFS) trên Linux.

SMB và NFS là các giao thức cho phép lưu trữ file trên server theo cách giống như dữ liệu được lưu trữ trên client.
Cho phép gắn kết tất cả hoặc một phần hệ thống tệp của mình và chia sẻ quyền truy cập trên nhiều thiết bị khách.
Các giao thức này cũng thường được sử dụng với các thiết bị Network-Attached Storage (NAS).

Thiết bị NAS thường được sử dụng để mở rộng quy mô lưu trữ file và cũng có thể được sử dụng dưới dạng bản sao lưu NAS để cung cấp dự phòng.

- **Ưu điểm:** Quen thuộc với người dùng với hệ thống file phân cấp.
File storage phù hợp với mục đích sử dụng văn phòng hoặc thư mục, lưu trữ lượng dữ liệu có cấu trúc nhỏ hoặc lưu trữ file có yêu cầu tính đảm bảo cao.

- **Nhược điểm:** tính linh hoạt thấp và ít tùy biến hơn so với block storage.

## Block storage
![image](https://user-images.githubusercontent.com/83684068/127802805-e7c72c6e-fc4b-4c27-9dbf-04dcf7897f79.png)

Block storage là một phương pháp lưu trữ trên thiết bị lưu trữ cấp thấp.
Các thiết bị block storage được quản lý như một cụm các đơn vị được gọi là khối.
Trong mỗi khối sẽ lưu trữ một phần của một file. Khối này sau đó được gán một địa chỉ duy nhất, cho phép các file được trải rộng trên nhiều máy để sử dụng lưu trữ hiệu quả hơn.

Khi muốn truy xuất một tệp, một request được thực hiện với thiết bị block storage.
Sau khi request được dịch thành block request (yêu cầu khối), file sẽ được tập hợp lại sẽ được trả về máy, thiết bị block storage như vậy sẽ tương tự như một ổ cứng tiêu chuẩn.

- **Ưu điểm:** Các hoạt động có độ trễ thấp.
Block storage cũng hỗ trợ các loại filesystem bao gồm NTFS, XFS hoặc ext4. Các block (khối) cũng thường được sao chép trên các thiết bị, đảm bảo rằng dữ liệu có thể khôi phục được nếu một thiết bị bị hỏng.

- **Nhược điểm:** có thể sẽ không mở rộng được quy mô sau khi đạt đến giới hạn được phân bổ của bộ nhớ


## File Storage vs Block Storage


| File storage | Block storage |
| --- |:------|
|   Quen thuộc của người dùng với hệ thống file phân cấp  | Hỗ trợ các loại filesystem bao gồm NTFS, XFS hoặc ext4.  |
|   Ít tùy biến hơn  |   tính linh hoạt cao hơn, có thể sửa đổi để tăng hiệu suất   |
|   Phù hợp với mục đích sử dụng văn phòng hoặc thư mục, lưu trữ lượng dữ liệu có cấu trúc nhỏ hoặc lưu trữ file có yêu cầu tính đảm bảo cao.  | Phù hợp cho cơ sở dữ liệu, lưu trữ dữ liệu của các ứng dụng và các hệ thống ảo hóa.    |

## Object Storage vs Block Storage

| Object storage | Block storage |
| --- |:-----|
|  Bao gồm metadata   |  Không có metadata nên sẽ ko có context cho file    |
|  Khả năng mở rộng dễ dàng hơn, chỉ cần thêm nhiều nút hơn vào cụm lưu trữ của mình.   |  Tùy thuộc vào dịch vụ block mà có thể không mở rộng được sau khi đạt đến giới hạn phân bổ của bộ nhớ  |
|  Mặc dù tínnh linh hoạt và khả năng tùy chỉnh cao hơn, nhưng tốc độ lại chậm hơn vì bất kỳ thay đổi nhỏ đều yêu cầu viết lại toàn bộ object và như vậy sẽ cần làm việc với nhiều đối tượng hơn   |   Tốc độ nhanh hơn vì block storage cho phép sửa đổi tuỳ theo các thành phần của file |
| Phù hợp với lưu trữ dữ liệu phi cấu trúc, lưu trữ tập dữ liệu lớn và lưu trữ dữ liệu với các chính sách bảo quản, xóa và lưu giữ dữ liệu tùy chỉnh.    | Phù hợp các ứng dụng và quy trình làm việc dựa vào hiệu suất lưu trữ và dữ liệu không yêu cầu phân tích metadata     |

![image](https://user-images.githubusercontent.com/83684068/127823038-1d0b66d4-e215-4f6f-b736-f2454889110a.png)
