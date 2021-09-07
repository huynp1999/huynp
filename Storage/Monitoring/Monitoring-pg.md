## PG state
Khi mà trạng thái của cluster không còn là `HEALTH OK`, ngoài trạng thái hoạt động của OSD thì sẽ cần kiểm tra cả trạng thái của các PG (PG state). Cụ thể trong những trường hợp sau:
1. Vừa tạo một pool và PG chưa được chỉ định.
2. Các PG đang trong thời gian khôi phục (recovery).
3. Vừa thêm hoặc xoá OSD trong cluster.
4. CRUSH map vừa được sửa đổi và các PG đang migrating với location mới.
5. Các bản sao (replica) một PG đang không nhất quán.
6. Ceph đang sử dụng các bản sao của một PG.
7. Ceph không còn đủ dung lượng lưu trữ cho quá trình migrate

Kiểm tra tổng quan trạng thái các pg, trong đos `384` là tổng số các pg và cũng có `384` pg đang trong trạng thái `active+clean`, phần còn lại về lượng dữ liệu lưu trữ.

    # ceph pg stat
    384 pgs: 384 active+clean; 1.6 KiB data, 517 MiB used, 113 GiB / 120 GiB avail
    
Các PG state cụ thể hơn như sau.
### Creating, peering, active, clean
Khi mới tạo mội pool mới, nó cần một thời gian ngắn để tạo ra lượng PG theo chỉ định và Ceph sẽ thông báo trạng thái PG là `creating`.

Ví dụ khi tạo một pool mới với 16 pg:

    pgs:     4.000% pgs not active
             384 active+clean
             16  creating+peering

Sau khi tạo xong sẽ là bước quảng bá các pg vừa được tạo cho các OSD (`peering`), các OSD này sẽ được đưa ra để cùng thống nhất về các object và metadata trong PG.

Sau khi hoàn tất 2 bước trên, PG state sẽ phải là `active+clean` tức client đã có thể tiến hành ghi vào PG.
- `active` có nghĩa đã sẵn sàng để đọc và ghi dữ liệu trong primary OSD và các replica OSD
- `clean` có nghĩa là các OSD đã thống nhất được với nhau và không có replica nào rời rạc.

