# Libvirt
Gồm một bộ phần mềm cung cấp các tiện ích để quản lý máy ảo và các chức năng của ảo hóa như quản lý lưu trữ, giao diện mạng.
Những phần mềm này bao gồm thư viện API, daemon (libvirtd) và các gói tiện tích giao diện dòng lệnh (virsh).

Mục đích chính của Libvirt là hỗ trợ hoàn thiện các tính năng quản lý ảo hóa từ các nhà cung cấp hay các loại hypervisor khác nhau.

<img src="https://user-images.githubusercontent.com/83684068/123903937-cdbef680-d999-11eb-8de0-d1259ab42c89.png" alt="drawing" width="600"/>

## Các chức năng chính
**1. VM management(Quản lý máy ảo):**
- Hỗ trợ các thao tác như start, stop, pause, save, restore và migrate.
- Các hoạt động hotplug cho nhiều loại thiết bị bao gồm disk và network interfaces, memory, và cpus

**2. Remote machine support:**
- Tất cả các chức năng của libvirt có thể được truy cập trên nhiều máy chạy libvirt deamon
- Hỗ trợ kết nối từ xa như SSH
- Hỗ trợ kết nối từ xa như SSH

![](https://camo.githubusercontent.com/637eea310fe97b243eef9045bcbe4c00730966b4d640c01dc26fec55739f4c5e/68747470733a2f2f692e6962622e636f2f346a664c5947732f53637265656e73686f742d66726f6d2d323032302d31302d31372d31312d31362d33302e706e67)

**3. Storage management:**
- Libvirt daemon hỗ trợ quản lý nhiều loại storage: tạo file image với nhiều định dạng (qcow2, vmdk, raw,...), mount NFS shares, tạo nhóm phân vùng LVM mới, phân vùng ổ cứng,...
- Các lệnh cấu hình pools và volumes

      pool-edit, pool-dumpxml, pool-define,..
      vol-edit, vol-dumpxml, vol-define,...
**4. Network interface management:**
- Libvirt daemon hỗ trợ quản lý các interface netowork vật lý và logic.
- Liệt kê các interface đang tồn tại, cũng như là cấu hình (hoặc tạo, xóa) các interfaces, bridge, vlans, và bond devices.
- Các lệnh cấu hình mạng ảo và các interface
    
      net-edit, net-dumpxml, net-start,...
      iface-edit, iface-define, iface-start,...

**5. Virtual NAT and Route based networking:**
- Quản lý và tạo các mạng ảo
- Libvirt virtual network sử dụng firewall như một router, cung cấp các máy ảo trong suốt truy cập tới mạng của host.

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
            <driver name="qemu" type="raw"/>
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
