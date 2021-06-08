# Gateway lab
Yêu cầu:
- Dựng lab gồm 1 server có nhiệm vụ làm gateway ra ngoài internet cho mạng
- Đồng thời kiêm DHCP server và DNS server
- Cấp phát IP và phân giải tên miền cho cho client

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen11.png)

## 1. Cấu hình DHCP (isc dhcp server)
### Mục đích: cấp phát IP cho các server trong mạng nội bộ
- Cài đặt isc-dhcp-server
        
      apt install isc-dhcp-server

- Cấu hình pool và fixed-address trong `/etc/dhcp/dhcpd.conf`

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen5.png)

- Restart

      service isc-dhcp-server restart
      
- Đặt DHCP tại cổng interface `ens3` của các server

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen9.png)

- Kiểm tra

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen12.png)

## 2. Cấu hình NAT (iptables)
### Mục đích: hướng các kết nối từ trong ra ngoài và ngược lại
- Kích hoạt IPtables forward sang máy khác
  
      echo "1" > /proc/sys/net/ipv4/ip_forward
      /etc/init.d/procps restart
  
- Thiết lập kết nối ra ngoài internet

      iptables -t nat POSTROUTING -o ens4 -j MASQUERADE
      
- Kiểm tra (từ server đi ra)

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen4.png)

- Thiết lập kết nối từ ngoài internet vào webserver theo port 80 (http)

      iptables -t nat -A PREROUTING -i ens4 -p tcp -d 192.168.53.124 --dport 80 -j DNAT --to 192.168.1.69:80
      iptables -A FORWARD -p tcp -d 192.168.1.69 —dport 80 -j ACCEPT
      
- Kiểm tra (từ ngoài internet vào webserver)
       
![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen3.png)

- Bảng `nat`

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen10.png)

Note: Lưu và khôi phục các cấu hình, vì sau reboot sẽ mất

      iptables-save > /etc/iptables/rules.v4
      iptables-restore /etc/iptables/rules.v4
      
## 3. Cấu hình DNS (bind9)
### Mục đích: phân giải tên miền `example.com` cùng CNAME `www` của nó thành địa chị IP `192.168.1.2`
- Cài đặt Bind9

      apt install bind9
      
- Cấu hình file zone `/etc/bind/named.conf.local`, thêm 2 zone thuận và nghịch của `example.com`
      
![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen6.png)      
      
- Cấu hình file phân giải thuận `/etc/bind/forward.example`

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen7.png) 

- Cấu hình file phân giải nghịch `/etc/bind/reverse.example`

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen8.png)

- Đặt DNS tại các server và kiểm tra bằng `nslookup` hoặc `dig`

![](https://github.com/huynp1999/huynp/blob/master/pic/network/gen1.png)
