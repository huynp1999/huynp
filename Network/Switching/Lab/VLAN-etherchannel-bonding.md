# Lab VLAN-routing
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/switching/topo.png)

Thông tin các VLAN:

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/switching/vlan.png)
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/switching/ping.png)

Etherchannel được tạo giữa 2 switch, gộp 2 interface vật lý thành một logic

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/switching/etherchannel.png)

Gộp 2 interface vật lý là ens3 và ens4 lại thành 1 interface ảo có tên là bond0. Cấu hình tại folder netplan `/etc/netplan/`

![Alt](https://github.com/huynp1999/huynp/blob/master/pic/network/switching/netplan.png)

Có thể thấy card bond0 sẽ có cờ 'MASTER' và 2 card ens3 và ens4 có có cờ 'SLAVE'

![Alt](https://github.com/huynp1999/huynp/blob/master/pic/network/switching/bond0.png)

![Alt](https://github.com/huynp1999/huynp/blob/master/pic/network/switching/ens34.png)
