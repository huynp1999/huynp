# Limit Bandwidth Lab

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc3.png)

**Mục tiêu**: giới hạn băng thông download của 2 máy client thuộc mạng `192.168.0.0`

Giải thích script:
- Dùng iptables nat ra ngoài internet
- Tạo `root qdisc` với handle là 1: và gán HTB
- Tạo class từ gốc `root qdisc` với handle là 1:1
  - Class này giới hạn tốc độ download còn 2mpbs cho mỗi Client trong mạng
- Tạo filter cho mạng `192.168.0.0` áp dụng vào class 1:1

```
#!/bin/bash
if="ens4"
TC=$(which tc)

echo "iptables nat outside";
iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE

echo "root";
$TC qdisc add dev $if root handle 1: htb default 10 

echo "limit bandwidth";
$TC class add dev $if parent 1:1 classid 1:1 htb rate 2mbit	
$TC filter add dev $if protocol ip parent 1: prio 1 u32 match ip dst 192.168.0.0/24 flowid 1:1 
```

### Kiểm tra
Trước khi thực hiện limit

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc1.png)

Sau khi thực hiện limit

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc2.png)

**Có thể thấy tốc độ download bị giới hạn xuống dưới 2mpbs**
