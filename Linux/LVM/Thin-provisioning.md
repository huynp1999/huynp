# Thin Provisioning
Là một tính năng cấp phát ổ cứng dựa theo nhu cầu trong LVM.
- Ví dụ: Với VG có 15GB dung lượng được chia cho 3 người, mỗi người có một **thin pool** với 5GB dung lượng.
- Trên thực tế, 3 người này có thể sẽ không dùng hết và chỉ sử dụng tổng cộng 7GB, Thin Provisioning sẽ dựa vào đó để cấp phát thêm 5GB còn thừa cho người thứ 4. Nhờ đó mà tận dụng tối ưu dung lượng lưu trữ.
- Tuy nhiên, nếu 3 người đầu tiên thật sự dùng hết 5GB sẽ xảy ra tình trạng Over Provisioning và cần phải được đối phó kịp thời, đây cũng là nhược điểm của tính năng này.

## Lab
1. Trước tiên cần tạo một VG dành riêng cho Thin Group
```
vgs
```

2. Tạo Thin Pool từ Thin Group
Bản chất Thin Pool chính là Logical Volume sử dụng thêm option `--thinpool`
```
# lvcreate -l 1018 --thinpool
```

3. Tạo Thin Volume từ Thin Pool
```
# lvcreate -V 1024 --thin -n
```
Kiểm tra:
```
lvs
```
4. Mount các Thin Volume
```
lvs
```
