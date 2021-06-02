# Iptables Linux Firewall
Được sử dụng để theo dõi lưu lượng truy cập đến và đi ở một server và lọc nó dựa trên các rule do người dùng định nghĩa trước đó.

Để làm được việc này, iptables tương tác với Netfilter Framework và cách các thành phần khác nhau để cung cấp một hệ thống lọc và xáo trộn toàn diện.

## iptables
Là giao diện dòng lệnh để cho phép người dùng tương tác với các tính năng Packet Filtering của Netfilter Framework trong Kernel.

![image](https://user-images.githubusercontent.com/83684068/120414873-d7e2da80-c384-11eb-8738-dfaa40d7ce93.png)

Cơ chế packet filtering của iptables hoạt động bao gồm 3 thành phần: **table, chain** và** target**.

### 1. Table
Iptables Firewall sử dụng các bảng để tổ chức các quy tắc của nó. Các bảng này phân loại các quy tắc theo loại quyết định mà chúng được sử dụng để đưa ra. Mặc định sử dụng là bảng filter.
- Ví dụ khi một quy tắc (rule) được đưa ra:
  - Nếu rule liên quan đến dịch địa chỉ mạng, nó sẽ được đưa vào bảng nat
  - Nếu rule dùng để quyết định gói tin đến được đích hay không, nó có thể sẽ được thêm vào bảng filter

#### 1.1 Filter table
Lọc gói dữ liệu. Quyết định gói tin có đến được địa chỉ đích hay không. Lọc theo các tiêu chí như như: địa chỉ nguồn, địa chỉ đích, port nguồn, port đích, TTL, TOS, giao thức.

Gồm 3 quy tắc:
- Forward chain: lọc gói khi đến các server khác
- Input chain: lọc gói khi vào trong server
- Output chain: Lọc gói khi ra khỏi server

#### 1.2 Mangle table
được sử dụng để thay đổi các tiêu đề IP của gói theo nhiều trường khác nhau, ví dụ như TOS(type of service), TTL(time to live), và MARK.

#### 1.3 NAT table
Cho phép các gói tin đến các host khác nhau trong mạng NAT table bằng cách thay đổi IP nguồn và IP đích của gói tin.

Xem thêm về NAT tại [đây](https://github.com/huynp1999/huynp/blob/master/Network/Protocols/DHCP-NAT/NAT.md).

#### 1.4 Raw table
Một gói tin có thể thuộc 1 kết nối mới hoặc 1 kết nối đã tồn tại. Raw table cho phép làm việc với gói tin trước khi Kernel kiểm tra trạng thái kết nối của gói tin.
cung cấp một cơ chế đánh dấu các gói để từ chối theo dõi kết nối.

### 2. Chain
Trong khi các bảng đại diện cho mục đích chung của các rule mà chúng nắm giữ, còn các chain đại diện cho các hook bộ lọc và kích hoạt chúng.
Mỗi table được tạo với 1 số chain nhất định.

![image](https://user-images.githubusercontent.com/83684068/120418019-07481600-c38a-11eb-8fe1-54a354b5e5d6.png)

| Chain | Chức năng | Table |
| ------------- |:-------------:|:-------------:|
| PREROUTING      | Rule trong chain này được thực thi ngay khi gói tin vừa vào đến giao diện mạng (Network Interface).   | nat, mangle và raw |
| POSTROUTING      | Rule trong chain này được thực thi ngay khi gói tin rời giao diện mạng.   | mangle và nat |
| INPUT      | Rule trong chain này được thực thi ngay trước khi gói tin gặp tiến trình(process).  | mangle và nat |
| OUTPUT      | Rule trong chain này được thực thi ngay sau khi gói tin được tiến trình tạo ra. | mangle, nat và filter |
| FORWARD      | Rule trong chain này thực thi cho các gói tin được định tuyến qua host hiện tại.    | mangle và filter |

**Mô hình hoạt động**

![image](https://user-images.githubusercontent.com/83684068/120418155-35c5f100-c38a-11eb-84e9-c876651ce81f.png)

#### 3. Target
Các hành động áp dụng cho các gói tin. Sử dụng qua option `-j`.

| Target | Chức năng |
| ------------- |:-------------:|
| ACCEPT | chấp nhận gói tin, cho phép gói tin đi vào hệ thống.    |
| DROP | Loại bỏ gói tin, không có gói tin trả lời, hay hệ thống không tồn tại.    |
| REJECT | Loại bỏ gói tin nhưng có trả lời table gói tin khác.  |
| LOG | chấp nhận gói tin nhưng sẽ ghi lại log     |
| DNAT      | chỉ được dùng trong chain PREROUTING và OUTPUT của nat table    |
| SNAT      | chỉ được dùng trong chain POSTROUTING của nat table    |
| MASQUERADE      |tương tự như SNAT nhưng sử dụng interface ra ngoài, thay vì 1 IP cố định như SNAT     |
