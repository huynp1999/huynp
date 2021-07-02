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
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/ha4.png)
### 1. Cài đặt HAProxy tại gateway
    apt-get install haproxy

### 2. Cấu hình trên 2 webserver
File cấu hình `/etc/haproxy/haproxy.cfg`

     global
        log /dev/log	local0
        log /dev/log	local1 notice
        chroot /var/lib/haproxy
        stats socket /run/haproxy/admin.sock mode 660 level admin
        stats timeout 30s
        user haproxy
        group haproxy
        daemon

        # Default SSL material locations
        ca-base /etc/ssl/certs
        crt-base /etc/ssl/private

        # Default ciphers to use on SSL-enabled listening sockets.
        # For more information, see ciphers(1SSL). This list is from:
        #  https://hynek.me/articles/hardening-your-web-servers-ssl-ciphers/
        ssl-default-bind-ciphers ECDH+AESGCM:DH+AESGCM:ECDH+AES256::RSA+AES:RSA+3DES:!aNULL:!MD5:!DSS
        ssl-default-bind-options no-sslv3

    defaults
        log	global
        mode	http
        option	httplog
        option	dontlognull
               timeout connect 5000
               timeout client  50000
               timeout server  50000
        errorfile 400 /etc/haproxy/errors/400.http
        errorfile 403 /etc/haproxy/errors/403.http
        errorfile 408 /etc/haproxy/errors/408.http
        errorfile 500 /etc/haproxy/errors/500.http
        errorfile 502 /etc/haproxy/errors/502.http
        errorfile 503 /etc/haproxy/errors/503.http
        errorfile 504 /etc/haproxy/errors/504.http
        
    frontend HaSv
        bind 192.168.1.10:80
        mode http
        default_backend WebSV
        
    backend WebSv
        mode http
        balance roundrobin
        option forwardfor
        http-request set-header X-Forwarded-Port %[dst_port]
        http-request add-header X-Forwarded-Proto https if { ssl_fc }
        option httpchk HEAD / HTTP/1.1rnHost:localhost
        server web1.example.com  192.168.1.1:80
        server web2.example.com  192.168.1.2:80
        server web3.example.com  192.168.1.3:80

Trong đó
- Trường `frontend` để báo cho HAProxy biết phải lắng nghe kết nối đến ở đâu, tại đây là lắng nghe từ port 80 của chính nó.
- Trường `backend` là nơi mà HAProxy sẽ gửi request tới.

Sau khi cấu hình, kiểm tra lại trước khi restart áp dụng các cài đặt:

    haproxy -c -f /etc/haproxy/haproxy.cfg

Nếu kết quả trả lại và `valid` tức không có lỗi thì restart:

    service haproxy restart

Như vậy HAProxy sẽ thực loadbalancing giữa 3 webbackend theo các lần truy cập (F5).
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/ha1.png)
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/ha2.png)
![](https://github.com/huynp1999/huynp/blob/master/pic/network/ha-keep/ha3.png)

- Các index ở webbackend đã được sửa lại theo IP để dễ quan sát quá trình điều hướng kết nối.
