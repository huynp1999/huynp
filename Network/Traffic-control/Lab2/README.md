# Limit bandwidth per IP
![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc2/tc3.png)

 Mục tiêu:
- `192.168.1.10` sẽ được ưu tiên mỗi khi tham gia mạng, và các IP khác sẽ bị giới hạn băng thông
- `192.168.1.20` và `.30` sẽ được dùng băng thông mặc định là 2mbps khi chưa có `.10` tham gia

```
#!/bin/bash
if="ens3"

tc q del dev $if root
tc q add dev $if root handle 1:0 htb default 10
tc c add dev $if parent 1:0 classid 1:3 htb rate 10mbps

#fastlink
tc c add dev $if parent 1:3 classid 1:31 htb rate 8mbps ceil 10mbps prio 0
#slowlink
tc c add dev $if parent 1:3 classid 1:33 htb rate 1mbps ceil 2mbps pri 1

tc f add dev $if parent 1:0 protocol ip prio 9 u32 match ip dst 192.168.1.10 flowid 1:31
tc f add dev $if parent 1:0 protocol ip prio 10 u32 match ip dst 192.168.1.20 flowid 1:33
tc f add dev $if parent 1:0 protocol ip prio 10 u32 match ip dst 192.168.1.30 flowid 1:33
```

Khi chưa có Linux1 tham gia, Linux3 và Linux2 được mượn tối đa 2mbps băng thông (`ceil 2mbps`)

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc2/tc2.png)

Khi Linux1 tham gia

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc2/tc4.png)

Cả 2 Linux2 và Linux3 bị cắt giảm băng thông

![](https://github.com/huynp1999/huynp/blob/master/pic/network/tc2/tc1.png)
