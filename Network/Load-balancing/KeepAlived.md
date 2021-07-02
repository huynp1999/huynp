# KeepAlived
KeepAlived giải quyết vấn đề sự cố trên một máy chủ đảm nhiệm cân bằng tải.

Để làm được điều này, KeepAlive thao tác với LVS (Linux Virtual Server) cho phép thêm hoặc xóa các máy chủ thực dựa trên health check. Có thể tạo một hay nhiều Virtual IP để liên kết các máy chủ mở rộng hệ thống Load Balancing.

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
      
## LVS (Linux Virtual Server)
LVS (Linux Virtual Server) là một thành phần được thêm vào kernel của linux để hỗ trợ tính năng load balancing. LVS hoạt động như network bridge (NAT) để cân bằng tải các luồng TCP/UDP.

Các thành phần của LVS router:
- WAN interface
- LAN interface
- Linux kernel

Các thành phần của LVS:
- VIP: Virtual IP, dùng để client truy cập
- Real server: các server có nhiệm vụ nhận requests từ client
- Server pool: Một khu chứa các real servers
- Virtual server: Điểm truy cập tới server pool
- Virtual Service: TCP/UDP service gắn liền với VIP
- VRRP: Giao thức dùng trong việc chuyển đổi giữa các máy dự phòng/ảo hóa.

