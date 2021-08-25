## CRUSH map
CRUSH sử dụng CRUSH map để đưa xác định vị trí dữ liệu nên được lưu vào đâu trong OSD, rồi phân phối chúng dựa theo các replicate rule và failure domain.

CRUSH map chứa danh sách OSD, hệ thống phân cấp bao gồm các 'bucket' trong đó bao gồm các thiết bị và các rule quyết định xem CRUSH sẽ replicate dữ liệu như thế nào trong cluster.
Nằm cuối cùng của cây phân cấp này là lá (leaves) tức các thiết bị (OSD).
Phía trên nó là các bucket tương tự như mô hình tổ chức các thiết bị vật lý như: host, rack, row, room, và lên tiếp tới datacenter, region. Device và các bucket sẽ được làm rõ hơn tại phần cấu trúc phía sau.

![image](https://user-images.githubusercontent.com/83684068/130724909-3ab30d23-06f4-4183-aa1d-a11bcb5e82c2.png)

Bằng cách mô tả lại tổ chức của thiết bị vật lý, CRUSH có thể hình dung rõ hơn về khả năng lỗi của các thiết bị, cũng như cách đặt vị trí của failure domain mà không làm hỏng đi các phân phối (distribution) mong muốn.

## Cấu trúc CRUSH
### Device
Nằm cuối trong cây phân cấp, các device tượng trưng cho các OSD lưu trữ dữ liệu, thông thường là một OSD tương ứng một disk.
Các device này được xác định bởi `id` (một số nguyên không âm) và `tên`, thông thường sẽ là `osd.N` trong đó `N` là id thiết bị.

Kể từ bản Ceph Luminous, các device này có thêm một trường thông tin là `class` (ví dụ: HDD, SSD hoặc NVME), tạo thuận tiện hơn cho CRUSH khi áp dụng các rule.
Điều này cũng đặc biệt hữu ích có nhiều loại thiết bị trong cùng một máy chủ.

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

Một OSD khi được khởi tạo sẽ mặc định có `CRUSH location` là

    `root=default host=HOSTNAME (HOSTNAME sẽ là output của hostname -s)`

Tương tự như vậy, với một device (OSD) ở một hàng, giá, khung và máy chủ cụ thể và thuộc root 'default', thì CRUSH location của nó sẽ là:

    `root=default row=a rack=a2 chassis=a2b host=a2b5`
    














