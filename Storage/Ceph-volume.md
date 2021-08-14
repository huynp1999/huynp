# Deploy OSD bằng ceph-volume

Tiện ích ceph-volume là một công cụ dành riêng cho việc triển khai các logical volume dưới dạng OSD. 
`ceph-volume` được tạo ra nhằm thay thế cho công cụ `ceph-disk` vốn phức tạp và kém linh hoạt. Tuy nhiên, quy trình hoạt động vẫn được dựa theo với các khâu từ chuẩn bị, kích hoạt và khởi động. Hiện tại, công cụ ceph-volume chỉ hỗ trợ plugin lvm, với kế hoạch hỗ trợ các công nghệ khác trong tương lai.

## Ceph-volume với plugin LVM
Bằng cách sử dụng các LVM flag, `lvm` sub-command hỗ trợ lưu trữ và tái khám phá bằng cách truy vấn các thiết bị được liên kết với OSD, để từ đó có thể được kích hoạt chúng.

Để sử dụng plugin LVM, cần phải thêm `lvm` làm sub-command (lệnh con) trong lệnh `ceph-volume`

    ceph-volume lvm
    
Trong đó lại có thêm 4 lệnh con

- `prepare`
- `activate`
- `create`
- `list`

### Prepare
Lệnh con này cho phép thiết lập với filestore hoặc bluestore. Bluestore objectstore được đặt làm mặc định với các OSD mới, vì phần nào linh hoạt hơn so với filestore.

Option `--bluestore` chấp nhận các thiết bị vật lý, phân vùng hoặc logical volume. Nếu cung cấp một thiết bị vật lý, thì logical volume sẽ được tạo. Một volume group cũng sẽ được tạo mới hoặc sử dụng lại, nếu đã có sẵn một vg có tên bắt đầu bằng `ceph`.

Các block được chỉ định bằng flag `--data`, ví dụ như với volume

    ceph-volume lvm prepare --bluestore --data vg/lv
    
hoặc với device

    ceph-volume lvm prepare --bluestore --data /path/to/device
    
`block.db` và `block.wal` là optinal trong bluestore, chúng có thể được chỉ định bằng `--block.db` và `--block.wal`.
Đây có thể là một thiết bị vật lý, một phân vùng hoặc một ổ đĩa hợp lý.

Trong khi tạo thư mục OSD, quy trình sẽ sử dụng một tmpfs mount để đặt tất cả các tệp cần thiết cho OSD. Các tệp này ban đầu được tạo bởi ceph-osd --mkfs và hoàn toàn là tạm thời.

Liên kết biểu tượng luôn được tạo cho thiết bị khối và tùy chọn cho block.db và block.wal. Đối với một cụm có tên mặc định và id OSD là 0, thư mục có thể trông giống như sau:


















