# Giao thức IP
Giao thức IP đóng các gói gọi là IP packet để chứa thông tin. 

Các đặc điểm:
- Mỗi packet là một đơn vị bản tin, chúng không được đánh số và không cần phải gửi theo thứ tự
- IP không thiết lập kết nối, việc này dành cho TCP và UDP nằm ở lớp Transport
- Các địa chỉ IP được phân theo các cấp bậc

### IPv4
Mỗi thiết bị phải có một IP duy nhất trong một vùng mạng.

Mỗi một IP bao gồm 2 phần: **Network** và **Host**. Subnetmask sẽ chỉ ra đâu là phần Network (bit 1) và đâu là phần Host (bit 0)

![Alt](https://vnreview.vn/image/17/69/26/1769266.jpg?t=1519272913318)

Trong đó phần Host sẽ quyết định việc phân ra những IP riêng biệt cho từng người dùng. Nhiều host_ID sẽ phân phát được nhiều hơn.

Việc phân chia Host và Network được chia thành 3 loại:
- Class A: 0.0.0.0 – 126.255.255.255    (1 octet (bytes) Network và 3 Host)
- Class B: 128.0.0.0 – 191.255.255.255  (2 octet (bytes) Network và 2 Host)
- Class C: 192.0.0.0 – 223.255.255.255  (3 octet (bytes) Network và 1 Host)

Subnet 172.0.0.0 dành cho loopback và 224.0.0.0 chính là class D được sử dụng cho multicast
#### IP Private và Public
- IP Public được sử dụng trên Internet
- IP Private được sử dụng trong mạng nội bộ và không nên sử dụng ra ngoài Internet

Phạm vi của IP private:
- Class A:  10.0.0.0 – 10.255.255.255
- Class B:  172.16.0.0 – 172.31.255.255
- Class C:  192.168.0.0 – 192.168.255.255

#### Chia mạng con
Gọi n là số bit mượn ở phần Host để chia subnet thì số mạng con là 2^n
m là số bit còn lại của phần host thì số host cho mỗi mạng con là 2^m - 2
n+m= số bit phần host ban đầu
