# ARP
Lệnh dùng để xem hoặc thêm nội dung của bảng Kernel ARP.

Hiển thị các giá trị hiện tại trong bảng ARP
    
    arp -a
        
Thêm 1 địa chỉ IP vào bảng ARP với địa chỉ IP và địa chỉ MAC.
    
    arp -s [ipaddress] -i eth_addr [MAC address]

Xóa địa chỉ IP khỏi ARP table

    arp -d [ip]        

# traceroute
Xác định đường đi được sử dụng đến đích 1 gói tin.
Trong Linux, traceroute sử dụng gói UDP ở port (33434-33534).

Cài đặt:

    sudo apt install traceroute 

Cú pháp:

    traceroute [domain_name/ipaddress]

    traceroute 24h.com.vn
    traceroute to 24h.com.vn (103.151.240.80), 30 hops max, 60 byte packets
     1  _gateway (192.168.18.1)  0.609 ms  0.818 ms  0.787 ms
     2  10.56.239.2 (10.56.239.2)  2.174 ms static.vnpt-hanoi.com.vn (203.210.148.18)  2.410 ms static.vnpt.vn (113.160.73.209)  1.336 ms
     3  static.vnpt-hanoi.com.vn (123.25.27.93)  2.665 ms 10.254.2.64 (10.254.2.64)  3.961 ms static.vnpt-hanoi.com.vn (123.25.27.93)  2.295 ms
     4  localhost (27.68.194.106)  2.571 ms  10.381 ms  2.504 ms
     5  localhost (27.68.228.38)  3.799 ms localhost (27.68.228.26)  2.446 ms *
     6  static.vnpt.vn (113.171.27.226)  24.459 ms  22.905 ms *
     7  static.vnpt.vn (113.171.7.221)  25.674 ms static.vnpt.vn (113.171.27.206)  25.099 ms static.vnpt.vn (113.171.7.221)  24.367 ms
     8  static.vnpt.vn (113.171.45.54)  27.858 ms  24.309 ms static.vnpt.vn (113.171.45.34)  23.139 ms
     9  static.vnpt.vn (113.171.48.78)  22.636 ms 172.16.30.126 (172.16.30.126)  23.952 ms 172.16.30.130 (172.16.30.130)  25.442 ms
    10  172.16.30.126 (172.16.30.126)  26.295 ms 172.16.30.122 (172.16.30.122)  22.520 ms 103.151.240.80 (103.151.240.80)  22.964 ms !X

   
# mtr (My Traceroute)
`mtr` là sự kết hợp giữa `ping` và `traceroute`

`mtr` hoạt động bằng cách gửi các gói tin ICMP bằng cách tăng giá trị TTL để tìm tuyến đường giữa nguồn và đích.

Ví dụ:
  - ping 5 gói tin lần đến 24h.com.vn và ghi kết quả vào file `report`

        mtr -r -c 5 24h.com.vn > report

        Start: 2021-06-10T11:12:12+0700
        HOST: huyComputer                 Loss%   Snt   Last   Avg  Best  Wrst StDev
          1.|-- _gateway                   0.0%     5    0.3   0.4   0.3   0.9   0.3
          2.|-- static.vnpt-hanoi.com.vn   0.0%     5    1.7   2.4   1.7   4.0   0.9
          3.|-- static.vnpt-hanoi.com.vn   0.0%     5    2.2   2.2   1.9   2.4   0.2
          4.|-- static.vnpt.vn             0.0%     5    2.1   1.9   1.5   2.1   0.3
          5.|-- ???                       100.0     5    0.0   0.0   0.0   0.0   0.0
          6.|-- static.vnpt.vn             0.0%     5   29.7  30.9  28.7  37.0   3.5
          7.|-- static.vnpt.vn             0.0%     5   28.2  28.6  28.0  29.0   0.4
          8.|-- static.vnpt.vn             0.0%     5   28.5  28.7  28.1  29.4   0.5
          9.|-- 172.16.30.122              0.0%     5   35.5  35.5  35.4  35.6   0.1
         10.|-- 103.151.240.80             0.0%     5   28.9  28.6  28.0  28.9   0.4

Các trường thông tin:
- `Loss%` hiển thị % số gói bị mất tại mỗi bước nhảy
- `Last` độ trễ của gói tin cuối cùng được gửi
- `AVG` độ trễ trung bình của tất cả các gói
- `Best` hiển thị thời gian quay vòng tốt nhất cho gói tin đến máy chủ lưu trữ này (RTT ngắn nhất)
- `Wrst` hiển thị thời gian quay vòng tệ nhất cho mỗi gói tin đến máy chủ lưu trữ (RTT dài nhất)
# netstat
Netstat là công cụ kiểm tra những dịch vụ đang kết nối đến hệ thống.

