# Tổng quan về các thành phần trong cấu trúc Ceph

![image](https://user-images.githubusercontent.com/83684068/128682228-94beda09-8622-4824-b7a0-711f5f6355e5.png)

Có thể thấy nằm ở trung tâm là RADOS, giữ vai trò đặc biệt quan trọng trong kiến trúc Ceph, là trái tim của hệ thống lưu trữ CEPH
RADOS cung cấp tất cả các tính năng của Ceph như lưu trữ object phân tán, đảm bảo tính sẵn sàng cao, tin cậy, không có SPOF (Single point of failure), tự sửa lỗi, tự quản lý.

## Các thành phần bên dưới RADOS
Có 2 loại thành phần quan trọng trong một cluster, là OSD daemon và Monitor. 

![image](https://user-images.githubusercontent.com/83684068/128685511-f26b234d-96ad-4c5c-87fc-670281812b0c.png)

- **OSD** daemon chịu trách nhiệm cung cấp tới data, số lượng của chúng có thể từ 10 lên tới hàng ngàn trong một cluster.
OSD cung cấp dịch vụ lưu trữ object tới client, vậy nên khi client yêu cầu truy cập một object, OSD sẽ có trách nhiệm trả về object đó cho client.
Các OSD cũng có chức năng replicate và recovery với nhau để đảm bảo khả năng chịu lỗi và dữ liệu sẽ luôn được đảm bảo.

- Thành phần quan trọng thứ 2 là **Monitor**, có trách nhiệm duy trì và kiểm soát tình trạng cho cluster. Thường có số lượng lẻ và từ 3 đến 5 monitor trong một cluster.
Các monitor dựa vào PASOX để vote và đưa ra quyết định xem một host trong cluster có bị lỗi hay không.
Như vậy sẽ không cần quá nhiều MON cho việc vote này, cũng như việc có số lượng lẻ sẽ tránh được số lượng vote bằng nhau. Các monitor không lưu trữ và phục vụ dữ liệu tới client.

- Ngoài ra còn có 2 thành phần khác là Manager và Metadata Server.
  - **Manager** làm nền giám sát chính, nhằm cung cấp hệ thống giám sát và giao diện bổ sung cho các hệ thống quản lý và giám sát bên ngoài.
  - **Metadata Server** sử dụng MDS daemon để quản lý metadata riêng biệt khỏi data, và daemon này dành cho Ceph Filesystem (CephFS)
## Các thành phần bên trên RADOS
- Bên trên RADOS, lớp LIBRADOS là thư viện C cho phép ứng dụng làm việc trực tiếp với RADOS.
Librados là thư viện cho RADOS, cung cấp các hàm API, giúp ứng dụng tương tác trực tiếp và truy xuất song song vào cluster
Ứng dụng có thể mở rộng các giao thức của nó để truy cập vào RADOS bằng cách sử dụng librados. Các thư viện tương tự cũng sẵn sàng cho C++, Java, Python, Ruby, PHP.
librados là nền tảng cho các service giao diện khác chạy bên trên, gồm Ceph Block Device, Ceph Filesystem, Ceph RADOS Gateway. Và cả 3 dịch vụ này đều được lưu trong cùng một cụm lưu trữ.

- Ceph RADOS Gateway: sử dụng RADOS để lưu trữ object 

![image](https://user-images.githubusercontent.com/83684068/128691134-2e49c5ea-12ad-47a5-9f9a-df882fb7413f.png)


Ví dụ:
- Nếu muốn giao tiếp với Ceph cluster sử dụng object thì sẽ cần thông qua Ceph Object Gateway (RADOSGw)
- Nếu muốn sử dụng virtual disk thì sẽ thông qua Ceph Block Device
- Và nếu muốn sử dụng file và directory thì thông qua Ceph Filesystem.
