# NAT (Network Address Translation)
Là một kỹ thuật cho phép một hoặc nhiều địa chỉ IP nội miền chuyển đổi sang một hoặc nhiều địa chỉ IP ngoại miền.
 
NAT được thực hiện tại các Router hoặc Server biên, kết nối giữa 2 mạng.

![image](https://user-images.githubusercontent.com/83684068/120141004-db038c80-c205-11eb-86e9-c1ed5b7c2e96.png)

## Cơ chế hoạt động 
Khi gửi một gói tin từ nội miền ra ngoài, NAT sẽ thực hiện thay đổi địa chỉ [IP private](https://github.com/huynp1999/huynp/blob/master/Network/Basic/IPv4.md) (unregistered) thành IP public (registered) bên trong gói tin.
Tương tự, ngược lại đối với các gói tin từ ngoài vào trong mạng nội bộ.

- NAT cho phép người dùng bảo mật được thông tin IP máy tính, cũng như vừa tiết kiệm được số lượng IPv4 cần sử dụng.

- Cũng vì vậy mà NAT yêu cầu nhiều tài nguyên CPU làm tăng khả năng trễ trong quá trình switching, và cũng có thể gây ra lỗi với một số ứng dụng cần sử dụng IP

## Các thuật ngữ
![image](https://user-images.githubusercontent.com/83684068/120202527-e16b2600-c250-11eb-96bb-911946beaa13.png)

**Địa chỉ inside local**
- Địa chỉ IP được đặt cho 1 thiết bị ở trong mạng nội bộ. Nó không được cung cấp bởi NIC (Network Information Center).

**Địa chỉ inside global**
- Địa chỉ IP đã được đăng ký tại NIC. Địa chỉ inside global thường được dùng để thay thế cho IP inside local.

**Địa chỉ outside local**
- Địa chỉ IP của một thiết bị nằm ở mạng bên ngoài. Các thiết bị trong mạng nội miền sẽ ra mạng ngoài thông qua địa chỉ IP này.
- Địa chỉ outside local không nhất thiết phải được đăng ký với NIC, có thể là một địa chỉ Private.

**Địa chỉ outside global**
- Địa chỉ IP được đặt cho một thiết bị nằm ở mạng bên ngoài. Địa chỉ này là một IP hợp lệ trên mạng internet.

## Phân loại NAT
1. **Static NAT (one-to-one mapping)**
Là kỹ thuật dùng để biến đổi một IP này thành một IP khác. Sử dụng phương pháp cố định thủ công địa chỉ IP Private sang Public.

Cấu hình:
eth0 = outside network
eth1 = inside network

    iptables -t nat -A PREROUTING -d {outside_address} -j DNAT --to-destination {inside_address}
    iptables -t nat -A POSTROUTING -d {inside_address} -j SNAT --to-destination {outside_address}
    
2. **Dynamic NAT (pool-to-pool mapping)**
Dynamic NAT sẽ chuyển đổi pool IP mạng cục bộ sang pool các IP đã được đăng ký, tự động hóa.

Cấu hình:

    iptables -t nat -A POSTROUTING -o eth0 -s 192.168.0.1-192.168.0.5 -j SNAT --to-source 1.1.1.1-1.1.1.5
    
3. **Dynamic NAT with PAT Overload (many-to-one mapping)**
Hay còn được biết đến là IP Masquerading, chỉ dùng chung 1 địa chỉ IP ngoài cho nhiều IP cục bộ.

Dùng địa chỉ số cổng khác nhau để phân biệt từng chuyển đổi (PAT = Port Address Translation Overload). Như vậy, sẽ có tối đã 65536 địa chi nội bộ được sử dụng.

    iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
    
Trong trường hợp IP ngoài không thay đổi, nên sử dụng SNAT để giảm bớt gánh nặng cho CPU:

    iptables -t nat -A POSTROUTING -o eth0 -j SNAT --to-source {outside_address}
