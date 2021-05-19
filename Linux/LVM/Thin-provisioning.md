# Thin Provisioning
Là một tính năng cấp phát ổ cứng dựa theo nhu cầu trong LVM.
- Ví dụ: Với VG có 15GB dung lượng được chia cho 3 người, mỗi người có một **thin pool** với 5GB dung lượng.
- Trên thực tế, 3 người này có thể sẽ không dùng hết và chỉ sử dụng tổng cộng 7GB, Thin Provisioning sẽ dựa vào đó để cấp phát thêm 5GB còn thừa cho người thứ 4. Nhờ đó mà tận dụng tối ưu dung lượng lưu trữ.
- Tuy nhiên, nếu 3 người đầu tiên thật sự dùng hết 5GB sẽ xảy ra tình trạng Over Provisioning và cần phải được đối phó kịp thời, đây cũng là nhược điểm của tính năng này.


## Lab
1. Trước tiên, cần tạo một VG dành riêng cho Thin Group
```
# vgcreate LVMThinGrp /dev/sdb /dev/sdc /dev/sdd
  Volume group "LVMThinGrp" successfully created
# vgs
  VG         #PV #LV #SN Attr   VSize VFree
  LVMThinGrp   3   0   0 wz--n- 2.99g 2.99g
```

2. Tạo Thin Pool từ Thin Group
Bản chất Thin Pool chính là Logical Volume sử dụng thêm option `--thinpool`
```
# lvcreate -l 750 --thinpool ThinPool LVMThinGrp
  Logical volume "ThinPool" created.
```

3. Tạo Thin Volume từ Thin Pool
```
# lvcreate -V 500 --thin -n Client1 LVMThinGrp/ThinPool
  Logical volume "Client1" created.
# lvs
  LV       VG         Attr       LSize   Pool     Origin Data%  Meta%  Move Log Cpy%Sync Convert
  Client1  LVMThinGrp Vwi-a-tz-- 500.00m ThinPool        0.00
  ThinPool LVMThinGrp twi---tz--   2.93g                 0.00   11.13
```
4. Mount các Thin Volume
Các bước mount Thin Volume tương tự như với Logical Volume.

```
# lvs
  LV       VG         Attr       LSize   Pool     Origin Data%  Meta%  Move Log Cpy%Sync Convert
  Client1  LVMThinGrp Vwi-aotz-- 500.00m ThinPool        4.97
  Client2  LVMThinGrp Vwi-aotz-- 500.00m ThinPool        4.97
  Client3  LVMThinGrp Vwi-aotz-- 500.00m ThinPool        4.97
  ThinPool LVMThinGrp twi---tz--   2.93g                 2.49   11.91
```

Có thể thấy các thin volume hiện đang sử dụng 4.97% dung lượng và thin pool chỉ sử dụng 2.49%.

# Thick Provisioning
Ngược lại với Thin, tính năng này chiếm hết dung lượng lưu trữ của bộ nhớ và kém linh hoạt. Tuy nhiên tốc độ phần nào nhanh hơn và quản lý dễ dàng, do được cấp phát cố định.
