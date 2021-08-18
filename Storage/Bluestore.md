# OSD Backends
Trong ceph osd daemon có một module quan trọng được gọi là ObjectStore, chịu trách nhiệm về cách thức lưu trữ và quản lý object. Ceph được thiết kế để hỗ trợ nhiều công cụ lưu trữ bằng cách đăng ký chúng như là các backend khác nhau cho ObjectStore.

Đối với Ceph có 2 loại backend FileStore và BlueStore. Ngoài ra còn có KStore được thử nghiệm trong phiên bản Jewel nhưng đã không còn sử dụng.

# BlueStore
Được sử dụng từ bản Luminous. BlueStore ra đời để tránh các hạn chế của FileStore.
BlueStore ghi trực tiếp object lên thiết bị vật lý và quản lý metada bằng RocksDB. RocksDB sử dụng một filesystem gọn nhẹ và tối giản tên là BlueFS

<img src="https://user-images.githubusercontent.com/83684068/128850502-93d7f9f9-1747-4c6e-83d8-1cb718249d5c.png" alt="drawing" width="750"/>

Trong trường hợp đơn giản nhất, BlueStore sử dụng một thiết bị lưu trữ duy nhất hay còn gọi là thiết bị chính. Thiết bị này sẽ áp dụng toàn bộ dung lượng lưu trữ của nó và được quản lý trực tiếp bởi BlueStore. Thiết bị này thường được xác định bởi một `block` symlink trong thư mục dữ liệu.

Thư mục dữ liệu là một `tmpfs` mount để đặt với tất cả các thông tin cần thiết về OSD như: mã định danh của nó, thuộc về cluster nào và private keyring.

    # df -h
    Filesystem      Size  Used Avail Use% Mounted on
    tmpfs           953M   24K  953M   1% /var/lib/ceph/osd/ceph-1
    tmpfs           953M   24K  953M   1% /var/lib/ceph/osd/ceph-0

Cũng có thể triển khai BlueStore trên một hoặc hai thiết bị bổ sung:

- **Write-Ahead Log (WAL) device:** Được xác định là block.wal trong thư mục dữ liệu. Có thể sử dụng cho write-ahead log hoặc internal journal cho BlueStore. WAL device chỉ hữu ích khi nó nhanh hơn thiết bị chính (ví dụ khi thiết bị này nằm trên SSD còn thiết bị chính nằm trên HDD).

- **DB device:** Được xác định là block.db trong thư mục dữ liệu. Có thể được sử dụng để lưu trữ internal metadata cho BlueStore. BlueStore (hay đúng hơn là RocksDB) sẽ đặt càng nhiều metadata càng tốt vào thiết bị DB để cải thiện hiệu suất cho thiết bị chính. Nếu thiết bị DB đầy, metadata sẽ tràn trở lại thiết bị chính. Và tương tự như WAL, DB device chỉ hữu ích nếu nó nhanh hơn thiết bị chính.

## Config Bluestore OSD
Một thiết bị có thể triển khai Bluestore OSD bằng câu lệnh

    ceph-volume lvm create --bluestore --data /path/to/device

Nếu logical volume đã được tạo sẵn (LV đơn và sử dụng 100% thiết bị) thì cũng có thể triển khai

    ceph-volume lvm create --bluestore --data ceph-vg/lv

(`block.db` và `block.wal` là optional trong bluestore, có thể chỉ định bằng `--block.db` và `--block.wal`)

Sau khi triển khai một OSD thì thư mục dữ liệu sẽ như sau

    # root@ceph01:~# ls -l /var/lib/ceph/osd/ceph-1
    total 24
    lrwxrwxrwx 1 ceph ceph 93 Aug 16 02:38 block -> /dev/ceph-aa7221d6-7879-4f2c-8e5d-f9ed131f21c4/osd-block-2135b85a-cb38-4275-a249-0d883c4acd48        #symlink từ block tới lv đã được ceph-volume tạo
    -rw------- 1 ceph ceph 37 Aug 16 02:38 ceph_fsid                            #fsid tức là id nhận dạng duy nhất của một cluster
    -rw------- 1 ceph ceph 37 Aug 16 02:38 fsid                                 #tương tự như trên nhưng là fsid của osd, ceph-volume sẽ tạo lg và lv dựa trên 2 fsid này
    -rw------- 1 ceph ceph 55 Aug 16 02:38 keyring                              #khoá xác thực của OSD khi làm việc với ceph auth
    -rw------- 1 ceph ceph  6 Aug 16 02:38 ready                                #trạng thái hoạt động của osd (ready)
    -rw------- 1 ceph ceph 10 Aug 16 02:38 type                                 #kiểu backend của osd, bluestore hoặc filestore
    -rw------- 1 ceph ceph  2 Aug 16 02:38 whoami                               #id thứ tự của osd


