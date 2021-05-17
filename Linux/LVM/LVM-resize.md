### Thay đổi kích thước của volume group

Khi cần thêm một phân vùng mới để tăng kích thước cho volume group, sử dụng cú pháp: `vgextend [vg] [partition]`

Ví dụ ở đây là `/dev/sdd` cần được gộp vào `LVMGroup` của ví dụ [phần trước](https://github.com/huynp1999/huynp/blob/master/Linux/LVM/LVM-basic.md).
```
# lvmdiskscan | grep sd
  /dev/sda2             [      15.81 GiB]
  /dev/sda5             [       3.72 GiB]
  /dev/sda6             [     476.00 MiB]
  /dev/sdb              [       1.00 GiB] LVM physical volume
  /dev/sdc              [       1.00 GiB] LVM physical volume
  /dev/sdd              [       1.00 GiB]
```

```
# vgextend /dev/LVMGroup /dev/sdd
  Physical volume "/dev/sdd" successfully created
  Volume group "LVMGroup" successfully extended
```

Kiểm tra:
```
~# vgs
  VG       #PV #LV #SN Attr   VSize VFree
  LVMGroup   3   2   0 wz--n- 2.99g 1.20g
```

Có thể thấy kích thước của LVMGroup tăng lên 1GB bằng đúng dung lượng của phân vùng vừa được thêm vào.

Tương tự như vậy khi cần giảm kích thước cho volume group: `vgreduce`

```
# vgreduce /dev/LVMGroup /dev/sdd
  Removed "/dev/sdd" from volume group "LVMGroup"
# vgs
  VG       #PV #LV #SN Attr   VSize VFree
  LVMGroup   2   2   0 wz--n- 1.99g 208.00m
```

### Thay đổi kích thước của logical volume

Để tăng kích thước của một logical volume, trước tiên cần phải có dung lượng trống trong volume group mà logical volume đó được tạo.

1. Kiểm tra dụng lượng tối đa dùng để tăng kích thước: `vgdisplay [vg]`

```
# vgdisplay LVMGroup | grep Free
  Free  PE / Size       307 / 1.20 GiB
```

Có thể thấy dung lượng tối đa có thể tăng cho một logical volume là 1.20GB hoặc 307 PE (physical extent).

2. Thêm dung lượng cho LV Client1: `lvextend -l [PE] [logical_volume]`

```
# lvextend -l 307 /dev/LVMGroup/Client1
  Size of logical volume LVMGroup/Client1 changed from 500.00 MiB (125 extents) to 1.20 GiB (307 extents).
  Logical volume Client1 successfully resized.
```

3. Thay đổi kích thước cho LV Client1: `resize2fs [logical_volume]`

```
# resize2fs /dev/LVMGroup/Client1
resize2fs 1.42.13 (17-May-2015)
Filesystem at /dev/LVMGroup/Client1 is mounted on /mnt/Client1; on-line resizing required
old_desc_blocks = 2, new_desc_blocks = 5
The filesystem on /dev/LVMGroup/Client1 is now 1257472 (1k) blocks long.
```

Để giảm kích thước của một logical volume, trước tiên cần phải unmount nó:

1. Unmount logical volume: `umount -v [mount_directory]`
```
# umount -v /mnt/Client1
umount: /mnt/Client1 unmounted
```
2. Kiểm tra lại filesystem: `e2fsck -f`
3. Cắt bỏ dung lượng của logical volume: `lvreduce -L -[size] [filesystem]
```
# lvreduce -L -1G /dev/LVMGroup/Client1
  WARNING: Reducing active logical volume to 204.00 MiB
  THIS MAY DESTROY YOUR DATA (filesystem etc.)
Do you really want to reduce Client1? [y/n]: y
  Size of logical volume LVMGroup/Client1 changed from 1.20 GiB (307 extents) to 204.00 MiB (51 extents).
  Logical volume Client1 successfully resized.
```
4. Giảm kích thước logical volume: `resize2fs [filesystem] [size]`

### Xóa LV, VG và PV
- Trước khi xóa một logical volume cần phải unmount trước khi tiến hành xóa với câu lệnh: `lvremove [filesystem]`
```
# lvremove /dev/LVMGroup/Client1
Do you really want to remove and DISCARD active logical volume Client1? [y/n]: y
  Logical volume "Client1" successfully removed
```

- Xóa volume group: `vgremove [filesystem]`
```
# vgremove /dev/LVMGroup
  Volume group "LVMGroup" successfully removed
```
- Xóa physical volume: `pvremove [filesystem]
```
# pvremove /dev/sdb
   Labels on physical volume "/dev/sdd" successfully wiped.
```

Kiểm tra:
```
# lvmdiskscan | grep sd
  /dev/sda2  [      15.81 GiB]
  /dev/sda5  [       3.72 GiB]
  /dev/sda6  [     476.00 MiB]
  /dev/sdb   [       1.00 GiB]
  /dev/sdc   [       1.00 GiB]
  /dev/sdd   [       1.00 GiB]
```

Như vậy tất cả đều được gỡ bỏ, các phân vùng trở về trạng thái ban đầu.
