# KeepAlived
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep6.png)

### 1. Đặt IP các interface theo topo
### 2. NAT ra ngoài tại gateway
 
       iptables -t nat POSTROUTING -o ens3 -j MASQUERADE
       sysctl -w net.ipv4.ip_forward=1
       /etc/init.d/procps restart

### 3. Cài đặt NGINX trên các webbackend
Sửa lại index để phân biệt giữa 2 webbackend:

![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep7.png)

### 4. Cái đặt và cấu hình KeepAlived
    
       apt install keepalived
Cho phép tạo Virtual IP (VIP) dùng cho KeepAlived:

      sysctl -w net.ipv4.ip_nonlocal_bind=1

Cấu hình webbackend 1 và 2 tại `/etc/keepalived/keepalived.conf` với nội dung

      global_defs {
        router_id test1                #khai báo route_id của keepalived
      }
      vrrp_script chk_haproxy {
        script "killall -0 haproxy"
        interval 2
        weight 2
      }
      vrrp_instance VI_1 {
        virtual_router_id 51
        advert_int 1
        priority 100                  #set độ ưu tiên với backend 1 là 100, 2 là 99
        state MASTER                  #khai báo trạng thái của webserver 1 là MASTER, 2 là BACKUP dành cho dự phòng
        interface ens3                #thông tin tên interface của server, bạn dùng lệnh `ifconfig` để xem và điền cho đúng
        virtual_ipaddress {
          192.168.1.254               #khai báo Virtual IP cho interface tương ứng và dùng IP này listen trên HAproxy
        }
       authentication {
           auth_type PASS
           auth_pass 123456           #password này phải khai báo giống nhau giữa các server keepalived
           }
        track_script {
          chk_haproxy
        }
      }

 Restart

       service keepalived start

 Khi kiểm tra có thể thấy chỉ webserver 1 là MASTER mới có quyền giữ VIP `192.168.1.254`, còn 2 thì không có

![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep3.png)
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep5.png)

### 5. Mở port cho NGINX cho phép truy cập từ ngoài internet vào

    iptables -t nat -A PREROUTING -i ens3 -p tcp -d 192.168.53.102 --dport 80 -j DNAT --to 192.168.1.254:80
    iptables -A FORWARD -p tcp --dst 192.168.1.254 --dport 80 -j ACCEPT

Kết quả, khi webserver 1 vẫn hoạt động bình thường

![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep1.png)

Down kết nối của webserver 1, khi này webserver 2 sẽ được giữ VIP

![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep2.png)
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/keep4.png)
# HAProxy
### 1. Cài đặt HAProxy tại gateway
    apt-get install haproxy

### 2. Cấu hình trên 2 webserver
File cấu hình `/etc/haproxy/haproxy.cfg`

    global
        daemon
        maxconn 256

    defaults
        mode http
        timeout connect 5000ms
        timeout client 50000ms
        timeout server 50000ms

    frontend http-in
        bind *:80
        default_backend app
    backend static
        balance roundrobin
        server static 192.168.1.254:80
    backend app
        balance roundrobin
        server test1 192.168.1.10:8080 check
        server test2 192.168.1.20:8080 check

Lưu ý:
- Cần phải đổi port http nginx để tránh conflict với dịch vụ http
- Đổi `listen port` trên mỗi server tại `/etc/nginx/sites-enabled/default`

Như vậy HAProxy sẽ loadbalancing giữa 2 webbackend theo các lần truy cập (F5).