![image](https://user-images.githubusercontent.com/83684068/131282020-e69a1cec-baaa-4238-bae2-107a703c6a2e.png)

### Degraded
Khi client ghi dữ liệu vào primary OSD, primary OSD có trách nhiệm tạo các bản sao và ghi vào replica OSD. Trong thời gian này, PG sẽ ở trong trạng thái `degraded` cho tới khi primary OSD nhận được thông báo đã tạo các bản sao thành công. Một trường hợp `degraded` nữa là Ceph không tìm thấy một hoặc nhiều object dữ liệu mà đáng ra nên ở PG này. Ngoài những object không tìm được ra thì các object khác vẫn có thể được truy xuất trong PG `degraded` này.

Trạng thái `active+degraded` xảy ra ở PG khi một OSD vẫn đang sẵn sàng ghi và sao lưu dữ liệu (active), nhưng nó lại không được đồng bộ replica với các OSD khác (degraded). Các PG thuộc OSD này sẽ bị đánh dấu `degraded`, tuy nhiên client vẫn có thể ghi dữ liệu vào.

Đối với một OSD ở cả hai trạng thái `degraded` và `down`, thì cũng nghĩa OSD này đã `out`. Dữ liệu của OSD khi `down` sẽ được chuyển sang các OSD khác.

### Recovering
Khi một OSD bị `down`, dữ liệu của nó sẽ bị lỗi thời so với các bản sao ở các PG khác. Khi OSD được `up` trở lại, dữ liệu của nó sẽ được update và sửa lại để phù hợp với trạng thái của cluster. Quá trình update này được thể hiện qua trạng thái `recovering`.

### Back filling
Khi một OSD mới được tạo trong cluster, CRUSH sẽ tái phân phát lại các PG đang có sẵn ở các OSD cũ tới OSD mới được thêm vào. Quá trình này gọi là back filling, thực hiện việc tái phân phát PG khi có một OSD được thêm hoặc bị xoá.

Việc bắt một OSD mới chấp nhận các PG ngay lập tức có thể khiến nó bị quá tải. 

Một số trạng thái xảy ra trong quá trình backfill:
- `backfill_wait` đang chờ, chưa được backfill
- `backfilling` đang tiến hành backfill
- `backfill_toofull` không thể hoàn tất backfill vì không đủ không gian lưu trữ. Khi một PG không thể được backfill, nó sẽ được đánh trạng thái `incomplete`. Tuy nhiên trạng thái này có thể chỉ là tạm thời, vì các PG sẽ di chuyển xung quanh cluster và làm trống bộ nhớ.

### Remapped
Khi chuyển giao vị trí primary của 2 OSD, dữ liệu được migrate từ primary OSD cũ sang primary OSD mới. Quá trình migrate có thể sẽ cần một lúc, trong thời gian này primary cũ tiếp tục phục vụ các request cho tới khi migrate các PG hoàn tất. Toàn bộ tiến trình này được gọi là remmaped, khi remmaped hoàn tất sẽ sử dụng primary OSD mới làm nơi phục vụ request từ client

### Stale
Ceph kiểm tra heartbeat để đảm bảo các host và daemon đang hoạt động, ceph-osd daemon có thể bị lỗi nào đó khiến cho nó không thể trả về heartbeat kịp thời cho cluster (ví dụ như mất kết nối mạng tạm thời). Trạng thái `stale` thường xảy ra khi mới khởi động cluster cho tới khi tiến trình `peering` hoàn tất. Còn đối với một cluster đang hoạt động, một PG trong trạng thái `stale` tức là primary OSD của PG đó đã bị `down` hoặc không thể báo cáo tình hình PG lại cho monitor.

### Inconsistency
Ceph quản lý và cập nhật checksums của các object được lưu trữ trong cụm. Một quá trình gọi là **deep srub** được dùng để tính toán checksum các replica của một object. Nếu checksum của một replica không khớp với bản sao thẩm quyền (authoritative copy), thì replica này sẽ được coi không nhất quán (inconsistency copy).

Để sửa chữa một PG không nhất quán, trước tiên cần phải biết chính xác id của nó:

    # ceph health detail
    ....
    pg 11.eeef is active+clean+inconsistent, acting [106,427,854]
    pg 5.ee92 is active+clean+inconsistent, acting [247,183,125]
    ....

Sử dụng `ceph pg repair` để sửa chữa một PG không nhất quán, câu lệnh này sẽ ghi đè authoritative copy lên trên inconsistent copy. 

    ceph pg repair 11.eeef

### Bảng tổng quan PG state

| Trạng   thái PG | Mô tả                                                                                                                | Nguyên nhân                                                                                                | Khắc phục                                                                                                                  |
|-----------------|----------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
| Creating        | PG đang được khởi tạo cho pool mới                                                                                 | Vừa tạo pool mới                                                                                           | Ceph tự động                                                                                                               |
| Peering         | Quảng bá, phân phát các PG vừa tạo cho các OSD                                                                     | OSD vừa start hoặc restart, vừa tạo pool mới,CRUSH map vừa được thay đổi                          | Ceph tự động                                                                                                               |
| Activating      | Khởi động PG, đưa vào phục vụ các request                                                                          | OSD vừa start hoặc restart, vừa tạo pool mới, CRUSH map vừa được thay đổi                          | Ceph tự động                                                                                                               |
| Active          | PG đã sẵn sàng để đọc và ghi dữ liệu                                                                               |                                                                                                            |                                                                                                                            |
| Clean           | PG tại các OSD đã thống nhất được với nhau và không có replica nào rời rạc.                                        |                                                                                                            |                                                                                                                            |
| Unclean         | Trong PG có chứa các object mà chưa đủ số lượng replicate theo quy định, và cản trở việc recover                   | PG không tìm được object cần thiết để recover (`unfound`), có OSD bị `down`, cấu hình sai        | Troubleshoot với OSD. Chỉnh lại file cấu hình, osd pool default size nên được để > 1 và < tổng số OSD trong cluster. |
| Inactive        | PG không thể phục vụ các yêu cầu đọc/ghi                                                                           | Quá trình peering gặp vấn đề                                                                             | Troubleshoot với OSD (`ceph osd df tree`)                                                                                |
| Degraded        | PG đang trong quá trình replicate PG không tìm thấy object                                                    | Cluster mới được khởi động, có OSD bị `down`, CRUSH map vừa được thay đổi                          | Ceph sẽ tự tiến hành `remapped`   khi CRUSH map được thay đổi                                                              |
| Undersized      | Cluster hiện có it OSD hơn `replicate size` của pool                                                               | Có OSD bị `down`                                                                                           | Troubleshoot OSD (`ceph osd df tree`). Sửa lại `osd pool default size` bằng với số lượng OSD hiện tại                |
| Back Filling    | CRUSH đang trong quá trình tái phân phát lại các PG từ OSD cũ sang mới, hoặc từ OSD bị lỗi sang các OSD còn   lại. | Khi có OSD được thêm hoặc bị xoá khỏi cluster. Khi OSD được thay đổi CRUSH location.                | Ceph tự động                                                                                                               |
| Remapped        | Các OSD đang trong quá trình chuyển giao vị trí primary cho nhau                                                   | Khi OSD được thay đổi CRUSH location.                                                                    | Ceph tự động                                                                                                               |
| Stale           | Monitor không nhận được update trạng thái (heartbeat) từ primary OSD của PG.                                       | Khi cluster mới được khởi động và đang peering. Nếu trạng thái kéo dài, tức là primary OSD đã `down` | Ceph tự động. Troubleshoot OSD (`ceph osd df tree`)                                                                    |
| Inconsistency   | Object trong PG đang không nhất quán với các replica khác                                                          | Phần cứng của OSD không ổn định                                                                          | Sử dụng câu lệnh `ceph pg repair [pgid]`. Kiểm tra, thay thế phần cứng                                               |
| Deep Scrubbing  | Thực hiện checksum các replica của các object, kiểm tra nhất quán                                                  | Thường xuất hiện kèm với trạng thái `inconsistent`                                                       | Ceph tự động                                                                                                               |
| Unfound         | PG biết nhưng không tìm thấy object                                                                                | Do gián đoạn trong quá trình recover. Gây ra trạng thái `unclean`                                    | Xem cách khắc phục của `unclean`                                                                                           |

## Troubleshooting
TH1: di chuyển location của một osd, nên các PG cũng cần được `remapped` để client truy xuất.  

    pgs:     3.500% pgs not active
             17/663 objects degraded (2.564%)
             5/663 objects misplaced (0.754%)
             374 active+clean
             13  remapped+peering
             5   active+recovery_wait+undersized+degraded+remapped
             5   active+remapped+backfill_wait
             1   active+recovering+degraded
             1   active+recovering+undersized+degraded+remapped
             1   peering

TH2: một OSD `down`, khi này sẽ có ít OSD hơn `replicate_size` của pool nên PG sẽ được đánh dấu `active+undersized`. Để loại bỏ trạng thái này thì cần đặt `osd pool default size = 2`, vì 2 là số OSD hiện còn hoạt động.

    pgs:     132/663 objects degraded (19.910%)
             197 active+clean
             177 active+undersized
             26  active+undersized+degraded

TH3: restart OSD, các PG cũng cần re-peer và active trở lại.

    pgs:     35.250% pgs not active
             48/663 objects degraded (7.240%)
             199 active+clean
             80  peering
             61  activating
             50  active+undersized
             10  active+undersized+degraded

TH4: một PG bị lỗi đồng bộ `inconsistent`, `scrubbing+deep` có nghĩa Ceph đang kiểm tra các object và đối chứng với các replica để đảm bảo tính nhất quán. PG này có thể fix bằng `ceph pg repair [pgid]`.

    health: HEALTH_ERR
             1 scrub errors
             Possible data damage: 1 pg inconsistent
    ...
    pgs:     4320 active+clean
             7    active+clean+scrubbing+deep
             1    active+clean+scrubbing+deep+inconsistent
             
TH5: PG bị `stale`, có nghĩa monitor không nhận được update trạng thái (heartbeat) từ primary OSD của PG đó. Trạng thái `stale` thường xuất hiện khi cluster mới được khởi động và đang peering. Nếu trạng thái này kéo dài, có nghĩa primary OSD đã bị `down`, khi OSD này `up` trở lại nó sẽ tự phục hồi PG.
 
    HEALTH_WARN 24 pgs stale; 3/300 in osds are down
    ...
    pg 2.5 is stuck stale+active+remapped, last acting [2,0]
    ...
    osd.10 is down since epoch 23, last address 192.168.106.220:6800/11080
    osd.11 is down since epoch 13, last address 192.168.106.220:6803/11539
    osd.12 is down since epoch 24, last address 192.168.106.220:6806/11861
    
TH6: PG bị `unclean` hoặc `inactive`, nghĩa là có gì đó cản trở việc replicate object, hoặc việc serve request của PG, nguyên nhân thường thấy là do OSD `down`.

    HEALTH_WARN 197 pgs stuck unclean
    
    HEALTH_WARN 197 pgs stuck inactive
TH7: khi một OSD lỗi khiến cho PG không thực hiện được `peering`, thì chúng sẽ bị đánh dấu là `down` theo.

    HEALTH_ERR 7 pgs degraded; 12 pgs down; 12 pgs peering; 1 pgs recovering; 6 pgs stuck unclean; 114/3300 degraded (3.455%); 1/3 in osds are down
    ...
    pg 0.5 is down+peering
    pg 1.4 is down+peering
    ...
    osd.1 is down since epoch 69, last address 192.168.106.220:6801/8651
TH8: object trong PG bị đánh dấu `unfound`, ví dụ trong trường hợp:
1. `osd.1` bị `down`, trong lúc đó dữ liệu đang được ghi vào `osd.2`.
2. Khi `osd.1` up trở lại và peering thì sẽ thấy những object mới được ghi và tạo tiến trình phục hồi `recovering`.
3. Nhưng trong quá trình phục hồi thì `osd.2` lại `down`.
4. Lúc này `osd.1` vẫn biết các object mới nằm ở đó nhưng không thể lấy được, các object này sẽ được đánh dấu là `unfound`.

Có thể kiểm tra PG nào chứa `unfound` object bằng `ceph health detail`, ở đây là `pg 3.8a5`:

    HEALTH_WARN 1 pgs recovering; 1 pgs stuck unclean; recovery 5/937611 objects degraded (0.001%); 1/312537 unfound (0.000%)
    pg 3.8a5 is stuck unclean for 803946.712780, current state active+recovering, last acting [320,248,0]
    pg 3.8a5 is active+recovering, acting [320,248,0], 1 unfound
    recovery 5/937611 objects degraded (0.001%); **1/312537 unfound (0.000%)**
