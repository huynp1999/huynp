# LVM-based guest
Bên cạnh image-based, LVM cũng được libvirt hỗ trợ và có một số ưu điểm so với guest dựa trên image.
Giúp giảm tải cho bộ điều khiển I/O của ổ cứng, và thuận tiện hơn cho quá trình sao lưu (LVM snapshots).

Để sử dụng LVM-based guest, volume group `/dev/vg_guest1` được tạo sẵn với kích thước 10GB.
Từ đây tạo một volume dành cho máy ảo LVM-based guest. Vm1 sẽ có 7GB không gian đĩa trống

    lvcreate -L 7G -n vm1 vg_guest1

Sử dụng file `.xml` để tạo guest, trong đó đã được cấu hình các thông số disk:

    <domain type='qemu'>
      <name>cirros2</name>
      <memory unit='MB'>1024</memory>
      <currentMemory unit='MB'>1024</currentMemory>
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
        <disk type="block" device="disk">                   #LVM-based: type=block
          <driver name="qemu" type="raw" cache='none'/>
          <source dev="/dev/vg_guest1/vm1"/>
          <target dev="vda" bus="virtio"/>
          <address type="pci" domain='0x0000' bus='0x00' slot='0x04' function='0x0'/>
        </disk>
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
        <serial type='pty'>
          <target port='0'/>
        </serial>
        <console type='pty'>
          <target type='serial' port='0'/>
        </console>
        </devices>
        <seclabel type='none'/>
    </domain>

Như vậy sau khi vào kiểm tra trong VM sẽ có thêm một disk 7GB

![](https://github.com/huynp1999/huynp/blob/master/pic/virt/lvmbased.png)

## Chuyển đổi image-based sang LVM-based
Tạo một phân vùng logical (ví dụ: /dev/vg_server1/vm10) có kích thước tương tự như file image (12GB):

    lvcreate -L2G -n vm2 vg_group1

Và convert image

    qemu-img convert /var/lib/libvirt/images/guest_image.img -O raw /dev/vg_group1/vm2

Cập nhật thông số cho VM bằng `virsh edit`

    <disk type='file' device='disk'>
      <driver name='qemu' type='raw' cache='none'/>
      <source file='/var/lib/libvirt/images/guest-img'/>
      <target dev='vda' bus='virtio'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x04' function='0x0'/>
    </disk>

Sửa đổi trường `type` và đường dẫn tới volume thành:

    <disk type="block" device="disk">
      <driver name="qemu" type="raw" cache='none'/>
      <source dev="/dev/vg_guest1/vm2"/>
      <target dev="vda" bus="virtio"/>
      <address type="pci" domain='0x0000' bus='0x00' slot='0x04' function='0x0'/>
    </disk>

