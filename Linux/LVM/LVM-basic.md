# Tổng quan LVM
LVM (Logical Volume Manager) là một phương pháp cho phép chuyển các không gian đĩa cứng thành những phân vùng logic, giúp thuận lợi cho việc quản lý kích thước các phân vùng. 

## Các chức năng chính
- Tạo và quản lý nhiều Logical Volume cũng một lúc.
- Snapshot, cho phép phục hổi hiện trạng của không gian ổ đĩa tại một thời điểm nhất định.
- Thin Provisioning, cấp phát dung lượng dựa trên bộ nhớ trống
- Migration, cho phép tạo ra bản sao từ Logical Volume nhằm di chuyển dữ liệu tới nơi khác

## Các khái niệm
**1. Physical volume (PV)**
  - Ổ cứng vật lí từ hệ thống (partition, SSD, đĩa cứng,..)
  - Đơn vị cơ bản để LVM khởi tạo volume group
**2. Volume group (VG)**
  - Nhóm các physical volume (ổ đĩa ảo) trên 1 hoặc nhiều ổ đĩa khác nhau.
  - Dung lượng của một VG sẽ được chia thành nhiều Physical Extent (PE) với kích cỡ bằng nhau.
  - Logical Volume được tạo từ dung lượng trống của VG
**3. Extent**
  - Là đơn vị dữ liệu của VG
  - Logical volume được tạo ra từ VG chứa nhiều extent nhỏ với kích thước bằng nhau
  - Các extent trên LV không nhất thiết phải nằm trên cùng một ổ cứng vật lí mà có thể rải rác trên nhiều ổ cứng khác nhau
  - Kích thước của một LV có thể được thêm bớt dựa theo các extent 
**4. Logical volume (LV)**
  - Phân vùng ảo của ổ đĩa ảo, được chia từ VG.
  - Dùng để mount tới các filesystem và được format với định dạng chuẩn khác nhau như ext2, ext3, ext4...
  - Tương tự như các partition trên ổ cứng nhưng linh hoạt hơn vì có thể tùy chỉnh kích thước mà không làm gián đoạn hệ thống.
  - LV được chia thành nhiều các Logical Extent, mỗi Logical Extent được ánh xạ với 1 Physical Extent trên ổ đĩa.

## Các thao tác quản lý

LVM là một phương pháp được hỗ trợ sẵn trong các hệ điều hành Linux. Các tính năng của nó được cung cấp qua nhiều tiện các câu lệnh. 

1. Đối với Physical Volumes, các câu lệnh chứa tiền tố `pv*` với một số chức năng chính như:
- `pvcreate` tạo PV từ partition  
- `pvs` show các PV đã được tạo
- `pvremove` xóa PV
- `pvresize` điều chỉnh kích thước của PV

Một Physical Volume tương đương với một đĩa vật lý hoặc một phân vùng, chẳng hạn như `/dev/sda1`,`/dev/sdb`.

Đối với Volume Group, các câu lệnh chứa tiền tố `vg*` với một số chắc năng chính như:
- `vgcreate` tạo VG từ PV
- `vgs` show các VG đã được tạo
- `vgextend`,`vgreduce` tăng và giảm kích thước VG
- `vgremove` xóa VG
- `vgcfgbackup`,`vgcfgrestore` lưu trữ và khôi phục cấu hình VG

Một Volume Group được hình thành từ là một nhóm các Physical Volume.

Đối với Logical Volume, các câu lệnh chứa tiền tố `lv*` với một số chắc năng chính như:
- `lvcreate` tạo LV từ VG
- `lvs` show các LV đã được tạo
- `lvextend`,`lvreduce` tăng và giảm kích thước LV
- `lvremove` xóa LV
- `lvmdiskscan` kiểm tra tình trạng các phân vùng ô cứng

Logical Volume là mức cuối cùng trước khi có thể mount vào hệ điều hành.

## LAB
### Bước 1: Tạo physical volume

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

### Bước 2: Tạo volume group từ physical volume
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

### Bước 3: Tạo logical volume từ volume group

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

### Bước 4: Format và mount
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

