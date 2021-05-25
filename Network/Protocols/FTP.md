# FTP (File Transfer Protocol)
Là một giao thức chuyển file giữa những máy tính với nhau qua mạng lưới internet hoặc nội bộ, v.v.
Hoạt động dựa trên mô hình client-server, với một FTP client trên máy tính người dùng tạo ra một kết nối đến một FTP server để gửi và lấy các tập tin đến và đi từ các máy chủ. 

## Mô hình hoạt động
FTP cần tới 2 kênh kết nối TPC trong quá trình giao tiếp giữa client và server

![Alt](https://news.cloud365.vn/wp-content/uploads/2020/01/FTP1.png)

- **Control connection (port 21)**
  - Được tạo ra khi phiên kết nối được thiết lập.
  - Nó được duy trì trong suốt phiên làm việc và chỉ cho các thông tin điều khiển đi qua ví dụ như lệnh và trả lời. Nó không được sử dụng để gửi dữ liệu.
  - Sử dụng Protocol Interpreter (PI), thành phần quản lý kênh điều khiển, phát và nhận lệnh và trả lời.
- **Data connection (port 20)**
  - Kết nối này dành riêng cho việc một gửi và nhận dữ liệu giữa server và client.
  - Khi hoàn tất việc một phiên truyền dữ liệu, kết nối được hủy bỏ.
  - Sử dụng Data Transfer Process (DTP), chịu trách nhiệm gửi và nhận dữ liệu giữa client và server.
 
![Alt](https://news.cloud365.vn/wp-content/uploads/2020/01/Screenshot_2.png)

#### Các tiến trình trên 2 kênh kết nối
Bởi FTP chia ra 2 kênh riêng biệt, nên mỗi kênh cũng có một thành phần giao thức riêng:
- **Server Protocol Interpreter**
  - Lắng nghe yêu cầu kết nối hướng từ user và khởi tạo tại server
  - Khi kết nối đã được thiết lập, nó nhận lệnh, reponse và quản lí tiến trình truyền dữ liệu.
- **Server Data Transfer Process**
  - Làm nhiệm vụ gửi hoặc nhận file từ bộ phận User-DTP.
  - Server DTP vừa làm nhiệm vụ thiết lập và lăng nghe yêu cầu kết nối kênh dữ liệu từ user.
  - Tương tác với dữ liệu trên hệ thống server hoặc của client để đọc và chép file.

Ngoài ra, bên phía người dùng còn có 1 thành phần thứ ba là giao diện người dùng
- **User Interface**
  - Là chương trình cung cấp giao diện xử lí cho người dùng.
  - Cho phép người dùng điều khiển, theo dõi và tương tác với phiên FTP

## Kênh dữ liệu
Để tạo ra kênh dữ liệu, FTP sử dụng 2 phương thức khác nhau
- **Normal (Active) Data Connections (mặc định)**
  - Phương thức khởi tạo kết nối dữ liệu thông thường hay kết nối dạng chủ động.
  - Phía Server-DTP tạo kênh dữ liệu bằng cách mở một cổng kết nối tới User-DTP. Server sử dụng cổng 20 dành riêng cho kết nối dữ liệu
- **Passive Data Connections**
  - Phương thức khởi tạo kết nối bị động.
  - Server sẽ lắng nghe yêu cầu từ client, và Client có thể tuỳ chọn sử dụng một cổng khác cho Data Connection

## Phương thức truyền dữ liệu
Khi Client-DTP và Server-DTP thiết lập xong kênh dữ liệu, FTP có ba phương thức truyền dữ liệu:
- Stream mode
 - Dữ liệu truyền đi liên tiếp dưới dạng các byte không cấu trúc.
 - Đẩy luồng dữ liệu qua kết nối TCP tới phía nhận.
 - Không có Header nên việc vận truyển dễ dàng hơn
- Block mode
  - Phương thức này mang tính quy chuẩn hơn.
  - Dữ liệu được chia thành nhiều khối nhỏ và đóng gói thành các FTP block.
  - Được gắn Header để theo dõi dữ liệu trên đuờng truyền
- Compressed mode
  - Sử dụng kỹ thuật nén
  - Có tác dụng phát hiện và xử lí các đoạn lặp trong dữ liệu nhằm giảm bớt lưu lượng truyền tải

 
