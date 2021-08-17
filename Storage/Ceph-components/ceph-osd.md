# ceph-osd
Là nơi lưu trữ và truy xuất dữ liệu thực (actual data) dưới dạng các object trong các ổ đĩa vật lí trên mỗi node của cluster. Một Ceph cluster bao gồm nhiều OSD và mỗi OSD deamon được gắn với một ổ đĩa vật lí.

Khi có hành động đọc ghi, client trước tiên cần yêu cầu một cluster map từ monitors, và về sau client sẽ trực tiếp tương tác với các OSD để thực hiện các tương tác mà không cần sự can thiệp của monitor. Điều này khiến qúa trình trao đổi dữ liệu diễn ra nhanh hơn, client có thế lưu trực tiếp tới OSD mà không cần bất kì lớp xử lí dữ liệu trung gian nào. 

RADOS đảm bảo tính năng replicate object trên các node trong cluster giúp luồng dữ liệu có tính sẵn sàng cao và khả năng chống lỗi. Theo đó, mỗi object trong OSD có một bản primary copy và một số secondary copy được phân bố đều trên các OSD khác. Mỗi OSD vừa đóng vai trò là primary OSD của một số object này, vừa có thể là secondary OSD của một số object khác. Khi ổ cứng xảy ra lỗi, OSD daemon sẽ so sánh với các OSD khác để thực hiện hành động recovery. Trong thời gian này, secondary OSD giữ bản sao của object bị lỗi sẽ được đẩy lên làm primary, đồng thời các bản sao mới sẽ được tạo trong qúa trình recover.

## Ceph OSD File System

<img src="https://user-images.githubusercontent.com/83684068/128716151-07579c7b-aaa6-4724-8ed6-974636f0cfac.png" alt="drawing" width="550"/>

Ceph OSD gồm 1 ổ cứng vật lý, Linux filesystem trên nó, và sau đó là Ceph OSD Service. Linux filesystem của Ceph cần hỗ trợ *extended attribute (XATTRs)*. Các thuộc tính của filesystem này cung cấp các thông tin về trạng thái object, metadata, snapshot và ACL cho Ceph OSD daemon, hỗ trợ việc quản lý dữ liêu.
Ceph OSD hoạt động trên ổ đĩa vật lý có phân vùng Linux. Phân vùng Linux có thể là Btrfs, XFS hay Ext4. Sự khác nhau giữa các filesystem này như sau:

- `Btrfs`: filesystem này cung cấp hiệu năng tốt nhất khi so với XFS hay ext4. Các ưu thế của Btrfs là hỗ trợ copy-on-write và writable snapshot, rất thuận tiện khi cung cấp VM và clone. Nó cũng hỗ trợ nén và checksum, và khả năng quản lý nhiều thiết bị trên cùng môt filesystem. Btrfs cũng hỗ trợ XATTRs, cung cấp khả năng quản lý volume hợp nhất gồm cả SSD, bổ xung tính năng fsck online. Tuy nhiên, btrfs vẫn chưa sẵn sàng để production.
- `XFS`: Đây là filesystem đã hoàn thiện và rất ổn định, và được khuyến nghị làm filesystem cho Ceph khi production. Tuy nhiên, XFS không thế so sánh về mặt tính năng với Btrfs. XFS có vấn đề về hiệu năng khi mở rộng metadata, và XFS là một journaling filesystem, có nghĩa, mỗi khi client gửi dữ liệu tới Ceph cluster, nó sẽ được ghi vào journal trước rồi sau đó mới tới XFS filesystem. Nó làm tăng khả năng overhead khi dữ liệu được ghi 2 lần, và làm XFS chậm hơn so với Btrfs, filesystem không dùng journal.
- `Ext4`: đây cũng là một filesystem dạng journaling và cũng có thể sử dụng cho Ceph khi production; tuy nhiên không phổ biến bằng XFS. Ceph OSD sử dụng *extended attribute* của filesystem cho các thông tin của object và metadata. XATTRs cho phép lưu các thông tin liên quan tới object dưới dạng `xattr_name` và `xattr_value`, do vậy cho phép *tagging* object với nhiều thông tin metadata hơn. ext4 file system không cung cấp đủ dung lượng cho XATTRs do giới hạn về dung lượng bytes cho XATTRs. XFS có kích thước XATTRs lớn hơn.

# Kiểm tra kết nối giữa các OSD
Trước tiên cần kiểm tra PID của các OSD trên node, ví dụ ở đây là osd.0 và osd.1 tương ứng với 1669 và 1665

    root@ceph01:~# ps aux
    ceph        1665  1.2  6.2 898584 121852 ?       Ssl  08:39   0:05 /usr/bin/ceph-osd -f --cluster ceph --id 1 --setuser ceph --setgroup ceph
    ceph        1669  1.2  5.7 889360 111396 ?       Ssl  08:39   0:05 /usr/bin/ceph-osd -f --cluster ceph --id 0 --setuser ceph --setgroup ceph

2 OSD của node ceph01 listen theo 8 port từ 6800 đến 6807, tức 4 port cho mỗi OSD
    
    root@ceph01:~# netstat -nlp | grep ceph-osd
    tcp        0      0 10.10.10.21:6800        0.0.0.0:*               LISTEN      1665/ceph-osd
    tcp        0      0 10.10.10.21:6801        0.0.0.0:*               LISTEN      1665/ceph-osd
    tcp        0      0 10.10.10.21:6802        0.0.0.0:*               LISTEN      1665/ceph-osd
    tcp        0      0 10.10.10.21:6803        0.0.0.0:*               LISTEN      1665/ceph-osd
    tcp        0      0 10.10.10.21:6804        0.0.0.0:*               LISTEN      1669/ceph-osd
    tcp        0      0 10.10.10.21:6805        0.0.0.0:*               LISTEN      1669/ceph-osd
    tcp        0      0 10.10.10.21:6806        0.0.0.0:*               LISTEN      1669/ceph-osd
    tcp        0      0 10.10.10.21:6807        0.0.0.0:*               LISTEN      1669/ceph-osd
    unix  2      [ ACC ]     STREAM     LISTENING     31791    1665/ceph-osd        /var/run/ceph/ceph-osd.1.asok
    unix  2      [ ACC ]     STREAM     LISTENING     31796    1669/ceph-osd        /var/run/ceph/ceph-osd.0.asok

Sau khi đã biết port tương ứng với 2 PID OSD, chuyển sang node ceph02 để kiểm tra các port đã được thiết lập thành công chưa.

Cụ thể kiểm tra port 6802 của osd.1 đã thiết lập kết nối thành công tới osd.2 và osd.3 (tương ứng PID 1611 và 1607 của ceph02) thông qua qua 2 port 58160 và 58056.

    root@ceph02:~# ps aux
    ceph        1607  1.0  5.9 894480 116036 ?       Ssl  08:39   0:15 /usr/bin/ceph-osd -f --cluster ceph --id 3 --setuser ceph --setgroup ceph
    ceph        1611  1.0  5.9 894480 116752 ?       Ssl  08:39   0:16 /usr/bin/ceph-osd -f --cluster ceph --id 2 --setuser ceph --setgroup ceph

    root@ceph02:~# netstat -ap | grep ceph01:6802
    tcp        0      0 ceph02:58160            ceph01:6802             ESTABLISHED 1611/ceph-osd
    tcp        0      0 ceph02:58056            ceph01:6802             ESTABLISHED 1607/ceph-osd

Với các port khác của các osd trong các node cũng kiểm tra tương tự.