Tại đây có thể thấy symlink từ `block` tới `vg/lv` mà đã được `ceph-volume` tạo ra theo cú pháp:
- Volume group name: `ceph-{cluster_fsid}` hoặc nếu vg đã tồn tại thì `ceph-{random_uuid}`
- Logical volume name: `osd-block-{osd_fsid}`

## Quy trình thực hiện
Quy trình thực hiện của câu lệnh `create` bao gồm 2 phần là prepare và active. Các bước thực hiện của phần prepare xung quanh việc tạo các thông tin cơ bản cho OSD:

1. Xác nhận volume hoặc device dành cho data và journal
2. Tạo UUID cho OSD
3. Yêu cầu Ceph Monitor nhận dạng OSD bằng UUID đã được tạo
4. Tạo thư mục dữ liệu OSD và mount data volume
5. Journal được symlink từ data volume đến vị trí dành cho journal
6. Kích hoạt `monmap`
7. Thiết bị được mount và thư mục dữ liệu được liên kết bởi ceph-osd
8. Gán LVM tag cho data và journal của OSD

Với backend là Bluestore thì một số LVM tag sau sẽ được thêm vào:

- `block_device` đường dẫn tới logical volume
- `block_uuid` id nhận dạng duy nhất của logical volume
- `cephx_lockbox_secret` là nơi chứa auth key để xác thực cho `dmcrypt_key` trong việc mở khoá thiết bị mã hoá
- `cluster_fsid` id nhận dạng duy nhất của cluster
- `cluster_name` tên cluster
- `encrypted` bằng 1 nếu sử dụng option mã hoá `--dmcrypt` khi tạo OSD
- `osd_fsid` id nhận dạng duy nhất của osd
- `osdspec_affinity`
- `vdo (Virtual Data Optimizer)` nếu có sẵn

- Note: Với Filestore sẽ có thêm tag `journal_device` vì Filestore yêu cầu xử lý journal riêng biệt với data. Khi sử dụng thêm các thiết bị bổ sung như WAL hoặc DB thì cũng có tag `wal_device` và `db_device`

Có thể check những LVM tag bằng câu lệnh `ceph-volume lvm list`.

    root@ceph01:/var/lib/ceph/osd# ceph-volume lvm list
    
    ====== osd.0 =======

      [block]       /dev/ceph-0cbd51ad-a42d-49e0-96bb-d8160818a6c5/osd-block-26f73ff2-5461-42c9-b70a-3e6e38b6a785

          block device              /dev/ceph-0cbd51ad-a42d-49e0-96bb-d8160818a6c5/osd-block-26f73ff2-5461-42c9-b70a-3e6e38b6a785
          block uuid                r4883N-eDlP-inoG-ucWS-A9Gg-2dSj-eWE6WM
          cephx lockbox secret
          cluster fsid              523677df-def2-4a84-90d2-9910ed6233f2
          cluster name              ceph
          crush device class        None
          encrypted                 0
          osd fsid                  26f73ff2-5461-42c9-b70a-3e6e38b6a785
          osd id                    0
          osdspec affinity
          type                      block
          vdo                       0
          devices                   /dev/sdb

