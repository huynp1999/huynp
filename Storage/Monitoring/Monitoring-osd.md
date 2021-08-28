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

Nếu một OSD đang là `up`, thì nó có thể đang nằm trong cluster (tức là có thể đọc và ghi dữ liệu) hoặc nằm ngoài cluster (`out`).
Nếu một OSD từng nằm trong cluster và gần đây đã được chuyển ra khỏi cluster, Ceph sẽ tự động di chuyển các PG sang cho các OSD khác.
Với OSD nằm ngoài cluster, CRUSH sẽ không chỉ định các PG cho OSD này. Và với OSD không hoạt động (`down`) cũng có nghĩa là `out`.

Một vài trường hợp khiến cho trạng thái của cluster bị `HEALTH WARN`:
1. Do cluster chưa được bật.
2. Do vừa start hoặc restart cluster nên nó có thể chưa sẵn sàng hoạt động được ngay, vì các PG cần thời gian khởi tạo và các OSD đang trong quá trình liên kết với nhau.
3. Thêm hoặc xóa OSD.
4. Cluster map vừa được sửa đổi.

Kiểm tra tổng quan các OSD:

    ceph osd stat
Câu lệnh sẽ cho biết tổng số `x` OSD, bao nhiêu `up` (y), bao nhiêu `in` (z) và epoch là số lần map được thay đổi?

    x osds: y up, z in; epoch: eNNNN












