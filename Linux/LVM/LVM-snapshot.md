# Snapshot
Là một tính năng hữu ích trong LVM, cho phép tạo ra các bản sao lưu và phục hồi dữ liệu của một Logical Volume trong một thời điểm ấn định trước.

### Tạo Snapshot
Cần phải sử dụng 1 phần của dung lượng trống trong VG để tạo ra snapshot, vậy nên trước tiên cần phải kiểm tra:
``` 
~# vgdisplay LVMGroup | grep Free
  Free  PE / Size       307 / 1.20 GiB
```
Snapshot cũng tương tự như một LV, dùng chung các câu lệnh như `lvcreate`, `lvextend`, `lvreduce` với chức năng tương tự:
``` 
# lvcreate -l 50 --snapshot -n Client1_Snap /dev/LVMGroup/Client1
  Logical volume "Client1_Snap" created.
```

Kiểm tra:
```
# lvs
  LV           VG       Attr       LSize   Pool Origin  Data%  Meta%  Move Log Cpy%Sync Convert
  Client1      LVMGroup owi-aos--- 500.00m                                                           
  Client1_Snap LVMGroup swi-a-s--- 200.00m      Client1 0.01                                         
  Client2      LVMGroup -wi-ao----   1.30g   
```
### Phục hồi dữ liệu
Trước khi sử dụng snapshot để phục hồi dữ liệu, yêu cầu phải unmount Logical Volume ra trước:
```
# umount -v /dev/LVMGroup/Client1
# lvconvert --merge /dev/LVMGroup/Client1_snap
# mount /dev/LVMGroup/Client1 /mnt/Client1
```
Sau khi merge xong snapshot sẽ bị xoá, và sau khi mount lại sẽ thấy được LV đúng như lúc snapshot.
