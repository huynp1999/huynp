# KeepAlived
KeepAlived giải quyết vấn đề sự cố trên một máy chủ đảm nhiệm cân bằng tải.

Để làm được điều này, KeepAlive thao tác với LVS (Linux Virtual Server) cho phép thêm hoặc xóa các máy chủ thực dựa trên health check. Có thể tạo một hay nhiều Virtual IP để liên kết các máy chủ mở rộng hệ thống Load Balancing.

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

