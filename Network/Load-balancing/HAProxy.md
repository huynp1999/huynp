# HAProxy (High Availability Proxy)
Là một công cụ cân bằng tải TCP/HTTP và giải pháp proxy mã nguồn mở phổ biến.

**High Availability** có nghĩa là “Độ sẵn sàng cao“, luôn luôn sẵn sàng phục vụ và người sử dụng sẽ không bị gián đoạn trong quá trình sử dụng.
Để đảm bảo được điều đó, tối thiểu có một cặp máy, thiết bị chạy song song liên tục liên lạc (health check) và từ động thay thế cho nhau.

**Load Balancing** (Cân bằng tải) là một phương pháp phân phối luồng lưu lượng trên nhiều máy tính để có thể sử dụng tối đa tài nguyên, tối ưu thời gian đáp ứng, giảm độ trễ và đảm bảo tính chịu lỗi.

HAProxy thường được kết hợp với [**KeepAlived**](https://github.com/huynp1999/huynp/blob/master/Network/Load-balancing/KeepAlived.md) để tạo thành một giải pháp hiệu quả với giá thành thấp.

## Các kiểu cân bằng tải
### 1. Không cân bằng tải
![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i1.png)

Trong một môi trường ứng dụng web đơn giản không hỗ trợ cân bằng tải, người dùng kết nối trực tiếp đến ứng dụng web, tại yourdomain.com.
Nếu máy chủ web (duy nhất) bị lỗi, người dùng sẽ không thể truy xuất đến website. Ngoài ra, nếu nhiều người dùng cùng truy xuất đến webserver cùng lúc nó sẽ không thể xử lý kịp lượng tải gây ra trễ hoặc không thể kết nối đến web.

### 2. Cân bằng tải layer 4
![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i2.png)

Cách đơn giản nhất để cân bằng lưu lượng mạng giữa nhiều backend server là dùng cân bằng tải layer 4 (transport layer).
Cân bằng tải theo cách này sẽ chuyển hướng lưu lượng người dùng dựa trên IP range và port (vd: nếu 1 request đến http://yourdomain.com/anything, lưu lượng sẽ được chuyển hướng đến backend mà xử lý tất cả các request cho yourdomain.com trên port 80).

### 3. Cân bằng tải layer 7
![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i3.png)

Tại layer 7 cho phép load balancer chuyển hướng request đến các máy chủ backend khác nhau dựa trên nội dung request. Chế độ cân bằng tải này cho phép chạy nhiều máy chủ ứng dụng web dưới cùng domain và port.

Trong ví dụ này, nếu người dùng yêu cầu yourdomain.com/blog, họ sẽ được chuyển hướng đến blog-backend, là tập các máy chủ chạy ứng dụng blog.
Các request khác được chuyển hướng đến web-backend, mà có thể sẽ chạy các ứng dụng khác. (cả 2 backend dùng cùng máy chủ database)

### 4. Khác biệt giữa load balancer layer 4 và layer 7
- **Layer 4**
  - Hoạt động ở lớp transport, quản lý lưu lượng truy cập dựa trên thông tin mạng như port và giao thức mà không quan tâm tới nội dung gói tin.
  - Layer 4 load balancer đơn giản chỉ chuyển tiếp gói dữ liệu mạng đến và đi mà không kiểm tra nội dung trong đó.
  - Sử dụng các giao thức TCP, UDP
- **Layer 7**
  - Hoạt động ở lớp application, quan tâm trực tiếp tới nội dung trong gói tin (URL, cookie,...) để từ đó đưa ra các quyết định cân bằng tải.
  - Các quyết định được đưa ra bởi các giao thức như HTTP, SMTP.
## Kết hợp với KeepAlived
Trong một hệ thống dùng chỉ 1 load balancer để điều khiển traffic tới nhiều backend server, khi load balancer bị lỗi dẫn đến việc dữ liệu sẽ bị ứ đọng và downtime. Keepalived được dành cho giải quyết vấn đề này.

![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i4.gif)

Ở ví dụ trên, khi có nhiều load balancer (1 active và một hoặc nhiều passive). Khi người dùng kết nối đến một server thông qua IP public của active load balancer, nếu active server fail, phương thức failover sẽ phát hiện và tự động gán IP tới 1 passive server khác.
