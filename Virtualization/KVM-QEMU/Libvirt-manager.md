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

# Virsh
Là một công cụ tương tác với libvirtd để quản lý virtual network và virtual machine, thông qua giao diện dòng lệnh.

Cú pháp virsh:

    virsh [OPTION]... <command> <domain> [ARG]...
    
Liệt kê tất cả các VM đang hoạt động (`--all` để hiển thị cả các VM đã stop)

    huynp@huyComputer:~$ virsh list --all
     Id    Name                           State
    ----------------------------------------------------

    
## Tạo máy ảo
Trước tiên cần tạo một file XML để định nghĩa thông tin máy ảo

      <domain type='kvm'>
        <name>guest</name>
        <memory unit='MB'>512</memory>
        <currentMemory unit='MB'>512</currentMemory>
        <vcpu>1</vcpu>
        <os>
          <type>hvm</type>
          <boot dev='cdrom'/>
        </os>
        <features>
          <acpi/>
        </features>
        <clock offset='utc'/>
        <on_poweroff>destroy</on_poweroff>
        <on_reboot>restart</on_reboot>
        <on_crash>destroy</on_crash>
        <devices>
          <emulator>/usr/bin/kvm</emulator>
          <disk type="file" device="disk">
            <driver name="qemu" type="qcow2"/>
            <source file="/var/lib/libvirt/images/cirros-0.5.1-x86_64-disk.img"/>
            <target dev="hda" bus="ide"/>
            <address type="drive" controller="0" bus="0" target='0'/>
          </disk>
          <interface type='network'>
            <source network='default'/>
            <target dev='vnet-'/>
            <address type='pci' domain='0x0000' bus='0x00' slot='0x03' function='0x0'/>
          </interface>
          </devices>
          <seclabel type='none'/>
      </domain>
   
Bao gồm các thông số sau:
- tên domain máy ảo
- 500MB RAM, 1 vCPU, 1 ổ đĩa
- Đường dẫn tới file img để boot máy ảo: `/var/lib/libvirt/images/cirros-0.5.1-x86_64-disk.img`
- Interface mạng 

Tạo VM từ file XML và kiểm tra

      huynp@huyComputer:/tmp$ virsh create vmtest.xml
      Domain guest created from vmtest.xml

      huynp@huyComputer:/tmp$ virsh list
       Id    Name                           State
      ----------------------------------------------------
       1     guest                          running

Bật console của VM

      huynp@huyComputer:/tmp$ virsh console guest2
      Connected to domain guest2
      Escape character is ^]

      login as 'cirros' user. default password: 'gocubsgo'. use 'sudo' for root.
      cirros login: cirros
      Password: 
      $ 

Một số command khác để tương tác với domain VM:
- `start, shutdown, destroy, reboot` bật tắt, khởi động lại
- `save, restore` lưu và phục hồi
  - `virsh save [vm_name] [vm_name_time].state` sau khi save, VM sẽ không thể khởi động và memory sẽ được các VM khác sử dụng (khác với snapshot)
- `suspend, resume` tạm dừng và tiếp tục
- `autostart (–disable)` bật tắt khởi động cùng hệ thống
- `define, undefine` tạo và xóa VM

Các command snapshot của virsh
- `snapshot-create-as` tạo
- `snapshot-list [vmname]` list những snapshot của một VM
- `snapshot-info` xem thông tin một snapshot
- `snapshot-revert` khôi phục
- `snapshot-delete` xóa

