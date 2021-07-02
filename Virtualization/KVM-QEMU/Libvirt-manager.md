# Virt Manager
Là ứng dụng giao diện đồ họa cho người dùng để quản lý các máy ảo thông qua các API của libvirt.

Cài đặt

    sudo apt-get install virt-manager -y
    
Sử dụng root user hoặc user nằm trong nhóm libvirtd bật virt-manager:

    virt-manager
    
- Note: Ubuntu server vẫn có thể sử dụng virt-manager thông qua chức năng X11 forwarding của SSH.

Sau khi bật virt manager, tạo một máy ảo mới (**File** --> **New virtual machine**) và thêm image của guest OS

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/virtman1.png)

Quản lý, tạo mới mạng ảo (tên vmnet1)

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/virtman2.png)
![](https://github.com/huynp1999/huynp/blob/master/pic/virt/virtman3.png)

# WebvirtMgr(Web panel)
Là một công cụ quản lí ảo hóa của libvirt với các chức năng tương tự như virt manager, nhưng dựa trên giao diện web.

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

Thêm file cấu hình `webvirtmgr.cfg` tại `/etc/nginx/conf.d/`
