# Iptables Linux Firewall
Được sử dụng để theo dõi lưu lượng truy cập đến và đi ở một server và lọc nó dựa trên các rule do người dùng định nghĩa trước đó.

Để làm được việc này, iptables tương tác với Netfilter Framework và cách các thành phần khác nhau để cung cấp một hệ thống lọc và xáo trộn toàn diện.

____

# Mục lục

- [1. Iptables](#content)
  - [1.1. Table](#table)
  - [1.2. Chain](#chain)
  - [1.3. Target](#target)
  - [1.4. Rule](#rule)
- [2. Các tùy chọn](#option)
  - [2.1. Các tùy chọn với thông số](#2.1)
  - [2.2. Các tùy chọn với chain](#2.2)
  - [2.3. Các tùy chọn với rule](#2.3)
  - [2.4. Ví dụ](#2.4)

____
## <a name="content">1. iptables</a>
Là giao diện dòng lệnh để cho phép người dùng tương tác với các tính năng Packet Filtering của Netfilter Framework trong Kernel.

![image](https://user-images.githubusercontent.com/83684068/120414873-d7e2da80-c384-11eb-8738-dfaa40d7ce93.png)

Cơ chế packet filtering của iptables hoạt động bao gồm 3 thành phần: **table, chain** và **target**.

![](https://raw.githubusercontent.com/ImKifu/thuctapsinh/master/HungNK/Basic_Linux_Command/Picture/netfilter1.png)

### <a name="table">1.1. Table</a>
Iptables Firewall sử dụng các bảng để tổ chức các quy tắc của nó. Các bảng này phân loại các quy tắc theo loại quyết định mà chúng được sử dụng để đưa ra. Mặc định sử dụng là bảng filter.
- Ví dụ khi một quy tắc (rule) được đưa ra:
  - Nếu rule liên quan đến dịch địa chỉ mạng, nó sẽ được đưa vào bảng nat
  - Nếu rule dùng để quyết định gói tin đến được đích hay không, nó có thể sẽ được thêm vào bảng filter

| Table  | Chức năng |
| ------------- |:-------------:|
| Filter      | Lọc, quyết định gói tin có đến được địa chỉ đích hay không. Lọc theo các tiêu chí như như: địa chỉ nguồn, địa chỉ đích, port nguồn, port đích, TTL, TOS, giao thức    |
| Mangle      | Được sử dụng để thay đổi các tiêu đề IP của gói theo nhiều trường khác nhau, ví dụ như TOS(type of service), TTL(time to live), và MARK     |
|    NAT   |  Cho phép các gói tin đến các host khác nhau trong mạng NAT table bằng cách thay đổi IP nguồn và IP đích của gói tin. Xem [thêm](https://github.com/huynp1999/huynp/blob/master/Network/Protocols/DHCP-NAT/NAT.md)  |
|   Raw    |  Một gói tin có thể thuộc 1 kết nối mới hoặc 1 kết nối đã tồn tại. Raw table cho phép làm việc với gói tin trước khi Kernel kiểm tra trạng thái kết nối của gói tin. Ccung cấp một cơ chế đánh dấu các gói để từ chối theo dõi kết nối    |
### <a name="chain">1.2. Chain</a>
Trong khi các bảng đại diện cho mục đích chung của các rule mà chúng nắm giữ, còn các chain đại diện cho các hook bộ lọc và kích hoạt chúng.
Mỗi table được tạo với 1 số chain nhất định.

![image](https://user-images.githubusercontent.com/83684068/120418019-07481600-c38a-11eb-8fe1-54a354b5e5d6.png)

| Chain | Chức năng | Table |
| ------------- |:-------------:|:-------------:|
| PREROUTING      | Rule trong chain này được thực thi ngay khi gói tin vừa vào đến giao diện mạng (Network Interface)   | nat, mangle và raw |
| POSTROUTING      | Rule trong chain này được thực thi ngay khi gói tin rời giao diện mạng   | mangle và nat |
| INPUT      | Rule trong chain này được thực thi ngay trước khi gói tin gặp tiến trình(process)  | mangle và nat |
| OUTPUT      | Rule trong chain này được thực thi ngay sau khi gói tin được tiến trình tạo ra | mangle, nat và filter |
| FORWARD      | Rule trong chain này thực thi cho các gói tin được định tuyến qua host hiện tại    | mangle và filter |

**Mô hình hoạt động**

![image](https://user-images.githubusercontent.com/83684068/120418155-35c5f100-c38a-11eb-84e9-c876651ce81f.png)

### <a name="target">1.3. Target</a>
Các hành động áp dụng cho các gói tin. Sử dụng qua option `-j`.

| Target | Chức năng |
| ------------- |:-------------:|
| ACCEPT | Chấp nhận gói tin, cho phép gói tin đi vào hệ thống    |
| DROP | Loại bỏ gói tin, không có gói tin trả lời, hay hệ thống không tồn tại    |
| REJECT | Loại bỏ gói tin nhưng có trả lời table gói tin khác  |
| LOG | Chấp nhận gói tin nhưng sẽ ghi lại log     |
| DNAT      | Chỉ được dùng trong chain PREROUTING và OUTPUT của nat table    |
| SNAT      | Chỉ được dùng trong chain POSTROUTING của nat table    |
| MASQUERADE      | Tương tự như SNAT nhưng sử dụng interface ra ngoài, thay vì 1 IP cố định như SNAT     |

### <a name="rule">1.4. Rule</a>
Kiểm tra các rule trong iptables: `iptables -L -v`

| Rule  | Đại diện |
| ------------- |:-------------:|
| TARGET      | Hành động sẽ thực thi    |
| PROT     | Giao thức hoạt động    |
| IN | Rule áp dụng cho gói tin từ interface đi nào |
| OUT | Rule áp dụng cho các gói tin từ interface ra |
| DESTINATION | Địa chỉ các lượt truy cập được phép áp dụng quy tắc |

## <a name="option">2. Các tùy chọn </a>
### <a name="2.1">2.1 Các tùy chọn với thông số</a>
- `t` chỉ định tên table
  - `-t nat` hoặc nếu không có sẽ mặc định là table filter.
- `-p` chỉ định loại giao thức
  - `-p tcp` 
- `-i`, `-o` chỉ định card interface mạng vào\ra
  - `-i ens3` 
- `-s` chỉ định vùng mạng hoặc pool IP source, dest
  - `-s 192.168.1.0`
  - `-s 192.168.1.10-192.168.1.20`
- `--sport`, `--dport` chỉ định cổng nguồn\đích

### <a name="2.2">2.2 Các tùy chọn với chain</a>
- `-N` tạo chain mới
- `-X` xóa các rule đã tạo trong chain
- `-P` đặt các chính sách cho các chain
-` -L` liệt kê các rule có trong chain
- `-F` xóa các rule có trong chain

### <a name="2.3">2.3 Các tùy chọn với rule</a>
- `-A` (append) thêm rule
  - `-A PREROUTING`
- `-D` (delete) xóa rule
- `-R` (replace) thay thế rule
- `-I` (insert) chèn thêm rule

### <a name="2.4">2.4 Ví dụ</a>
- Cho phép tất cả các truy cập

      iptables -A INPUT -i ens3 -j ACCEPT
      
- Cho phép tất cả các truy cập tcp trên cổng ssh

      iptables -A INPUT -p tcp --dport 22 -j ACCEPT
      
- Chặn các truy cập bằng IP

      iptables -A INPUT -s 192.168.1.3 -j DROP

- NAT static, ánh xạ tất cả các kết nối của LAN ra ngoài bằng port 1337:

      iptables -A PREROUTING -t nat -i ens3 -p tcp --dport 1337 -j DNAT --to 192.168.1.2:1337
      iptables -A FORWARD -p tcp -d 192.168.1.2 --dport 1337 -j ACCEPT
    
Với `ens3` là interface ra mạng ngoài (WAN) và `192.168.1.2` là IP mạng cục bộ của máy (LAN)

- Kiểm tra các rule 

      iptables -L -v

- Xóa các rule
      
      iptables -F

- Lưu các rule

      /sbin/iptables-save
