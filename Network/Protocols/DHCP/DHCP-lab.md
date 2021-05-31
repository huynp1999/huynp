# DHCP Lab
![image](https://user-images.githubusercontent.com/83684068/120133903-30846d00-c1f7-11eb-889d-1a20f7ec485b.png)

### 1. Cấu hình interface trên server (netplan)
    vi /etc/netplan/50

![image](https://user-images.githubusercontent.com/83684068/120134006-6a557380-c1f7-11eb-9bc9-344b8eeba047.png)

### 2. Cài đặt gói DHCP server
    apt update
    apt install isc-dhcp-server
    
### 3. Cấu hình DHCP
Lựa chọn interface để phục vụ các DHCP request từ Client:
    
    vi /etc/default/isc-dhcp-server
    
File cấu hình core của DHCP:

    vi /etc/dhcp/dhcpd.conf

Cấu hình pool địa chỉ dành cho việc cấp phát:

![image](https://user-images.githubusercontent.com/83684068/120134487-6aa23e80-c1f8-11eb-94dd-140dd005b519.png)

Gán IP theo một địa chỉ MAC nhất định:

![image](https://user-images.githubusercontent.com/83684068/120134598-ab01bc80-c1f8-11eb-8212-56f6ab09f7dd.png)

Restart để cập nhật các cấu hình:

    service isc-dhcp-server restart
    
### 4. Phía Client
Đặt các interface của client theo IP động DHCP, và kết quả cuối cùng:

![image](https://user-images.githubusercontent.com/83684068/120134698-e4d2c300-c1f8-11eb-9e71-fa4398564d77.png)
