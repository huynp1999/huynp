## Trạng thái bảo trì
Một hệ thống trên thực tế sẽ cần thực hiện bảo trì, nâng cấp và sửa lỗi, giải quyết sự cố trong failure domain.
Các mức độ bảo trì có thể trên một osd, một rack, hay toàn bộ cluster.

Tuy nhiên không thể ngắt bỏ hay thay thế ngay lập tức một OSD hay một host được, vì cluster đang trong quá trình hoạt động và client thì đang ghi dữ liệu.
Trước khi thực hiện các hành động bảo trì, cần tắt tính năng tự động cân bằng của CRUSH bằng flag `noout`, ví dụ đối với một OSD cụ thể:

    ceph osd add-noout osd.0
    ceph osd rm-noout  osd.0
    
Hay ví dụ cần add thêm RAM ở một bucket tên `ceph-data1701`:

    ceph osd set-group noout ceph-data1701
    ceph osd unset-group noout ceph-data1701

Hoặc có thể là toàn bộ cluster:

    ceph osd set noout
    ceph osd unset noout
    
Sau khi flag đã được set hoàn tất, có thể dừng các OSD hoặc các service khác trong failure domain để tiến hành bảo trì.

    systemctl stop ceph-@...
    
## Use case
### 1. Reboot, bảo trì một node
Tắt tạm thời auto rebalancing

    ceph osd set noout
    noout is set
    ceph -s
      cluster:
        id:     xxx
        health: HEALTH_WARN
                noout flag(s) set
    [...]

Sau khi khởi động lại node hoàn tất, unset các flag để trở về trạng thái bình thường

    ceph osd unset noout
    noout is unset
    ceph -s
      cluster:
        id:     xxx
        health: HEALTH_OK
    [...]

### 2. Stop, start cluster
Set các OSD flag, tránh cho việc dữ liệu bị 

    ceph osd set noout
    ceph osd set nobackfill
    ceph osd set norecover
    ceph osd set norebalance
    ceph osd set nodown
    ceph osd set pause
    ceph -s
      cluster:
      [...]
        health: HEALTH_WARN
                pauserd,pausewr,nodown,noout,nobackfill,norebalance,norecover flag(s) set

      services:
      [...]
        osd: x osds: y up, z in
             flags pauserd,pausewr,nodown,noout,nobackfill,norebalance,norecover

Dừng các service theo thứ tự mgr -> osd -> mon: (node by node)

    sudo systemctl stop ceph-mgr\*.service
    sudo systemctl stop ceph-osd\*.service
    sudo systemctl stop ceph-mon\*.service

Khởi động theo thứ tự mon -> osd -> mgr: (node by node)

    sudo systemctl start ceph-mon\*.service
    systemctl start ceph-osd@DEVICE.service
    sudo systemctl start ceph-mgr\*.service

Unset các flag

    ceph osd unset pause
    ceph osd unset nodown
    ceph osd unset norebalance
    ceph osd unset norecover
    ceph osd unset nobackfill
    ceph osd unset noout