Ngoài ra các LVM tag có thể list theo fomart JSON cũng sẽ nhận được những tag tương tự `ceph-volume lvm list --format=json`. Hoặc theo lệnh lv show `lvs -o lv_tag /dev/ceph-vg/block-lv`, ví dụ xem lvm tag của osd.0:

    # lvs -o lv_tags /dev/ceph-0cbd51ad-a42d-49e0-96bb-d8160818a6c5/osd-block-26f73ff2-5461-42c9-b70a-3e6e38b6a785
      LV Tags                                                                                                                                                                                                                                                                                           
      ceph.block_device=/dev/ceph-0cbd51ad-a42d-49e0-96bb-d8160818a6c5/osd-block-26f73ff2-5461-42c9-b70a-3e6e38b6a785,ceph.block_uuid=r4883N-eDlP-inoG-ucWS-A9Gg-2dSj-eWE6WM,ceph.cephx_lockbox_secret=,ceph.cluster_fsid=523677df-def2-4a84-90d2-9910ed6233f2,ceph.cluster_name=ceph,ceph.crush_device_class=None,ceph.encrypted=0,ceph.osd_fsid=26f73ff2-5461-42c9-b70a-3e6e38b6a785,ceph.osd_id=0,ceph.osdspec_affinity=,ceph.type=block,ceph.vdo=0

Tới phần active, sẽ sử dụng những gì đã được tạo sẵn để kích hoạt đưa vào sử dụng ceph-osd

1. Yêu cầu id OSD và uuid OSD
2. Bật systemd unit theo với id và uuid tương thích
3. Systemd unit sẽ đảm bảo tất cả các thiết bị nhận dạng đã được mount và sẵn sàng

        #  systemctl | grep ceph
        var-lib-ceph-osd-ceph\x2d0.mount                           loaded active mounted   /var/lib/ceph/osd/ceph-0
        var-lib-ceph-osd-ceph\x2d1.mount                           loaded active mounted   /var/lib/ceph/osd/ceph-1
5. Systemd unit `ceph-osd` được khởi động

# FileStore
Trong FileStore, các object được lưu với một file riêng lẻ.
Sử dụng FileStore, ceph yêu cầu sử dụng journal bên ngoài để đảm bảo tính nhất quán.

Ceph đảm bảo tính nhất quán cao giữa các bản sao dữ liệu, tất cả các thao tác ghi được xem như đơn vị transaction.
Các transactions được ghi vào journal trước giúp cải thiện hiệu năng. Sau khi được ghi xong vào journal, FileStore daemon thực hiện ghi xuống disk để lưu trữ cố định.

Và trong FileStore, transaction sẽ được chia thành data và metadata. Data sẽ được ghi vào một XFS filesystem, còn metadata sẽ được lưu vào database (leveldb). Và database này cũng dựa trên XFS filesystem

<img src="https://user-images.githubusercontent.com/83684068/128850540-b1fbc61d-6270-4545-95d0-a086fc9782de.png" alt="drawing" width="750"/>

FileStore đã được thử nghiệm tốt và sử dụng rộng rãi trong thị trường. Tuy nhiên, nó có nhiều khiếm khuyết về hiệu suất do thiết kế tổng thể và sự phụ thuộc vào file system truyền thống để lưu trữ object data.

# So sánh giữa Filestore và Bluestore
![image](https://user-images.githubusercontent.com/83684068/128842467-5439240c-f90d-46bf-a983-55f729de5708.png)

**Điểm khác biệt chính** giữa 2 loại module là với FileStore, object phải ghi 2 lần: 1 lần vào journal và 1 lần vào disk. Đối với BlueStore ghi trực tiếp object lên disk và quá trình quản lý metadata cũng được tối giản hơn khi so với Filestore.

Benchmark hiệu năng bằng radosbench, với 7 client cùng write vào object store. Cột xanh là tốc độ ghi (mbps) của Filestore, cột đỏ là tốc độ ghi (mbps) của Bluestore. Dòng kẻ màu xanh lá biểu thị cho phần trăm hiệu suất vượt trội của Bluestore, bắt đầu từ 40% của client đầu tiên tới cao nhất 42%. Có thể thấy Bluestore về cơ bản có tốc độ hoạt động tốt hơn đáng kể so với Filestore.

![image](https://user-images.githubusercontent.com/83684068/129704558-8585b415-21fc-493c-9d2e-ffbd9e62418b.png)
