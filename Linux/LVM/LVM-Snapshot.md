# Snapshot
Là một tính năng hữu ích trong LVM, cho phép tạo ra các bản sao lưu và phục hồi dữ liệu của một Logical Volume trong một thời điểm ấn định trước.

### Tạo Snapshot
Cần phải sử dụng 1 phần của dung lượng trống trong VG để tạo ra snapshot, vậy nên trước tiên cần phải kiểm tra:
- `vgdisplay LVMVolGroup | grep Free`

Snapshot cũng tương tự như một LV, dùng chung các câu lệnh như `lvcreate`, `lvextend`, `lvreduce` với chức năng tương tự:
``` 
lvcreate

```

Kiểm tra:

```
lvs
```

### Phục hồi dữ liệu
Trước khi sử dụng snapshot để phục hồi dữ liệu, yêu cầu phải unmount Logical Volume ra trước:
```umount -v 
  lvconvert --merge
``` 
Sau khi merge xong, snapshot sẽ bị xoá.
