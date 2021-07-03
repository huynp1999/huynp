# WebvirtMgr(Web panel)
Là một công cụ quản lí ảo hóa của libvirt giống như virt manager, nhưng dựa trên giao diện web và có ít tính năng hơn virt manager.

Cho phép tạo và phân bổ tài nguyên của một domain. Hỗ trợ viewer VNC qua một tunnel SSH đưa ra một giao diện điều khiển đồ họa đầy đủ tính năng đến các guest domain. Hiện Webvirt chỉ hỗ trợ KVM.

## Cài đặt và cấu hình
![image](https://user-images.githubusercontent.com/83684068/124342294-1a4e4000-dbed-11eb-94bf-47f0f3f72ef8.png)

Topo gồm 2 node
- WebvirtMgr: cài đặt giao diện quản lí web bằng NGINX.
- QEMU: cài đặt QEMU và chịu trách nhiệm lưu máy ảo và các image.

Cài đặt các gói cần thiết:
    
    sudo apt-get install git python-pip python-libvirt python-libxml2 novnc supervisor nginx

Cài đặt python và cài đặt môi trường cho django

    git clone git://github.com/retspen/webvirtmgr.git
    cd webvirtmgr
    sudo pip install -r requirements.txt # or python-pip (RedHat, Fedora, CentOS, OpenSuse)
    ./manage.py syncdb


Nhập các thông tin cần thiết trong quá trình cài đặt:

    You just installed Django's auth system, which means you don't have any superusers defined.
    Would you like to create one now? (yes/no): yes
    Username (Leave blank to use 'admin'): huynp 
    E-mail address: huynp@domain.local 
    Password: 
    Password (again): 
    Superuser created successfully.
    
Sau đó:
    
    ./manage.py collectstatic
    
### Cấu hình cho nginx
Chuyển thư mục webvirtmgr:

    sudo mv ~/webvirtmgr /var/www/webvirtmgr

Thêm file cấu hình `webvirtmgr.cfg` tại `/etc/nginx/conf.d/` (và `sites-available/`)

    server {
        listen 80 default_server;

        server_name $hostname;
        #access_log /var/log/nginx/webvirtmgr_access_log; 

        location /static/ {
            root /var/www/webvirtmgr/webvirtmgr; # or /srv instead of /var
            expires max;
        }

        location ~ .*\.(js|css)$ {
               proxy_pass http://127.0.0.1:8000;
        }

        location / {
            proxy_pass http://127.0.0.1:8000;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-for $proxy_add_x_forwarded_for;
            proxy_set_header Host $host:$server_port;
            proxy_set_header X-Forwarded-Proto $scheme;
            proxy_connect_timeout 600;
            proxy_read_timeout 600;
            proxy_send_timeout 600;
            client_max_body_size 1024M; # Set higher depending on your needs 
        }
    }

Comment tất cả các dòng trong `/etc/nginx/sites-enabled/default` để NGINX load theo cấu hình` webvirtmgr.conf`, thay vì theo site mặc định

Restart để áp dụng các cấu hình

    service nginx restart
Chỉnh sửa  /etc/insserv/overrides/novnc

    #!/bin/sh
    ### BEGIN INIT INFO
    # Provides:          nova-novncproxy
    # Required-Start:    $network $local_fs $remote_fs $syslog
    # Required-Stop:     $remote_fs
    # Default-Start:     
    # Default-Stop:      
    # Short-Description: Nova NoVNC proxy
    # Description:       Nova NoVNC proxy
    ### END INIT INFO

Cấp quyền cho tất cả các file trong dir webvirt
    
    chown -R www-data:www-data /var/www/webvirtmgr

Tạo và thêm nội dung vào `/etc/supervisor/conf.d/webvirtmgr.conf`

    [program:webvirtmgr]
    command=/usr/bin/python /var/www/webvirtmgr/manage.py run_gunicorn -c /var/www/webvirtmgr/conf/gunicorn.conf.py
    directory=/var/www/webvirtmgr
    autostart=true
    autorestart=true
    stdout_logfile=/var/log/supervisor/webvirtmgr.log
    redirect_stderr=true
    user=www-data

    [program:webvirtmgr-console]
    command=/usr/bin/python /var/www/webvirtmgr/console/webvirtmgr-console
    directory=/var/www/webvirtmgr
    autostart=true
    autorestart=true
    stdout_logfile=/var/log/supervisor/webvirtmgr-console.log
    redirect_stderr=true
    user=www-data

Restart để áp dụng các cấu hình

    service supervisor restart

![image](https://github.com/huynp1999/huynp/blob/master/pic/virt/webvirt7.png)

## Tạo và quản lý VM
Thêm host mới

![image](https://github.com/huynp1999/huynp/blob/master/pic/virt/webvirt1.png)

Tạo đường dẫn cho tới các file image cho VM, cụ thể là `/var/lib/libvirt/images`
- Tuy nhiên ban đầu đây là thư mục trống và cần download hoặc copy file vào

        huynp@huyComputer:~$ scp Downloads/ubuntu-16.04.7-server-amd64.iso root@192.168.53.191:/var/lib/libvirt/images
        root@192.168.53.191's password: 
        ubuntu-16.04.7-server-amd64.iso                                        100%  880MB   2.3MB/s   06:28    
 
File image sẽ được hiển thị trên webvirt

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/webvirt2.png)

Tạo máy ảo

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/webvirt5.png)

Chọn file image để load trên máy ảo

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/webvirt3.png)

Chọn **Console** để hiện thị giao diện đồ họa của máy ảo thông qua màn hình VNC viewer

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/webvirt4.png)

