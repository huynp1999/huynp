Mục lục
- [CRUSH map](./CRUSH-map.md#crush-map)
- [Cấu trúc CRUSH map](./CRUSH-map.md#cấu-trúc-crush-map)
  - [Device](./CRUSH-map.md#device)
    - [Các lệnh với device class](./CRUSH-map.md#các-lệnh-với-device-class)
  - [Bucket](./CRUSH-map.md#bucket-type)
    - [Các lệnh của OSD với bucket](./CRUSH-map.md#các-lệnh-với-osd-và-bucket)
    - [Ví dụ](./CRUSH-map.md#ví-dụ)
  - [Rule](./CRUSH-map.md#rule)
    - [Các lệnh với rule](./CRUSH-map.md#các-lệnh-với-rule)
    - [Ví dụ](./CRUSH-map.md#ví-dụ-1) 
    - [Chỉnh sửa rule thủ công](./CRUSH-map.md#chỉnh-sửa-crush-rule-thủ-công)

## CRUSH map
CRUSH sử dụng CRUSH map để đưa xác định vị trí dữ liệu nên được lưu vào đâu trong OSD, rồi phân phối chúng dựa theo các replicate rule và failure domain.

CRUSH map chứa danh sách OSD, hệ thống phân cấp bao gồm các 'bucket' trong đó bao gồm các thiết bị và các rule quyết định xem CRUSH sẽ replicate dữ liệu như thế nào trong cluster.
Nằm cuối cùng của cây phân cấp này là lá (leaves) tức các thiết bị (OSD).
Phía trên nó là các bucket tương tự như mô hình tổ chức các thiết bị vật lý như: host, rack, row, room, và lên tiếp tới datacenter, region. Device và các bucket sẽ được làm rõ hơn tại phần cấu trúc phía sau.

![image](https://user-images.githubusercontent.com/83684068/130724909-3ab30d23-06f4-4183-aa1d-a11bcb5e82c2.png)

Bằng cách mô tả lại tổ chức của thiết bị vật lý, CRUSH có thể hình dung rõ hơn về khả năng lỗi của các thiết bị, cũng như cách đặt vị trí của failure domain mà không làm hỏng đi các phân phối (distribution) mong muốn.

## Cấu trúc CRUSH map
Cấu trúc của CRUSH bao gồm cá thông tin chính về device (OSD), device class, bucket (type), weight và các rule quyết định việc replicate.

### Device
Nằm cuối trong cây phân cấp, các thiết bị tượng trưng cho các OSD lưu trữ dữ liệu, thông thường là một OSD tương ứng một disk.
Các thiết bị này được xác định bởi `id` (một số nguyên không âm) và `tên`, thông thường sẽ là `osd.N` trong đó `N` là id thiết bị.

Kể từ bản Ceph Luminous, các device này có thêm một trường thông tin là `class` (ví dụ: HDD, SSD hoặc NVME), tạo thuận tiện hơn cho CRUSH khi áp dụng các rule.
Điều này cũng đặc biệt hữu ích có nhiều loại thiết bị trong cùng một máy chủ.

#### Các lệnh với device class
Theo mặc định khi khởi động, OSD tự động đặt class là hdd, ssd hoặc nvme tuỳ theo loại thiết bị mà chúng được triển khai trên đó.

- Chỉ định class cho OSD

        ceph osd crush set-device-class <class> <osd-name> [...]
        
- Sau khi class được đặt, nó sẽ là cố định và muốn thay đổi sẽ phải gỡ ra trước tiên, điều này giúp cho class được gắn thủ công thể không bị thay đổi tự động bởi OSD khi restart:

        ceph osd crush rm-device-class <osd-name> [...]
 
 - Xem thêm cách tạo rule cho từng class riêng biệt ở mục "Rule".
### Bucket (Type)
'Bucket' là thuật ngữ của CRUSH dành cho cho các node trong hệ thống tổ chức phân cấp các thiết bị: máy chủ (host), giá đỡ (rack), hàng (row), phòng (room), v.v... 

CRUSH map có sẵn các `type` dùng để mô tả các node này, bao gồm:
- `osd (or device)`
- `host`
- `chassis`
- `rack`
- `row`
- `pdu`
- `pod`
- `room`
- `datacenter`
- `zone`
- `region`
- `root`

#### Các lệnh với OSD và bucket
- Một OSD khi được khởi tạo sẽ mặc định có `CRUSH location` là:

        root=default host=HOSTNAME (HOSTNAME sẽ là output của hostname -s)

- Tương tự như vậy, với một device (OSD) ở một hàng, giá, khung và máy chủ cụ thể và thuộc root 'default', thì CRUSH location của nó sẽ là:

        root=default row=a rack=a2 chassis=a2b host=a2b5`

- Xem cây phân cấp CRUSH và *weight* của chúng sẽ được biểu thị theo đơn vị terabtye:

        ceph osd tree

- Add/move OSD vào CRUSH map theo các bucket bằng câu lệnh:

        ceph osd crush set {name} {weight} root={root} [{bucket-type}={bucket-name} ...]
    
- Xoá OSD khỏi CRUSH map

        ceph osd crush remove {name}
                
    
#### Ví dụ
Có 3 host trong một datacenter, mỗi host có 2 OSD. Host 1 nằm cùng ngăn (rack) với host 2, còn host 3 nằm khác hàng (row).

    ceph osd crush set osd.0 1.0 root=default datacenter=dc1 room=room1 row=row1 rack=rack1 host=host1
    tương tự với osd.1-osd.3...
    
Với host 3 sẽ cần tạo một row2 và chuyển nó vào room1, rồi mới chuyển các osd vào

    ceph osd crush add-bucket row2 row
    ceph osd crush move row2 root=default room=room1
    
    root@ceph01:~# ceph osd tree
    ID  CLASS WEIGHT  TYPE NAME                      STATUS REWEIGHT PRI-AFF
     -1       6.00000 root default
    -13       6.00000     datacenter dc1
    -12       6.00000         room room1
    -11       4.00000             row row1
    -10       4.00000                 rack rack1
     -9       2.00000                     host host1
      0   hdd 1.00000                         osd.0      up  1.00000 1.00000
      1   hdd 1.00000                         osd.1      up  1.00000 1.00000
    -19       2.00000                     host host2
      2   hdd 1.00000                         osd.2      up  1.00000 1.00000
      3   hdd 1.00000                         osd.3      up  1.00000 1.00000
     -3       2.00000             row row2
    -21       2.00000                 host host3
      4   hdd 1.00000                     osd.4          up  1.00000 1.00000
      5   hdd 1.00000                     osd.5          up  1.00000 1.00000

 Ngoài ra, có thể move cả một host vào rack riêng thay vì chuyển từng osd, ví dụ chuyển host2 sang cùng hàng với host3
    
    ceph osd crush move host2 root=default room=room1 row=row2


### Rule
CRUSH rule xác định cách thức dữ liệu được phân phối trên các thiết bị thuộc hệ thống phân cấp. Chúng xác định vị trí theo tính toán rồi sao chép hoặc phân phối. Các rule giúp chỉ định chính xác cách mà CRUSH đặt các bản sao dữ liệu.

Các CRUSH rule có thể được tạo bằng cách chỉ định loại hình mà mà chúng sẽ được sử dụng (replicated hoặc erasure coded (EC)), failure domain và có thể với cả device class

#### Các lệnh với rule
- Xem các rule được chỉ định trong cluster:

        ceph osd crush rule ls
- Xem nội dung của các rule đó:

        ceph osd crush rule dump

- Tạo replicated rule dành cho một device class cụ thể

        ceph osd crush rule create-replicated <rule-name> <root> <failure-domain> <class>

Trong đó:
- `<rule-name>` tên rule
- `<root>` thông thường sẽ là giá trị `default` tức node `root`
- `<failure-domain>` là bucket type thuộc node root dành cho việc replicate
  - Ví dụ failure domain là `host`, CRUSH sẽ đảm bảo mỗi bản sao của dữ liệu sẽ được lưu trên từng host riêng biệt
  - Còn nếu là `rack`, thì bản sao dữ liệu sẽ được lưu trên các rack khác nhau
  - Việc chọn failure domain tuỳ theo độ lớn của cluster
- `<class>` là device class (hdd, ssd, nvme)

- Xoá rule

        ceph osd crush rule rm {rule-name}

#### Ví dụ:
Tạo CRUSH rule mới và gán cho pool `rbd` để cho phép dữ liệu trong pool này chỉ được ghi vào một loại thiết bị cụ thể là hdd

    ceph osd crush rule create-replicated replicated_hdd default host hdd
    ceph osd pool set rbd crush_rule replicated_hdd

#### Chỉnh sửa CRUSH rule thủ công
Ngoài bằng câu lệnh thì cũng có thể chỉnh sửa các rule thủ công. (có thể làm với cả device, bucket, type)

Trước tiên cần phải lấy CRUSH map và decompile rồi mới có thể edit được:

    ceph osd getcrushmap -o {compiled-crushmap-filename}
    crushtool -d {compiled-crushmap-filename} -o {decompiled-crushmap-filename}
    
Sau khi edit thì compile và set CRUSH map vào lại cluster:

    crushtool -c {decompiled-crushmap-filename} -o {compiled-crushmap-filename}
    ceph osd setcrushmap -i {compiled-crushmap-filename}
    










