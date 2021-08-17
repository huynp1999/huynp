## ceph-mon
Ceph monitor chịu trách nhiệm giám sát tình trạng của toàn hệ thống.
Nó hoạt động như các daemon duy trì sự kết nối trong cluster bằng cách chứa các thông tin cơ bản về cluster, tình trạng các node lưu trữ và thông tin cấu hình cluster.
Ceph-mon thực hiện điều này bằng cách duy trì các bản sao của cluster map. Các cluster map này bao gồm monitor, OSD, PG, CRUSH và MDS map.

Thông qua việc truy xuất cluster map của một ceph-mon, client có thể xác định vị trí của tất cả các ceph-mon và ceph-osd còn lại.
Việc kết nối với ceph-mon cũng là cần thiết để client có thể đọc hoặc ghi vào ceph-osd. Từ các bản sao hiện tại của cluster map và thuật toán CRUSH, ứng dụng client có thể tính toán vị trí cho bất kỳ object nào và giao tiếp trực tiếp với ceph-osd đó.
Đây là một tính năng quan trọng liên quan tới hiệu suất và khả năng mở rộng cao của Ceph.

Ngoài ra, ceph-mon cũng cung cấp các dịch vụ xác thực và ghi log.
Ceph-mon sẽ ghi tất cả các thay đổi vào một bản PAXOS duy nhất và PAXOS sẽ ghi các thay đổi vào kho key-value đảm bảo tính nhất quán tốt nhất.
Ceph-mon tận dụng snapshot và trình vòng lặp để thực hiện đồng bộ hóa trên toàn kho lưu trữ.

<img src="https://user-images.githubusercontent.com/83684068/128659461-df3007a9-2fb3-45ad-9548-e24a5c827135.png" alt="drawing" width="600"/>

## Cluster map
- **Monitor map**: map này lưu giữ thông tin về các node monitor, theo thứ tự gồm: epoch là phiên bản map tại một thời điểm (ví dụ thêm hoặc bớt monitor sẽ +1 epoch), CEPH Cluster ID, lần sửa đổi cuối cùng, thời gian tạo, phiên bản của ceph, hostname các node kèm địa chỉ IP và số port. Kiểm tra monitor map:

      # ceph mon dump
      epoch 2                                                           #phiên bản map tại một thời điểm (ví dụ thêm hoặc bớt monitor sẽ +1 epoch)
      fsid 523677df-def2-4a84-90d2-9910ed6233f2                         #CEPH Cluster ID
      last_changed 2021-08-06 03:40:58.354095                           #lần sửa đổi cuối cùng
      created 2021-08-06 03:40:34.970660                                #thời gian tạo mon
      min_mon_release 14 (nautilus)                                     #phiên bản của ceph
      0: [v2:10.10.10.21:3300/0,v1:10.10.10.21:6789/0] mon.ceph01       #hostname các node kèm địa chỉ IP và số port
      1: [v2:10.10.10.22:3300/0,v1:10.10.10.22:6789/0] mon.ceph02
      2: [v2:10.10.10.23:3300/0,v1:10.10.10.23:6789/0] mon.ceph03
      dumped monmap epoch 2

- **OSD map**: map này lưu giữ các trường như cluster ID, epoch cho việc tạo map OSD và lần sửa đổi cuối và thông tin liên quan đến pool như tên, ID, loại, mức nhân bản và PG. Nó cũng lưu các thông tin OSD như tình trạng, trọng số, thông tin host OSD. Kiểm tra OSD map:

      # ceph osd dump
      epoch 72
      fsid 523677df-def2-4a84-90d2-9910ed6233f2
      created 2021-08-06 03:40:53.857657
      modified 2021-08-11 02:26:14.090777
      flags sortbitwise,recovery_deletes,purged_snapdirs,pglog_hardlimit
      crush_version 13
      full_ratio 0.95                                                       #các mức cảnh báo đầy bộ nhớ
      backfillfull_ratio 0.9                                                #ví dụ như khi dung lượng đạt 85% thì sẽ warning gần đầy bộ nhớ, 95% sẽ báo hết bộ nhớ trống
      nearfull_ratio 0.85
      require_min_compat_client jewel                                       #yêu cầu client phải sử dụng từ phiên bản ceph jewel trở lên
      min_compat_client jewel
      require_osd_release nautilus
      pool 1 '.rgw.root' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 32 pgp_num 32 autoscale_mode warn last_change 28 flags hashpspool stripe_width 0 application rgw
      pool 2 'default.rgw.control' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 32 pgp_num 32 autoscale_mode warn last_change 30 flags hashpspool stripe_width 0 application rgw
      pool 3 'default.rgw.meta' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 32 pgp_num 32 autoscale_mode warn last_change 32 flags hashpspool stripe_width 0 application rgw
      pool 4 'default.rgw.log' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 32 pgp_num 32 autoscale_mode warn last_change 34 flags hashpspool stripe_width 0 application rgw
      pool 5 'rbd' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 128 pgp_num 128 autoscale_mode warn last_change 45 flags hashpspool,selfmanaged_snaps stripe_width 0 application rbd
              removed_snaps [1~3]
      pool 6 'rbdpool1' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 128 pgp_num 128 autoscale_mode warn last_change 52 flags hashpspool,selfmanaged_snaps stripe_width 0 application rbd
              removed_snaps [1~3]
      max_osd 6
      osd.0 up   in  weight 1 up_from 70 up_thru 71 down_at 69 last_clean_interval [61,68) [v2:10.10.10.21:6804/1849,v1:10.10.10.21:6805/1849] [v2:10.10.11.21:6804/1849,v1:10.10.11.21:6805/1849] exists,up 26f73ff2-5461-42c9-b70a-3e6e38b6a785
      osd.1 up   in  weight 1 up_from 70 up_thru 71 down_at 69 last_clean_interval [58,68) [v2:10.10.10.21:6800/1851,v1:10.10.10.21:6801/1851] [v2:10.10.11.21:6800/1851,v1:10.10.11.21:6801/1851] exists,up 2135b85a-cb38-4275-a249-0d883c4acd48
      ...
      ...
      
