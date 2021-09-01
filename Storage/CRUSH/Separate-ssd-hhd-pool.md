## Cách 1: Tạo 2 rule cho 2 class HDD và SSD, set 2 pool tương ứng với 2 rule đó.
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

Benchmark kiểm tra với từng pool. Có thể thấy khi test từng pool thì chỉ có device có class thích hợp mới được hoạt động

Ví dụ benchmark ssdpool thì chỉ sử dụng device có class sdd

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/benchssd.png)

Tương tự với hddpool

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/benchdd.png)

## Cách 2: Tách các osd có class ssd ra một ssd root riêng và tạo rule cho root đó. Như vậy root default sẽ trở thành hdd root. 
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

Tạo 1 root bucket mới cho ssd pool (ssds)
    
    ceph osd crush add-bucket ssds root

Tạo các host bucket dành cho ssd và move vào root vừa tạo

    ceph osd crush add-bucket ceph01-ssd host
    ceph osd crush move ceph01-ssd root=ssdroot

Chuyển OSD ssd mới và move tới root ssd bước 1

    ceph osd crush set osd.1 1 root=ssdroot host=ceph01-ssd

(Optional) Cấu hình `ceph.conf` trên 3 node để location ko bị reset về default

    [osd]
    osd crush update on start = false
    [osd.1]
    host = ceph01
    crush_location = root=ssdroot host=ceph01-ssd
    
Tạo pool ssd

    ceph osd pool create ssdpool 128 128

Tạo rule cho root ssd theo cú pháp

    ceph osd crush rule create-simple ssdrule ssds host
    
    ceph osd crush rule create-simple {rulename} {root} {failure-domain}
    
Gắn rule cho pool ssd

    ceph osd pool set ssdpool crush_rule ssdrule 

Kiểm tra ceph osd tree

    root@ceph01:~# ceph osd tree
    ID  CLASS WEIGHT  TYPE NAME                      STATUS REWEIGHT PRI-AFF
    -37       3.00000 root ssdroot
    -38       1.00000     host ceph01-ssd
      1   ssd 1.00000         osd.1                      up  1.00000 1.00000
    -39       1.00000     host ceph02-ssd
      3   ssd 1.00000         osd.3                      up  1.00000 1.00000
    -40       1.00000     host ceph03-ssd
      5   ssd 1.00000         osd.5                      up  1.00000 1.00000
     -1       3.00000 root default
    -33       1.00000     host ceph01
      0   hdd 1.00000         osd.0                      up  1.00000 1.00000
     -8       1.00000     host ceph02
      2   hdd 1.00000         osd.2                      up  1.00000 1.00000
     -5       1.00000     host ceph03
      4   hdd 1.00000         osd.4                      up  1.00000 1.00000

Kiểm tra crush rule và các pool

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
            "rule_id": 3,
            "rule_name": "ssdrule",
            "ruleset": 3,
            "type": 1,
            "min_size": 1,
            "max_size": 10,
            "steps": [
                {
                    "op": "take",
                    "item": -37,
                    "item_name": "ssdroot"
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

    root@ceph01:~# ceph osd pool ls detail
    pool 19 'ssdpool' replicated size 3 min_size 1 crush_rule 3 object_hash rjenkins pg_num 128 pgp_num 128 autoscale_mode warn last_change 1657 flags hashpspool stripe_width 0
    pool 20 'rbdpool' replicated size 3 min_size 1 crush_rule 0 object_hash rjenkins pg_num 128 pgp_num 128 autoscale_mode warn last_change 1656 flags hashpspool stripe_width 0

Dựa vào các thông tin trên:
- Các ssd được tách ra với `root ssdroot` và có một rule và pool dành riêng cho ssd.
- Các hdd còn lại ở root default nên root này mặc định sẽ dành riêng cho hdd.

Khác biệt giữa 2 cách:
- Đối với cách 1: rule sẽ phân biệt hdd và ssd thông qua 2 class là `ssd` và `hdd`.
- Đối với cách 2: rule sẽ phân biệt dựa trên 2 root là `root=ssdroot` và `root=default`

Benchmark cách 2 sẽ cho tốc độ ghi dữ liệu nhanh hơn cách 1 theo cả ssd lẫn hdd:

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/benchss2.PNG)

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/benchhdd2.PNG)
