1. **Tạo physical volume**

Cú pháp: `pvcreate [partition1] [partition2]`

```
root@huynp:~# lvmdiskscan | grep sd
  /dev/sda2  [      15.81 GiB]
  /dev/sda5  [       3.72 GiB]
  /dev/sda6  [     476.00 MiB]
  /dev/sdb   [       1.00 GiB] LVM physical volume
  /dev/sdc   [       1.00 GiB] LVM physical volume
  /dev/sdd   [       1.00 GiB]
 ```
 
hoặc sử dụng câu lệnh `pvs`:
 ```
root@huynp:~# pvs
  PV         VG   Fmt  Attr PSize PFree
  /dev/sdb        lvm2 ---  1.00g 1.00g
  /dev/sdc        lvm2 ---  1.00g 1.00g
```

2. **Tạo volume group** từ physical volume
Cú pháp: `vgcreate [vg_name] [pv1] [pv2]`

```
root@huynp:~# vgcreate LVMGroup /dev/sdb /dev/sdc
  Volume group "LVMGroup" successfully created
```

Kiểm tra với `pvs` hoặc `vgs`:

```
root@huynp:~# pvs
  PV         VG       Fmt  Attr PSize    PFree
  /dev/sdb   LVMGroup lvm2 a--  1020.00m 1020.00m
  /dev/sdc   LVMGroup lvm2 a--  1020.00m 1020.00m\
```
```
root@huynp:~# vgs
  VG       #PV #LV #SN Attr   VSize VFree
  LVMGroup   2   0   0 wz--n- 1.99g 1.99g
```

Có thể thấy dung lượng của volume group `LVMGroup` thiếu một ít so với tổng tổng dung lượng của 2 phân vùng tạo ra nó, bởi vì trong quá trình sử dụng LVM, nó sẽ sử dụng một phần dung lượng để lưu trữ các thông tin khác.

3. **Tạo logical volume** từ volume group

Cú pháp: `lvcreate -L [size] -n [logical_volume_name] [volume_group_name]`

Như vậy một logical volume mới sẽ được tạo từ không gian trống của một volume group.

Ví dụ, cần 2 logical volume với dung lượng như sau:
```
Client1    500MB
Client2    1.3GB
```
```
root@huynp:~# lvcreate -L 500M -n Client1 LVMGroup
  Logical volume "Client1" created.
root@huynp:~# lvcreate -L 1.3G -n Client2 LVMGroup
  Rounding up size to full physical extent 1.30 GiB
  Logical volume "Client2" created.
```

Kiểm tra với option `-o` và thêm những cột thông tin như `lv_size,lv_name`:
```
root@huynp:~# vgs -o +lv_size,lv_name
  VG       #PV #LV #SN Attr   VSize VFree   LSize   LV
  LVMGroup   2   2   0 wz--n- 1.99g 208.00m 500.00m Client1
  LVMGroup   2   2   0 wz--n- 1.99g 208.00m   1.30g Client2
```

4. **Format và mount**
Cuối cùng, các volume group cần phải được format và mount để sử dụng chúng trong hệ thống. Các LV có thể được truy cập ở một trong hai nơi:

`/dev/volume_group_name/logical_volume_name`

hoặc

`/dev/mapper/volume_group_name-logical_volume_name`

Trước tiên format với [mfsk](https://github.com/huynp1999/huynp/blob/master/Linux/Filesystem/Filesystem.md):

```
root@huynp:~# mkfs.ext4 /dev/LVMGroup/Client1
root@huynp:~# mkfs.ext4 /dev/LVMGroup/Client2
```

Mount vào 2 thư mục đã tạo ở `/mnt`:

```
root@huynp:~# mount /dev/LVMGroup/Client1 /mnt/Client1
root@huynp:~# mount /dev/LVMGroup/Client2 /mnt/Client2
```

Kiểm tra các ổ đĩa với câu lệnh `df -h`:

```
root@huynp:~# df -h
Filesystem                    Size  Used Avail Use% Mounted on
udev                          973M     0  973M   0% /dev
tmpfs                         199M  6.3M  193M   4% /run
/dev/sda2                      16G  2.4G   13G  17% /
tmpfs                         992M     0  992M   0% /dev/shm
tmpfs                         5.0M     0  5.0M   0% /run/lock
tmpfs                         992M     0  992M   0% /sys/fs/cgroup
/dev/sda6                     453M  111M  315M  26% /boot
cgmfs                         100K     0  100K   0% /run/cgmanager/fs
tmpfs                         100K     0  100K   0% /run/lxcfs/controllers
tmpfs                         199M     0  199M   0% /run/user/1000
/dev/mapper/LVMGroup-Client1  477M  2.3M  445M   1% /mnt/Client1
/dev/mapper/LVMGroup-Client2  1.3G  2.0M  1.2G   1% /mnt/Client2
```

Lưu ý: `/mnt` chỉ được dùng để mount tạm thời , khi reboot lại sẽ mất. Để tránh khỏi điều này, cần phải cấu hình lại file quản lý thiết bị mount `/etc/fstab` với nội dung sau:

`/dev/mapper/LVMGroup-Client1 /mnt/Client1 ext4 defaults 0 0 /dev/mapper/LVMGroup-Client2 /mnt/Client2 ext4 defaults 0 0`