- **PG map**: map này lưu giữ các cột thông tin về PG (thành phần quản lý các object trong ceph) ví dụ như ID là 5.25, các object được chứa bên trong là [1,3,5], các timestamp về trạng thái và sửa đổi, lần sửa đổi OSD map cuối cùng là 37, tỉ lệ đầy và gần đầy dung lượng. Nó cũng lưu các object count, tình trạng hoạt động và srub (hoạt động kiểm tra tính nhất quán của dữ liệu lưu trữ).

      # ceph pg dump
      
      PG_STAT OBJECTS MISSING_ON_PRIMARY DEGRADED MISPLACED UNFOUND BYTES    OMAP_BYTES* OMAP_KEYS* LOG  DISK_LOG STATE        STATE_STAMP                VERSION REPORTED UP      UP_PRIMARY ACTING  ACTING_PRIMARY LAST_SCRUB SCRUB_STAMP                LAST_DEEP_SCRUB DEEP_SCRUB_STAMP           SNAPTRIMQ_LEN
      5.25          1                  0        0         0       0    20480           0          0   37       37 active+clean 2021-08-17 02:58:17.590547   72'37   99:163 [1,3,5]          1 [1,3,5]              1      72'37 2021-08-16 02:43:03.186908           72'37 2021-08-11 02:32:27.061182             0
      6.26          0                  0        0         0       0        0           0          0 2265     2265 active+clean 2021-08-17 02:58:18.014467 68'2265  99:2381 [4,3,1]          4 [4,3,1]              4    68'2265 2021-08-16 02:43:26.991294         68'2265 2021-08-16 02:43:26.991294             0
      5.24          3                  0        0         0       0 12582912           0          0   52       52 active+clean 2021-08-17 02:58:17.348761   94'52   99:174 [5,0,3]          5 [5,0,3]              5      94'52 2021-08-16 02:44:34.068065           94'52 2021-08-16 02:44:34.068065             0

- **CRUSH map**: map này lưu các thông tin của các thiết bị lưu trữ trong Cluster. Tiếp đến là các buckets hierarchy, chứa trong đó là các node phân cấp như osd, host, rack, root,... Cuối cùng là các rule xác định chính sách về cách dữ liệu được phân phối trên các node trong buckets hierarchy. Ví dụ ở đây là `replicated_rule` được mô tả qua các bước thực hiện `take`, `"chooseleaf_firstn", "num": 0, "type": "host"`. Ý nghĩa các steps này là thực hiện replicate mỗi một OSD trong các host (một host có thể chứa nhiều OSD).

      # ceph osd crush dump
      {
      "devices": [
        {
            "id": 0,
            "name": "osd.0",
            "class": "hdd"
        },
        {
            "id": 1,
            "name": "osd.1",
            "class": "hdd"
        },
      ...
      ...
      "types": [
        {
            "type_id": 0,
            "name": "osd"
        },
        {
            "type_id": 1,
            "name": "host"
        },
        {
            "type_id": 2,
            "name": "chassis"
        },
        {
            "type_id": 3,
            "name": "rack"
      ...
      ...
      "rules": [
        {
            "rule_id": 0,
            "rule_name": "replicated_rule",
            "ruleset": 0,
            "type": 1,
            "min_size": 1,
            "max_size": 10,
            "steps": [
                {
                    "op": "take",
                    "item": -1,
                    "item_name": "default"
                },
                {
                    "op": "chooseleaf_firstn",
                    "num": 0,
                    "type": "host"
                },
                {
                    "op": "emit"
                }          


- **MDS map**: lưu thông tin về thời gian tạo và chỉnh sửa, dữ liệu và metadata pool ID, cluster MDS count, tình trạng hoạt động của MDS, epoch của MDS map hiện tại. Kiểm tra MDS map:

      #  ceph mds dump

## Vai trò
Vai trò của monitor là cập nhật cluster map tới client cũng như các node trong cluster, chứ không phải lưu và phục vụ dữ liệu tới client.
Client và các node trong cluster sẽ định kì kiểm tra tới monitor để lấy được cluster map gần nhất.

Monitor là một lightweight daemon không yêu cầu nhiều tài nguyên tính toán. Các node monitor nên có không gian ổ đĩa đủ lớn để lưu cluster logs (OSD log, MDS log và monitor log). Một Ceph cluster điển hình thường có nhiều hơn một node monitor và số lượng node monitor nên là số lẻ để đạt được hiểu quả tốt nhất (minimum 1, recommend 3). Vì trong một quorum, hơn một nửa số lượng monitor node cần được đảm bảo sẵn sàng để tránh rơi vào trạng thái "split-brain". Một monitor node sẽ là leader, và các node còn lại sẽ đưa đưa lên làm leader nếu node ban đầu bị lỗi.

Monitor daemon vẫn có thể chạy cùng trên OSD node và sẽ cần trang bị nhiều CPU, RAM và ổ cứng hơn để lưu monitor logs. Nhưng đối với các hệ thống lớn, nên sử dụng các node monitor chuyên dụng. Với các rack, switch và nguồn điện riêng biệt.
