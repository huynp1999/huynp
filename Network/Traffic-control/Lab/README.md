# Limit Bandwidth Lab

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc3.png)

**Mục tiêu**: giới hạn băng thông download của 2 máy client thuộc mạng `192.168.0.0`

Giải thích script:
- Dùng iptables nat 2 subnet ra ngoài internet
- Tạo `root qdisc` theo từng interface và với gán TBF
- TBF cho phép làm chậm luồng lưu lượng xuống một tốc độ cố định
  - Ví dụ ở đây với subnet `192.168.1.0` = 2mbps, `192.168.2.0` = 8 mpbs
- Đính kèm qdisc ingress và set giới hạn là 2mbit cho uplink theo từng interface

```
#!/bin/bash
if="ens3"
if4="ens4"
if5="ens5"
down1="2mbit"
down2="8mbit"
up="2mbit"
TC=$(which tc)

echo "iptable";
iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE

echo "egress";
$TC qdisc add dev $if4 root tbf rate $down1 latency 25ms burst $down1
$TC qdisc add dev $if5 root tbf rate $down2 latency 25ms burst $down2

echo "ingress";
$TC qdisc add dev $if5 handle ffff: ingress
$TC qdisc add dev $if4 handle ffff: ingress

echo "limit up";
$TC filter add dev $if4 parent ffff: protocol ip prio 1 u32 match ip src 192.168.1.0/24 police rate $up burst $up flowid :1
$TC filter add dev $if5 parent ffff: protocol ip prio 1 u32 match ip src 192.168.2.0/24 police rate $up burst $up flowid :2
```

### Kiểm tra
Trước khi thực hiện limit

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc1.png)

Sau khi thực hiện limit:
- Tại client 1

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc5.png)

-Tại client 2

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc4.png)

**Có thể thấy tốc độ download bị giới hạn xuống dưới 2mpbs**
