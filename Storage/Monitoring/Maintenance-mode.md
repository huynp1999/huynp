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
 
Các flag khác có chung mục đích dành cho việc bảo trì:
| Flag                       | Mô tả                                                                                                                                                                                                                                                  |
|----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `noout`                    | Sau một thời gian cố định (`osd mon report interval`), nếu OSD không báo cạo được tình trạng lại cho monitor, nó sẽ bị đánh dấu là `out` khỏi cluster. Vậy nên `noout` thường được dùng trong quá trình troubleshoot OSD mà không bị monitor hiểu lầm. |
| `nodown`                   | Các sự cố về mạng có thể gây gián đoạn heartbeat của Ceph, một OSD đang `up` nhưng sẽ có thể bị đánh dấu `down`. Set `nodown` để tránh monitor hiểu lầm trong quá trình troubleshoot OSD.                                                              |
| `full`                     | Khi cluster chạm tới tỉ lệ `full_ratio`, ceph sẽ chặn quá trình ghi dữ liệu lại. Flag `full` được dùng để ngăn chặn trường hợp trên và mở rộng dung lượng.                                                                                             |
| `pause`                    | Flag này dùng để ngăn client truy xuất dữ liệu trong quá trình troubleshoot.                                                                                                                                                                           |
| `nobackfill`               | Khi một OSD hoặc một node bị down tạm thời (ví dụ khi thay thế phần cứng, nâng cấp hệ điều hành), set `nobackfill` để Ceph không thực hiện backfill trong khi các OSD `down`.                                                                          |
| `nonrebalance`             | Ngăn chặn việc PG bị phân tán ra các OSD khác trong quá trình thay thế một OSD disk.                                                                                                                                                                   |
| `norecover`                | Tắt tính tăng tự phục hồi từ các OSD khác trong thời gian troubleshoot                                                                                                                                                                                 |
| `noscrub`, `nodeep-scrubb` | Flag này được dùng để ngăn chặn quá trình deep scrub tự động, nhằm giảm tải cho các hoạt động khác như recovery, backfilling, rebalancing,...                                                                                                          |
## Use cases
### 1. Reboot một node
Tắt tạm thời auto rebalancing

    ceph osd set noout
    noout is set
    ceph osd set norebalance
    norebalance is set
    ceph -s
      cluster:
        id:     xxx
        health: HEALTH_WARN
                noout,norebalance flag(s) set
    [...]

Sau khi khởi động lại node hoàn tất, unset các flag để trở về trạng thái bình thường

    ceph osd unset noout
    noout is unset
    ceph osd unset norebalance
    norebalance is unset
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

