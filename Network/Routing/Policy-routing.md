# PBR (Policy Based Routing)
Là một giải pháp giúp người quản trị mạng có thể điều khiển đường đi của gói tin bằng cách quy định các chính sách, giúp phân luồng và quản lý dữ liệu hiệu quả hơn trong quá trình hoạt động.

Việc phân luồng này có thể dựa trên nhiều nhu cầu, ví dụ dựa dựa vào địa chỉ IP source, theo loại giao thức (telnet, http,…), theo kích thước gói,...

**Một số những lợi ích**
- **Source-Based Transit Provider Selection:** nhóm user khác nhau sẽ đi qua các ISP khác nhau
- **QoS:** phân loại traffic và dành độ ưu tiên khác nhau 
- **Cost Savings:** phân loại traffic theo các tuyến high-bandwidth, low-cost
- **Load Balancing:** cân bằng tải, giả sử đến cùng một đích sẽ load qua nhiều line khác nhau, khác với định tuyến truyền thống
- **Performance Improvement:** với các line có MTU khác nhau, có thể chọn line có MTU hợp lý nhất để tránh phân mảnh

## Trên Linux
Một thiết bị linux đóng vai trò làm router có thể quản lý nhiều bảng định tuyến, trong mỗi bảng lại có nhiều rule để áp đặt cho các mạng IP.

Các bảng định tuyến được quản lý tại
     
    etc/iproute2/rt_table
     
Thực hiện add các định tuyến vào table đã được tạo
  
    ip route add default via 192.168.1.1 table test
    
Các rule để tuỳ chỉnh traffic, ví dụ như gói tin có header `10.0.0.23` phải tuân theo bảng định tuyến `test` và bị forward tới `192.168.1.1`.

    ip rule add from 10.0.0.23 table test
