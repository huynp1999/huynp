# Limit Bandwidth Lab

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc3.png)

**Mục tiêu**: giới hạn băng thông download của 2 máy client thuộc mạng `192.168.0.0`

Giải thích script:
- Dùng iptables nat 2 subnet ra ngoài internet
- Tạo `root qdisc` theo từng interface và với gán TBF
- TBF cho phép giới hạn luồng lưu lượng cụ thể xuống một tốc độ cố định
  - Ví dụ ở đây với subnet `192.168.1.0` = 2mbps, `192.168.2.0` = 8 mpbs
- Đính kèm qdisc ingress và set tốc độ uplink chung = 2mbit cho từng interface

```
#!/bin/bash
if4="ens4"
if5="ens5"
down1="2mbit"
down2="8mbit"
up="2mbit"
TC=$(which tc)

echo "nat";
iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE

echo "limit download";
$TC qdisc add dev $if4 root tbf rate $down1 latency 25ms burst $down1
$TC qdisc add dev $if5 root tbf rate $down2 latency 25ms burst $down2

echo "ingress";
$TC qdisc add dev $if5 handle ffff: ingress
$TC qdisc add dev $if4 handle ffff: ingress

echo "limit upload";
$TC filter add dev $if4 parent ffff: protocol ip prio 1 u32 match ip src 192.168.1.0/24 police rate $up burst $up flowid :1
$TC filter add dev $if5 parent ffff: protocol ip prio 1 u32 match ip src 192.168.2.0/24 police rate $up burst $up flowid :2
```

### Kiểm tra
Trước khi thực hiện limit

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc1.png)

Sau khi thực hiện limit:
- Tại client 1

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc5.png)

- Tại client 2

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc/tc4.png)

**Có thể thấy tốc độ download của client 1 và 2 bị giới hạn xuống 2mpbs và 8mpbs**
