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
    

#Lab
Từ Router Linux ping được tới Linux-Router qua 2 interface (default gateway) khác nhau, thay vì chỉ 1 đường định tuyến duy nhất theo mặc định.

Đạt được bằng cách áp dụng các mạng vào trong rule table.

## Cấu hình

1. Đặt IP tĩnh như theo topo

| Router  | ens3 | ens4 |
| ------------- |:-------------:|:-------------:|
| Router 1     | 10.2.13.1     | 10.2.12.1 |
| ISP 1    | 10.2.12.2    | 10.2.24.2 |
| ISP 2     | 10.2.13.3    | 10.2.34.3 |
| Router 4     | 10.2.34.4    | 10.2.24.4 |

2. Trên ISP1 và ISP2 cấu hình cho phép forward gói tin

       echo "1" > /proc/sys/net/ipv4/net_forward
       
3. Định tuyến cho Router Linux 4

       ip route add 10.2.13.0/24 via 10.2.34.3 dev ens3
       ip route add 10.2.12.0/24 via 10.2.24.2 dev ens4
 
4. Định tuyến, tạo default gateway tại Router Linux 1
- Do có hai đường nên cần tạo 2 table để áp đặt cho các mạng
     
       echo "200 test1" >> etc/iproute2/rt_table
       echo "201 test2" >> etc/iproute2/rt_table

- Cấu hình 
  - Default gateway 1

        ip route add 10.2.13.0/24 dev ens3 src 10.2.13.1 table test1
        ip route add default via 10.2.13.3 dev ens3 table test1
        ip rule add from 10.2.13.1/24 table test1
       
  - Default gateway 2
       
        ip route add 10.2.12.0/24 dev ens4 src 10.2.12.1 table test2
        ip route add default via 10.2.12.2 dev ens4 table test2
        ip rule add from 10.2.12.1/24 table test2

5. Ping kiểm tra 2 đường từ Router Linux 4



