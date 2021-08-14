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
Có thể thấy các OSD của node ceph01 lăng nghe theo 8 port từ 6800 đến 6807, tức 4 port cho mỗi osd.0 và osd.1

    root@ceph01:~# netstat -nlp | grep ceph
    tcp        0      0 10.10.11.21:6807        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.10.21:6807        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.11.21:6800        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.10.21:6800        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.11.21:6801        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.10.21:6801        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.11.21:6802        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.10.21:6802        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.11.21:6803        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.10.21:6803        0.0.0.0:*               LISTEN      1833/ceph-osd
    tcp        0      0 10.10.11.21:6804        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.10.21:6804        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.11.21:6805        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.10.21:6805        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.11.21:6806        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp        0      0 10.10.10.21:6806        0.0.0.0:*               LISTEN      1834/ceph-osd
    tcp6       0      0 :::8443                 :::*                    LISTEN      1103/ceph-mgr
    unix  2      [ ACC ]     STREAM     LISTENING     30292    1029/ceph-mon        /var/run/ceph/ceph-mon.ceph01.asok
    unix  2      [ ACC ]     STREAM     LISTENING     33901    1103/ceph-mgr        /var/run/ceph/ceph-mgr.ceph01.asok
    unix  2      [ ACC ]     STREAM     LISTENING     33920    1834/ceph-osd        /var/run/ceph/ceph-osd.0.asok
    unix  2      [ ACC ]     STREAM     LISTENING     33925    1833/ceph-osd        /var/run/ceph/ceph-osd.1.asok

Kiểm tra tại node ceph02 thì có thể thấy các port của osd.0 và osd.1 đã được thiết lập thành công

    root@ceph02:~# netstat -a | grep ceph01
    tcp        0      0 ceph02:34190            ceph01:6808             ESTABLISHED
    tcp        0      0 ceph02:46662            ceph01:6800             ESTABLISHED
    tcp        0      0 ceph02:34198            ceph01:6808             ESTABLISHED
    tcp        0      0 ceph02:46598            ceph01:6800             ESTABLISHED
    tcp        0      0 ceph02:6806             ceph01:47740            ESTABLISHED
    tcp        0      0 ceph02:3300             ceph01:39372            ESTABLISHED
    tcp        0      0 ceph02:6802             ceph01:41282            ESTABLISHED
    tcp        0      0 ceph02:6802             ceph01:41328            ESTABLISHED
    tcp        0      0 ceph02:34192            ceph01:6808             ESTABLISHED
    tcp        0      0 ceph02:6800             ceph01:42020            ESTABLISHED
    tcp        0      0 ceph02:6806             ceph01:47684            ESTABLISHED
    tcp        0      0 ceph02:3300             ceph01:39586            ESTABLISHED
    tcp        0      0 ceph02:37310            ceph01:6802             ESTABLISHED
    tcp        0      0 ceph02:34194            ceph01:6808             ESTABLISHED
    tcp        0      0 ceph02:46976            ceph01:3300             ESTABLISHED
    tcp        0      0 ceph02:6804             ceph01:41894            ESTABLISHED
    tcp        0      0 ceph02:58576            ceph01:6804             ESTABLISHED
    tcp        0      0 ceph02:58558            ceph01:6804             ESTABLISHED
    tcp        0      0 ceph02:49590            ceph01:6806             ESTABLISHED
    tcp        0      0 ceph02:49592            ceph01:6806             ESTABLISHED
    tcp        0      0 ceph02:34196            ceph01:6808             ESTABLISHED
    tcp        0      0 ceph02:37282            ceph01:6802             ESTABLISHED
