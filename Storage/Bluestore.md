# OSD Backends
![image](https://user-images.githubusercontent.com/83684068/128842467-5439240c-f90d-46bf-a983-55f729de5708.png)

Trong ceph osd daemon có một module quan trọng được gọi là ObjectStore, chịu trách nhiệm về cách thức lưu trữ và quản lý object. Ceph được thiết kế để hỗ trợ nhiều công cụ lưu trữ bằng cách đăng ký chúng như là các backend khác nhau cho ObjectStore.

Đối với Ceph có 2 loại backend FileStore và BlueStore. Ngoài ra còn có KStore được thử nghiệm trong phiên bản Jewel nhưng đã không còn sử dụng.

## BlueStore
Được sử dụng từ bản Luminous. BlueStore ra đời để tránh các hạn chế của FileStore.
BlueStore ghi trực tiếp object lên thiết bị vật lý và quản lý metada bằng RocksDB. RocksDB sử dụng một filesystem gọn nhẹ và tối giản tên là BlueFS

<img src="https://user-images.githubusercontent.com/83684068/128850502-93d7f9f9-1747-4c6e-83d8-1cb718249d5c.png" alt="drawing" width="750"/>





## FileStore
Trong FileStore, các object được lưu với một file riêng lẻ.
Sử dụng FileStore, ceph yêu cầu sử dụng journal bên ngoài để đảm bảo tính nhất quán.
- Ceph đảm bảo tính nhất quán cao giữa các bản sao dữ liệu, tất cả các thao tác ghi được xem như đơn vị transaction.
Các transactions được ghi vào journal trước giúp cải thiện hiệu năng. Sau khi được ghi xong vào journal, FileStore daemon thực hiện ghi xuống disk để lưu trữ cố định.

Và trong FileStore, transaction sẽ được chia thành data và metadata. Data sẽ được ghi vào một XFS filesystem, còn metadata sẽ được lưu vào database (leveldb). Và database này cũng dựa trên XFS filesystem

<img src="https://user-images.githubusercontent.com/83684068/128850540-b1fbc61d-6270-4545-95d0-a086fc9782de.png" alt="drawing" width="750"/>



**Điểm khác biệt chính** giữa 2 loại module là với FileStore, object phải ghi 2 lần: 1 lần vào journal và 1 lần vào disk. Đối với BlueStore ghi trực tiếp object lên disk và quá trình quản lý metadata cũng được tối giản hơn khi so với Filestore.

























