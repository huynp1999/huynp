# LAB 1 - Webserver forward
![image](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/iptables/ip3.png)

## Mục tiêu
- Webserver 1, 2 đã cài NGINX.
  - Riêng webserver 2 được cấu hình thêm SSL (các bước cấu hình tại [đây](https://www.digitalocean.com/community/tutorials/how-to-create-a-self-signed-ssl-certificate-for-nginx-on-centos-7))
- Backend 1 lắng nghe port 80
- Backend 2 lắng nghe port 443
- FORWARD gói tin đến port 80 trên e0 đến port tương tự trên Backend1
- FORWARD gói tin đến port 443 trên e0 đến port tương tự trên Backend2
- ACCEPT các gói tin ra ngoài internet thông qua server
- ACCEPT Kiểm tra kết nối 5 lần mỗi phút từ mạng LAN.
- ACCEPT kết nối SSH từ trong mạng LAN

## Cấu hình
### Tại backend
- Đặt gateway: `10.2.2.1`

### Tại server
- Bật tính năng định tuyến cho server

      echo '1' > /proc/sys/net/ipv4/ip_forward

- Cấu hình NAT từ mạng trong ra ngoài

      iptables -t nat -A POSTROUTING -o ens4 -j MASQUERADE 

      hoặc với IP tĩnh, cố định:
      
      iptables -t nat -A POSTROUTING -o ens4 -j SNAT --to-source 192.168.53.117
      
![image](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/iptables/ip2.png) 

- Cấu hình forward từ ngoài vào trong
  - Webserver 1 (HTTP:80)

        iptables -t nat -A PREROUTING -i ens4 -p tcp -d 192.168.53.117 —dport 80 -j DNAT —to 10.2.2.30:80
        iptables -A FORWARD -p tcp -d 10.2.2.30 —dport 80 -j ACCEPT
 
  - Webserver 2 (HTTPS:443)

        iptables -t nat -A PREROUTING -i ens4 -p tcp -d 192.168.53.117 —dport 443 -j DNAT —to 10.2.2.40:443
        iptables -A FORWARD -p tcp -d 10.2.2.40 —dport 443 -j ACCEPT
            
- Kiểm tra kết nối, ping 5 lần mỗi phút từ mạng trong ra ngoài
            
      iptables -A INPUT -p icmp --icmp-type echo-request -m limit --limit 5/m --limit-burst 5 -s 10.10.10.0/24 -d 10.10.10.11 -j ACCEPT

- ACCEPT kết nối SSH từ trong mạng LAN

      iptables -A INPUT -p tcp -s 10.10.10.0/24 -d 10.10.10.11 --dport 22 -m state --state NEW -j ACCEPT



# LAB 2 - 
