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

# Virtsh
