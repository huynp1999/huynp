## Cách 1:
Có sẵn 3 cặp hdd và ssd ở mỗi host

    root@ceph01:~# ceph osd tree
    ID  CLASS WEIGHT  TYPE NAME                      STATUS REWEIGHT PRI-AFF
     -1       6.00000 root default
    -33       2.00000     host ceph01
      0   hdd 1.00000         osd.0                      up  1.00000 1.00000
      1   ssd 1.00000         osd.1                      up  1.00000 1.00000
     -8       2.00000     host ceph02
      2   hdd 1.00000         osd.2                      up  1.00000 1.00000
      3   ssd 1.00000         osd.3                      up  1.00000 1.00000
     -5       2.00000     host ceph03
      4   hdd 1.00000         osd.4                      up  1.00000 1.00000
      5   ssd 1.00000         osd.5                      up  1.00000 1.00000

Tạo replicated rule cho từng class và sử dụng host (hdd, ssd) làm failure domain:

    ceph osd crush rule create-replicated replicated_hdd default host hdd
    ceph osd crush rule create-replicated replicated_ssd default host ssd

Kiểm tra các rule mới tạo:

    root@ceph01:~# ceph osd crush rule dump
    [
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
            ]
        },
        {
            "rule_id": 1,
            "rule_name": "replicated_hdd",
            "ruleset": 1,
            "type": 1,
            "min_size": 1,
            "max_size": 10,
            "steps": [
                {
                    "op": "take",
                    "item": -2,
                    "item_name": "default~hdd"
                },
                {
                    "op": "chooseleaf_firstn",
                    "num": 0,
                    "type": "host"
                },
                {
                    "op": "emit"
                }
            ]
        },
        {
            "rule_id": 2,
            "rule_name": "replicated_ssd",
            "ruleset": 2,
            "type": 1,
            "min_size": 1,
            "max_size": 10,
            "steps": [
                {
                    "op": "take",
                    "item": -36,
                    "item_name": "default~ssd"
                },
                {
                    "op": "chooseleaf_firstn",
                    "num": 0,
                    "type": "host"
                },
                {
                    "op": "emit"
                }
            ]
        }
    ]

Tạo các pool mới và áp dụng các rule vừa tạo, như vậy dữ liệu sẽ chỉ đi vào class được chỉ định trong mỗi rule và pool

    ceph osd pool create ssdpool 128 128 replicated_ssd
    ceph osd pool create hddpool 128 128 replicated_hdd

Kiểm tra các pool mới tạo và 

    root@ceph01:~# ceph osd pool ls detail
    pool 7 'ssdpool' replicated size 3 min_size 1 crush_rule 2 object_hash rjenkins pg_num 128 pgp_num 128 autoscale_mode warn last_change 1214 flags hashpspool stripe_width 0
    pool 8 'hddpool' replicated size 3 min_size 1 crush_rule 1 object_hash rjenkins pg_num 128 pgp_num 128 autoscale_mode warn last_change 1217 flags hashpspool stripe_width 0
    
Như vậy `ssdpool` sẽ có id là 7 và `hddpool` sẽ có id là 8, kiểm tra trong `pg dump` để xem cụ thể OSD nào sẽ tương tác với pool nào.
- Các pg có số index là 7 (ssdpool) thì chúng sẽ sử dụng các osd có id = [0,2,4]
- Các pg có số index là 8 (hddpool) thì chúng sẽ sử dụng các osd có id = [1,3,5]

```
    8.70          0                  0        0         0       0     0           0          0    4        4 active+clean 2021-08-27 03:41:41.671181    1217'4   1217:14 [4,2,0]
    7.7f          0                  0        0         0       0     0           0          0    6        6 active+clean 2021-08-27 03:41:29.078938    1217'6   1217:19 [3,1,5]
    8.71          0                  0        0         0       0     0           0          0    0        0 active+clean 2021-08-27 03:41:41.676971       0'0   1216:10 [0,2,4]
    7.7e          0                  0        0         0       0     0           0          0    8        8 active+clean 2021-08-27 03:41:29.062753    1217'8   1217:21 [3,1,5]
    8.72          0                  0        0         0       0     0           0          0    6        6 active+clean 2021-08-27 03:41:41.699308    1217'6   1217:16 [2,4,0]
```

Benchmark kiểm tra với từng pool. Có thể thấy khi test từng pool thì chỉ có device có class thích hợp mới được hoạt động (ví dụ benchmark ssdpool thì chỉ sử dụng device có class sdd)

