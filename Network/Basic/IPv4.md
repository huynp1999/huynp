# Giao thức IP
Giao thức IP đóng các gói IP packet để chứa thông tin. 

Các đặc điểm:
- Mỗi packet là một đơn vị bản tin, chúng không được đánh số và không cần phải gửi theo thứ tự
- IP không thiết lập kết nối, việc này dành cho TCP và UDP nằm ở lớp Transport
- Các địa chỉ IP được phân theo các cấp bậc

## IPv4
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
- Gọi n là số bit mượn ở phần Host để chia subnet thì số mạng con là 2^n
- m là số bit còn lại của phần host thì số host cho mỗi mạng con là 2^m - 2
- n+m= số bit phần host ban đầu

## IPv6
Địa chỉ IPv6 dài 128 bit, được chia làm 8 nhóm (octet), mỗi nhóm gồm 16 bit, được ngăn cách với nhau bằng dấu hai chấm “:”. Mỗi nhóm được biểu diễn bằng 4 số hexa.
- Ví dụ: FEDC:BA98:768A:0C98:FEBA:CB87:7678:1111

### Cấu trúc
![alt](https://wiki.matbao.net/wp-content/uploads/2019/09/ipv6-la-gi-5-basic-IPv6-address.png)

Một địa chỉ IPv6 được chia thành 3 phần:
- **Site prefix**: là số được gán đến website bằng một ISP. Theo đó, tất cả máy tính trong cùng một vị trí sẽ được chia sẻ cùng một site prefix.
- **Subnet ID**: là thành phần ở bên trong trang web, được sử dụng với chức năng miêu tả cấu trúc trang của mạng. Một IPv6 subnet có cấu trúc tương đương với một nhánh mạng đơn như subnet của IPv4.
- **Interface ID**: có cấu trúc tương tự host_ID trong IPv4. Số này nhận dạng duy nhất một host riêng trong mạng. Interface ID được cấu hình tự động điển hình là dựa vào địa chỉ MAC của giao diện mạng.

Với số lượng địa chỉ lớn, khả năng cung cấp được cho nhiều node và cấu trúc phân cấp linh hoạt. Cùng vì nhiều nên nó cần 1 số quy tắc để nhằm rút ngắn lại cách biểu diễn:
- Cho phép bỏ các số 0 nằm trước mỗi nhóm (octet).
- Thay bằng số 0 cho nhóm có toàn số 0.
- Thay bằng dấu “::” cho các nhóm liên tiếp nhau có toàn số 0 (chỉ được thay 1 lần)

Ví dụ với một IPv6 đầy đủ như sau: `1080:0000:0000:0070:0000:0989:CB45:005F` có thể viết được thành `1080::70:0:989:CB45:5F`

### Phân loại

Một địa chỉ IPv6 có thể được phân thành 1 trong 3 loại:
- **Unicast**: chỉ có duy nhất 1 địa chỉ unicast trên một cổng của một node IPv6
- **Multicast**: một địa chỉ multicast định nghĩa một nhóm các cổng IPv6. Một gói tin gửi đến địa chỉ multicast được xử lý bởi tất cả những thành viên trong nhóm
- **Anycast**: địa chỉ được đăng kí cho nhiều cổng (trên nhiều node)
