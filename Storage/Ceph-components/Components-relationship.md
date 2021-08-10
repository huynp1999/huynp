# Liên hệ giữa các thành phần trong Ceph

![image](https://user-images.githubusercontent.com/83684068/128682228-94beda09-8622-4824-b7a0-711f5f6355e5.png)

Có thể thấy nằm ở trung tâm là RADOS, giữ vai trò đặc biệt quan trọng trong kiến trúc Ceph, là trái tim của hệ thống lưu trữ CEPH
RADOS cung cấp tất cả các tính năng của Ceph như lưu trữ object phân tán, đảm bảo tính sẵn sàng cao, tin cậy, không có SPOF (Single point of failure), tự sửa lỗi, tự quản lý.

## Các thành phần bên dưới RADOS
Có 2 loại thành phần quan trọng trong một RADOS cluster, là **OSD** và **Monitor**. Ngoài ra còn có 2 thành phần khác là **Manager** mới được phát triển từ bản Luminous và **Metadata Server** dành riêng cho CephFS.

<img src="https://user-images.githubusercontent.com/83684068/128800053-460d6983-b00f-482e-b7ba-4c2a488edc29.png" alt="drawing" width="550"/>

1. **OSD ([ceph-osd](./ceph-osd)):** chịu trách nhiệm cung cấp tới data, số lượng của chúng có thể từ 10 lên tới hàng ngàn trong một cluster.
OSD cung cấp dịch vụ lưu trữ object tới client, vậy nên khi client yêu cầu truy cập một object, OSD sẽ có trách nhiệm trả về object đó cho client.
Các OSD cũng có chức năng replicate và recovery với nhau để đảm bảo khả năng chịu lỗi và dữ liệu sẽ luôn được đảm bảo.

- Ceph OSD gồm 1 ổ cứng vật lý, được format theo 3 loại Linux filesystem bao gồm Btrfs, XFS, hoặc ext4. Và cuối cùng là Ceph OSD Service.
<img src="https://user-images.githubusercontent.com/83684068/128716151-07579c7b-aaa6-4724-8ed6-974636f0cfac.png" alt="drawing" width="550"/>

2. **Monitor ([ceph-monitor](./ceph-mon)):** có trách nhiệm duy trì và kiểm soát tình trạng cho cluster. Thường có số lượng lẻ và từ 3 đến 5 monitor trong một cluster.
Các monitor dựa vào PASOX để vote và đưa ra quyết định xem một host trong cluster có bị lỗi hay không.
Như vậy sẽ không cần quá nhiều MON cho việc vote này, cũng như việc có số lượng lẻ sẽ tránh được số lượng vote bằng nhau. Các monitor không lưu trữ và phục vụ dữ liệu tới client.

3. **Manager ([ceph-mgr](./ceph-mgr)):** làm nền giám sát chính, nhằm cung cấp hệ thống giám sát và giao diện bổ sung cho các hệ thống quản lý và giám sát bên ngoài.
4. **Metadata Server ([ceph-mds](./ceph-mds)):** sử dụng MDS daemon để quản lý metadata riêng biệt khỏi data, và daemon này dành riêng cho Ceph Filesystem (CephFS). Dùng để chứa các permission, đường dẫn, thông tin về dữ liệu, v.v
## Các thành phần bên trên RADOS
1. **LIBRADOS:** là thư viện C cho phép ứng dụng làm việc trực tiếp với RADOS.
Librados là thư viện cho RADOS, cung cấp các hàm API, giúp ứng dụng tương tác trực tiếp và truy xuất song song vào cluster
Ứng dụng có thể mở rộng các giao thức của nó để truy cập vào RADOS bằng cách sử dụng librados. Các thư viện tương tự cũng sẵn sàng cho C++, Java, Python, Ruby, PHP.
librados là nền tảng cho các service giao diện khác chạy bên trên, gồm **Ceph RADOS Gateway**, **Ceph Block Device** và **Ceph Filesystem**. Cả 3 dịch vụ này đều có thể vận hành trong cùng một cụm lưu trữ.

2. **Ceph RADOS Gateway ([ceph-radosgw](./ceph-radosgw)):** sử dụng radosgw daemon để tương tác với librgw, và librados như một lớp trung gian để sử dụng RADOS lưu trữ object. Cung cấp RESTful object storage, tương thích với S3 và Swift.

<img src="https://user-images.githubusercontent.com/83684068/128691134-2e49c5ea-12ad-47a5-9f9a-df882fb7413f.png" alt="drawing" width="550"/>

3. **RADOS Block Device ([ceph-rbd](./ceph-rbd)):** là interface dành cho block storage. Tương tự như một một ổ đĩa ảo với khả năng mapped, formated và mounted. Dữ liệu khi được lưu trữ trong RADOS sẽ được RBD bổ ra thành nhiều block và phân tán ra khắp cluster (pool). Và khi muốn truy cập và sử dụng chúng sẽ cần thông qua librbd. Ngoài ra cũng có thể map RBD image như một device trong Linux, vì RBD driver được tích hợp với Linux kenel.

![image](https://user-images.githubusercontent.com/83684068/128717163-bc8e249f-678e-4790-a00f-db8633037fac.png)

4. **Ceph Filesystem:** sử dụng metadata server để quản trị metadata, tách biệt khỏi data ở OSD. Metadata sẽ được lưu trong RADOS và khi một MDS down thì một MDS khác sẽ được up.

<img src="https://user-images.githubusercontent.com/83684068/128718897-99464e7a-a263-4c63-b658-1f415d4b7228.png" alt="drawing" height="350"/>

Ví dụ:
- Nếu muốn giao tiếp với Ceph cluster sử dụng object thì sẽ cần thông qua Ceph Object Gateway (RADOSGw)
- Nếu muốn sử dụng virtual disk thì sẽ thông qua Ceph Block Device
- Và nếu muốn sử dụng file và directory thì thông qua Ceph Filesystem.
