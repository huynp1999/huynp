# HAProxy (High Availability Proxy)
Là một công cụ cân bằng tải TCP/HTTP và giải pháp proxy mã nguồn mở phổ biến.

**High Availability** có nghĩa là “Độ sẵn sàng cao“, luôn luôn sẵn sàng phục vụ và người sử dụng sẽ không bị gián đoạn trong quá trình sử dụng.
Để đảm bảo được điều đó, tối thiểu có một cặp máy, thiết bị chạy song song liên tục liên lạc (health check) và từ động thay thế cho nhau.

**Load Balancing** (Cân bằng tải) là một phương pháp phân phối luồng lưu lượng trên nhiều máy tính để có thể sử dụng tối đa tài nguyên, tối ưu thời gian đáp ứng, giảm độ trễ và đảm bảo tính chịu lỗi.

HAProxy thường được kết hợp với [**KeepAlived**](https://github.com/huynp1999/huynp/new/master/Network/Keepalived.md) để tạo thành một giải pháp hiệu quả với giá thành thấp.

## Các kiểu cân bằng tải
### 1. Không cân bằng tải
![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i1.png)

Trong một môi trường ứng dụng web đơn giản không hỗ trợ cân bằng tải, người dùng kết nối trực tiếp đến ứng dụng web, tại yourdomain.com.
Nếu máy chủ web (duy nhất) bị lỗi, người dùng sẽ không thể truy xuất đến website. Ngoài ra, nếu nhiều người dùng cùng truy xuất đến webserver cùng lúc nó sẽ không thể xử lý kịp lượng tải gây ra trễ hoặc không thể kết nối đến web.

### 2. Cân bằng tải Layer 4
![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i2.png)

Cách đơn giản nhất để cân bằng lưu lượng mạng giữa nhiều backend server là dùng cân bằng tải layer 4 (transport layer).
Cân bằng tải theo cách này sẽ chuyển hướng lưu lượng người dùng dựa trên IP range và port (vd: nếu 1 request đến http://yourdomain.com/anything, lưu lượng sẽ được chuyển hướng đến backend mà xử lý tất cả các request cho yourdomain.com trên port 80).

### 3. Cân bằng tải layer 7
![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i3.png)

Tại layer 7 cho phép load balancer chuyển hướng request đến các máy chủ backend khác nhau dựa trên nội dung request. Chế độ cân bằng tải này cho phép chạy nhiều máy chủ ứng dụng web dưới cùng domain và port.

Trong ví dụ này, nếu người dùng yêu cầu yourdomain.com/blog, họ sẽ được chuyển hướng đến blog-backend, là tập các máy chủ chạy ứng dụng blog.
Các request khác được chuyển hướng đến web-backend, mà có thể sẽ chạy các ứng dụng khác. (cả 2 backend dùng cùng máy chủ database)

## Các thuật toán trong cân bằng tải
### 1. Round Robin
Là thuật toán mặc định của NGINX, và không cần cấu hình thêm trong block `http`

Các request sẽ được luân chuyển liên tục giữa các server 1:1, điều này sẽ giảm tải cho các hệ thống có lượng request lớn.
    
    http {
        upstream backends {
            server 10.10.20.10:80;
            server 10.10.20.20:80;
        }

### 2. Weighted load balancing
Cho phép phân ra được khối lượng xử lý giữa các server.

Ví dụ: có 2 server dùng để load balancing, cứ 5 request đến thì 3 rq dành cho server `.10`, 2 rq dành cho server `.20`
    
    http {
        upstream backends {
            server 10.10.20.10:80 weight=3;
            server 10.10.20.20:80 weight=2;
        }

### 3. Least Connection
Đây là thuật toán nâng cấp của round robin và weighted load balancing, thuật toán này sẽ giúp tối ưu hóa cân bằng tải cho hệ thống.

Least Connection sẽ chuyển request đến cho server đang xử lý ít việc hơn.
Thích hợp với các hệ thống mà có các session cần duy trì trong thời gian dài, mềm dẻo và tránh đi theo các quy tắc định sẵn.
   
    http {
        upstream backends {
            least_conn;
            server 10.10.20.10:80;
            server 10.10.20.20:80;
        }

### 4. Health Check
Health check đkiểm tra định kì 1 máy chủ trong backend có sẵn sàng xử lý request hay không. Nếu máy chủ backend gặp sự cố và không thể qua kiểm tra health check, nó sẽ được tự động vô hiệu hóa trong backend. lưu lượng sẽ không được chuyển hướng đến cho đến khi nó sẵn sàng. Nếu tất cả các máy chủ trong backend lỗi, dịch vụ sẽ không sẵn sàng cho đến khi ít nhất 1 máy chủ trong backend sẵn sàng phục vụ.
   
    http {
        upstream backends {
            server 10.10.20.10:80;
            server 10.10.20.20:80 max_fails=3 fail_timeout=5s;
            server 10.10.20.20:80;
        }
      
## Kết hợp với KeepAlived
Trong một hệ thống dùng chỉ 1 load balancer để điều khiển traffic tới nhiều backend server, khi load balancer bị lỗi dẫn đến việc dữ liệu sẽ bị ứ đọng và downtime. Keepalived được dành cho giải quyết vấn đề này.

![](https://github.com/meditechopen/meditech-thuctap/blob/master/ThaoNV/HAProxy%20%2B%20KeepAlive/images/i4.gif)

Ở ví dụ trên, khi có nhiều load balancer (1 active và một hoặc nhiều passive). Khi người dùng kết nối đến một server thông qua IP public của active load balancer, nếu active server fail, phương thức failover sẽ phát hiện và tự động gán IP tới 1 passive server khác.
