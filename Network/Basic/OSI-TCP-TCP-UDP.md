# Mô hình OSI
Mô hình OSI ra đời nhằm thống nhất hạ tầng mạng của các nhà phát triển với nhau.

<img src="https://cehv.com/wp-content/uploads/2021/03/osi-model-7-layers-1024x734-1.jpg" alt="drawing" width="700"/>

Mô hình OSI gồm 7 lớp, trong đó, 4 lớp đầu tiên là quan trọng đối với **networking**, 3 lớp tiếp theo là về **applications**

1. **Lớp vật lý (Physical)**
- Đại diện cho những thứ như mức điện áp, thời gian, đầu nối vật lý, v.v.
2. **Lớp liên kết dữ liệu (Data Link)**
- Có chức năng đảm bảo dữ liệu được định dạng theo đúng cách, có khả năng sửa lỗi và vận truyển dữ liệu tin cậy
- Ethernet frame và MAC address nằm lại lớp này 
3. **Lớp mạng (Network)**
- Có chức năng điều khiển kết nối và định tuyến (routing)
- IPv4 và IPv6 nằm tại lớp này
4. **Lớp giao vận (Transport)**
- Có chức năng quản lý việc truyển tải các segment
- UDP và TCP nằm tại lớp này
5. **Lớp phiên (Session)**
- Có chức năng thiết lập và quản lý các phiên kết nối giữa 2 đầu cuối
- Ví dụ như khi một người dùng truy cập vào 1 website cũng đồng nghĩa với 1 phiên kết nối từ user tới webserver
6. **Lớp trình diễn (Presentation)**
- Có chức năng định dạng và cấu trúc cho dữ liệu để lớp **Application** có thể hiểu được
7. **Lớp ứng dụng (Application)**
- Gồm các ứng dụng như trình duyệt web (HTTP), E-mail, FPT, v.v.

#### Ví dụ quá trình truyền dữ liệu trong thực tế theo mô hình OSI
1. Khi người dùng gõ một tên miền vào URL, máy tính sẽ gửi một bản tin tới webserver yêu cầu *trang web* hiện tại, đây chính là giao thức HTTP
2. Lớp trình diễn sẽ cấu trúc bản tin theo một định dạng xác thực
3. Lớp phiên tạo ra các phiên kết nối
4. Giao thức TCP tạo ra các **Segment** cho phép trang web đó tới tay người dùng một cách toàn vẹn
5. Tại đây **IP Packet** sẽ được tạo ra, trong đó bao gồm địa chỉ IP đầu cuối, giao thức vận truyển của lớp Transport và dữ liệu của 3 lớp ứng dụng
6. Packet tiếp tục được đóng vào một **Ethernet Frame**, trong này bao gồm thêm địa chỉ MAC đầu cuối
7. Cuối cùng tất cả được chuyển thành các bit truyền đi bằng tín hiệu điện
# Mô hình TCP/IP
Có cùng ý tưởng và chức năng tương tự như mô hình OSI nhưng với một số lớp được gộp lại làm một.

<img src="https://fiberbit.com.tw/wp-content/uploads/2013/12/TCP-IP-model-vs-OSI-model.png" alt="drawing" width="600"/>

TCP/IP gồm 4 lớp:
1. **Network Interface**
- Được gộp lại từ 2 lớp cuối cùng của OSI, là lớp vật lý và lớp liên kết dữ liệu
- Tầng này mô tả về các đặc điểm vật lý của các kết nối, điều khiển truy cập và định dạng dữ liệu để truyền tải.
2. **Network**
- Tương tự như lớp 3 mạng của OSI
3. **Transport**
- Tương tự như lớp 4 giao vận của OSI
4. **Application**
- Được gộp lại từ 3 lớp đầu tiên của OSI, là lớp ứng dụng, trình diễn và phiên
- Cung cấp các ứng dụng cho các hoạt động trên internet như duyện web, truyền file,... và xử lý sự cố

# TCP và UDP
- #### Giống nhau:
  - TCP và UDP là hai giao thức cốt lõi nằm ở tầng giao vận (Transport) thuộc giao thức TCP/IP có khả năng gửi tin đến các máy chủ khác thông qua Internet.
  - Cả hai đều được xây dựng trên giao thức IP. Nói cách khác, dù có dùng TCP hay UDP, cá gói tin đều được gửi đến một địa chỉ IP.
  - Những gói tin được xử lý như nhau, đều từ máy tính cá nhân qua các router trung gian và đến điểm đích.
- #### Điểm khác nhau:

| TCP (Transmission Control Protocol)| UDP (User Datagram Protocol) |
| ------------- |:-------------:|
| Hướng kết nối  |Không kết nối     |
|   Tin cậy  | Không tin cậy     |
| Đảm bảo tính toàn vẹn |  Không đảm bảo
| Tốc độ thấp hơn| Tốc  độ  nhanh hơn
| Download, chia sẻ file| VoIP, streaming    |

Nhận xét:
- TCP đảm bảo tính toàn vẹn của dữ liệu, nhưng tốn nhiều thời gian hơn để kiểm tra đầy đủ thông tin từ thứ tự dữ liệu cho đến việc giám sát, khắc phục lỗi trong khi truyền.
- Trái với TCP, UDP có thấy tốc độ truyền tải nhanh hơn nhưng lại không đảm bảo được dữ liệu có đến được đích hay không.
- Do vậy mà header UDP cũng đơn giản và bé hơn TCP (8 và 20 byte).

