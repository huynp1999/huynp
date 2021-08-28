Tính sẵn sàng và độ tin cậy cao đòi hỏi khả năng chịu lỗi trong việc quản lý các vấn đề về phần cứng lẫn phần mềm.
Ceph không có *single point-of-failure* và vẫn có thể phục vụ dữ liệu khi ở chế độ "degraded".
Data placement trong Ceph sử dụng một lớp điều hướng để đảm bảo rằng dữ liệu không phụ thuộc hay liên kết với các địa chỉ OSD cụ thể.
Như vậy thì việc quản trị các lỗi hệ thống đòi hỏi phải tìm đến các Placement Group (PGs) và các OSD bên dưới để tìm ra gốc rễ của vấn đề.

## Monitoring OSD
Các trạng thái của một OSD trong cluster có thể là:
- `in` trong cluster
- `out` ngoài cluster
- `up` đang hoạt động
- `down` không hoạt động

Kiểm tra tổng quan các OSD, câu lệnh sẽ cho biết tổng số `x` OSD, bao nhiêu `up` (y), bao nhiêu `in` (z) và epoch là số lần map được thay đổi?

    # ceph osd stat
    x osds: y up, z in; epoch: eNNNN

Nếu số OSD `in` lớn hơn `up` thì dùng lệnh sau để làm rõ cái nào không hoạt động: (kham khảo tại [đây](https://docs.ceph.com/en/latest/rados/troubleshooting/troubleshooting-osd/#osd-not-running) nếu không bật thủ công lại đuợc):

    ceph osd tree

Có thể bật lại thủ công bằng câu lệnh `sudo systemctl start ceph-osd@1`, tuy nhiên thông thường khi OSD được set trạng thái `down` thì có nghĩa chúng cần thời gian restart và phục hồi trở lại, cụ thể những trường hợp:
1. Do vừa start hoặc restart cluster nên nó có thể chưa sẵn sàng hoạt động được ngay, vì các PG cần thời gian khởi tạo và các OSD đang trong quá trình liên kết với nhau.
2. Thêm hoặc xóa OSD, CRUSH cần thời gian phân phát PG cho các OSD khác.
3. Cluster map vừa được sửa đổi.








