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
Khi một OSD bị `down`, dữ liệu của nó sẽ bị lỗi thời so với các bản sao ở các PG khác. Khi OSD được `up` trở lại, dữ liệu của nó sẽ được update để phù hợp với trạng thái của cluster. Quá trình update này được thể hiện qua trạng thái `recovering`.

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

### Ví dụ
TH1: di chuyển location của một osd:

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

Do một OSD di chuyển location, nên nó cũng cần được `remapped` để client truy xuất.  

TH2: một OSD `down`, khi này sẽ có ít OSD hơn `replicate_size` của pool nên PG sẽ được đánh dấu `active+undersized`. Để loại bỏ trạng thái này thì cần đặt `osd pool default size = 2`, vì 2 là số OSD hiện còn hoạt động.

    pgs:     132/663 objects degraded (19.910%)
             197 active+clean
             177 active+undersized
             26  active+undersized+degraded

TH3: restart OSD, các PG cũng cần peer và active lại.

    pgs:     35.250% pgs not active
             48/663 objects degraded (7.240%)
             199 active+clean
             80  peering
             61  activating
             50  active+undersized
             10  active+undersized+degraded
