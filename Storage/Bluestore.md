# OSD Backends
![image](https://user-images.githubusercontent.com/83684068/128842467-5439240c-f90d-46bf-a983-55f729de5708.png)

Trong ceph osd daemon có một module quan trọng được gọi là ObjectStore, chịu trách nhiệm về cách thức lưu trữ và quản lý object. Ceph được thiết kế để hỗ trợ nhiều công cụ lưu trữ bằng cách đăng ký chúng như là các backend khác nhau cho ObjectStore.

Đối với Ceph có 2 loại backend FileStore và BlueStore. Ngoài ra còn có KStore được thử nghiệm trong phiên bản Jewel nhưng đã không còn sử dụng.

# BlueStore
Được sử dụng từ bản Luminous. BlueStore ra đời để tránh các hạn chế của FileStore.
BlueStore ghi trực tiếp object lên thiết bị vật lý và quản lý metada bằng RocksDB. RocksDB sử dụng một filesystem gọn nhẹ và tối giản tên là BlueFS

<img src="https://user-images.githubusercontent.com/83684068/128850502-93d7f9f9-1747-4c6e-83d8-1cb718249d5c.png" alt="drawing" width="750"/>

Trong trường hợp đơn giản nhất, BlueStore sử dụng một thiết bị lưu trữ duy nhất hay còn gọi là thiết bị chính. Thiết bị này sẽ áp dụng toàn bộ dung lượng lưu trữ của nó và được quản lý trực tiếp bởi BlueStore. Thiết bị này thường được xác định bởi một `block` symlink trong thư mục dữ liệu.

```
#
```

Thư mục dữ liệu là một `tmpfs` mount để đặt với tất cả các thông tin cần thiết về OSD như: mã định danh của nó, thuộc về cluster nào và private keyring.

Cũng có thể triển khai BlueStore trên một hoặc hai thiết bị bổ sung:

- **Write-Ahead Log (WAL) device:** Được xác định là block.wal trong thư mục dữ liệu. Có thể sử dụng cho write-ahead log hoặc internal journal cho BlueStore. WAL device chỉ hữu ích khi nó nhanh hơn thiết bị chính (ví dụ khi thiết bị này nằm trên SSD còn thiết bị chính nằm trên HDD).

- **DB device:** Được xác định là block.db trong thư mục dữ liệu. Có thể được sử dụng để lưu trữ internal metadata cho BlueStore. BlueStore (hay đúng hơn là RocksDB) sẽ đặt càng nhiều metadata càng tốt vào thiết bị DB để cải thiện hiệu suất cho thiết bị chính. Nếu thiết bị DB đầy, metadata sẽ tràn trở lại thiết bị chính. Và tương tự như WAL, DB device chỉ hữu ích nếu nó nhanh hơn thiết bị chính.

Một thiết bị có thể triển khai Bluestore OSD bởi câu lệnh

    ceph-volume lvm create --bluestore --data /path/to/device

`block.db` và `block.wal` là optional trong bluestore, chúng có thể được chỉ định bằng `--block.db` và `--block.wal`

Nếu logical volume đã được tạo sẵn (LV đơn và sử dụng 100% thiết bị) thì cũng có thể triển khai

    ceph-volume lvm create --bluestore --data ceph-vg/lv

Câu lệnh `create` trên sẽ thêm những LVM tag sau:

- cluster_fsid
- data_device
- journal_device
- encrypted
- osd_fsid
- osd_id
- journal_uuid

Quy trình thực hiện của câu lệnh `create`

- Xác nhận volume hoặc device dành cho data và journal
- Tạo UUID cho OSD
- Yêu cầu Ceph Monitor nhận dạng OSD bằng UUID đã được tạo
- Tạo thư mục dữ liệu OSD và mount data volume
- Journal được symlink từ data volume đến vị trí dành cho journal
- Kích hoạt `monmap`
- Thiết bị được mount và thư mục dữ liệu được liên kết bởi ceph-osd
- Gán LVM tag cho data và journal của OSD
# FileStore
Trong FileStore, các object được lưu với một file riêng lẻ.
Sử dụng FileStore, ceph yêu cầu sử dụng journal bên ngoài để đảm bảo tính nhất quán.
- Ceph đảm bảo tính nhất quán cao giữa các bản sao dữ liệu, tất cả các thao tác ghi được xem như đơn vị transaction.
Các transactions được ghi vào journal trước giúp cải thiện hiệu năng. Sau khi được ghi xong vào journal, FileStore daemon thực hiện ghi xuống disk để lưu trữ cố định.

Và trong FileStore, transaction sẽ được chia thành data và metadata. Data sẽ được ghi vào một XFS filesystem, còn metadata sẽ được lưu vào database (leveldb). Và database này cũng dựa trên XFS filesystem

<img src="https://user-images.githubusercontent.com/83684068/128850540-b1fbc61d-6270-4545-95d0-a086fc9782de.png" alt="drawing" width="750"/>



**Điểm khác biệt chính** giữa 2 loại module là với FileStore, object phải ghi 2 lần: 1 lần vào journal và 1 lần vào disk. Đối với BlueStore ghi trực tiếp object lên disk và quá trình quản lý metadata cũng được tối giản hơn khi so với Filestore.


