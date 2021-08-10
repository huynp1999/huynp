# Ceph Object Gateway (Ceph RADOSGW)

![image](https://user-images.githubusercontent.com/83684068/128802567-df82853e-3100-40ab-b41e-efe16acdb9ad.png)

Ceph Object Gateway, hay RADOS Gateway, là interface của object storage được xây dựng dựa trên nền của `librados` để cung cấp RESTful gateway cho Ceph Storage Clusters. Ceph Object Storage hỗ trợ 2 giao diện sau:

- **S3**: Cung cấp Amazon S3 RESTful API.
- **Swift**: Cung cấp OpenStack Swift API. Ceph Object Gateway có thể thay thế Swift.

Ceph Object Gateway có phương thức quản lý người dùng riêng.
Cả S3 và Swift API chia sẻ cùng một namespace chung trong Ceph cluster, do đó có thể ghi dữ liệu từ một API và lấy từ một API khác.
Để xử lý nhanh, nó có thể dừng RAM làm cache metadata. Có thể dùng nhiều Gateway và sử dụng Load balancer để cân bằng tải vào Object Storage.
Hiệu năng được cải thiện thông qua việc cắt nhỏ các REST object thành các RADOS object. Bên cạnh S3 và Swift API.
Ứng dụng có thể bypass qua RADOS gateway và truy xuất trực tiếp tới librados, thường thấy trong các ứng dụng doanh nghiệp đòi hỏi hiệu năng cao.
Ceph cho phép truy xuất trực tiếp tới cluster, điều khác biệt so với các hệ thống lưu trữ khác vốn giới hạn về các interface giao tiếp.

![image](https://user-images.githubusercontent.com/83684068/128802948-f748d3d3-fb71-4221-9a06-9f18ffc552e4.png)