Các option:
- `-a ` all tất cả các kết nối có trong hệ thống
- `-u` liệt kê các port ở trạng thái UDP
- `-t` Liệt kê các port ở trạng thái TCP
- `-aut` liệt kê các port ở 2 trạng thái UDP và TCP
- `-l` liệt kê các port ở trạng thái Listening
- `-s` thống kê các giao thức
- `-p` hiện thị PID
- `-r` hiển thị bảng định tuyến

Ví dụ: show các port ở trạng thái ESTABLISHED kèm theo PID

    huynp@huyComputer:~$ netstat -etup
    
    (Not all processes could be identified, non-owned process info
     will not be shown, you would have to be root to see it all.)
    Active Internet connections (w/o servers)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State       User       Inode      PID/Program name           
    tcp        0      0 huyComputer:56724       52.108.46.8:https       ESTABLISHED huynp      99157      4728/firefox               
    tcp        0      0 huyComputer:50656       ec2-52-35-57-239.:https TIME_WAIT   root       0          -                          
    tcp        0      0 huyComputer:36650       91.108.56.189:https     ESTABLISHED huynp      148867     5535/telegram-deskt        
    tcp        0      0 huyComputer:36230       ec2-52-42-216-19.:https ESTABLISHED huynp      52744      4728/firefox        
    tcp        0      0 huyComputer:46962       lb-140-82-112-25-:https ESTABLISHED huynp      130810     4728/firefox        
    tcp        0      0 huyComputer:56728       52.108.46.8:https       ESTABLISHED huynp      99814      4728/firefox        
    tcp        0      0 huyComputer:52088       13.107.42.13:https      ESTABLISHED huynp      101977     4728/firefox    
                                                                                                                
# tcpdump
Là một tiện ích phân tích gói tin, cho phép theo dõi băng thông mạng thông qua việc lưu trữ dữ liệu (packet) truyền tải trên mạng.

Tính năng chính:
- Bắt các bản tin và lưu vào định dạng PCAP (có thể đọc được bởi Wireshark).
- Tạo các bộ lọc filter để bắt các gói cụ thể
- Có thể truyền kết quả vào log để phục vụ cho việc phân tích.

Các option:
- `-i [interface]` sử dụng khi cần bắt các gói tin trên interface chỉ định
- `-D` liệt kê tất cả các interface trên máy mà có thể capture được
- `-c [N]` ngừng hoạt động khi capture N gói tin
- `-n` không phân giải địa chỉ sang hostname
- `-w` ghi vào file

Các filter:
- `port [port_num]` lọc theo port
- `src [ip]` lọc theo IP nguồn
- `dst [ip]` lọc theo IP đích

Ví dụ: bắt 5 gói tin từ interface `eno1` và lưu kết quả vào file test.pcap

    sudo tcpdump -i eno1 -c 5 -w test.pcap

    huynp@huyComputer:~$ tcpdump -r test.pcap 
    reading from file test.pcap, link-type EN10MB (Ethernet)
    11:56:42.403130 IP 192.168.18.37.55899 > 239.255.255.250.1900: UDP, length 171
    11:56:42.421333 STP 802.1w, Rapid STP, Flags [Learn, Forward, Agreement], bridge-id 8000.50:f7:22:de:02:95.8005, length 43
    11:56:42.739933 ARP, Request who-has 192.168.18.181 tell 192.168.18.92, length 46
    11:56:42.765359 ARP, Request who-has 192.168.18.76 tell _gateway, length 46
    11:56:43.062745 IP 192.168.18.113.33612 > 239.255.255.250.1900: UDP, length 171

Các trường thông tin được xếp theo format:

    time-stamp src > dst: flags data-seqno ack window urgent options
    
    11:56:43.062745 IP 192.168.18.113.33612 > 239.255.255.250.1900: UDP, length 171

|Tên trường|Mô tả|
|----------|-----|
|Time-stamp|Thời gian gói tin được capture|
|Src > Dst|IP nguồn đến IP đích|
|Flags| S(SYN): Quá trình bắt tay giao thức TCP
|| .(ACK): Thông báo cho bên gửi biết gói tin đã nhận được dữ liệu thành công|
|| F(FIN): Đóng kết nối TCP|  
|| P(PUSH): Đánh dấu việc truyền dữ liệu|
|| R(RST): Sử dụng khi muốn thiết lập lại đường truyền|
|Data-sqeno| Số sequence number của gói dữ liệu hiện tại|
|ACK| Số Sequence number tiếp theo của gói tin do bên gửi truyền (Số sequence number mong muốn nhận được)|
|Window| Vùng đệm có sẵn theo hướng khác|
|Urgent|Dữ liệu khẩn cấp trong gói tin|
