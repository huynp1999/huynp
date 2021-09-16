# Glance
Image service (code-name Glance) cung cấp dịch vụ dành cho người dùng tải lên và truy xuất các vào kho dữ liệu, nơi mà được sử dụng với các dịch vụ khác.
Trong đó sẽ bao gồm *image* và *metadata*.

## Image
Glance bao gồm các dịch vụ về lưu trũ, đăng ký và truy xuất image của máy ảo (VM).
Glance sử dụng RESTful API cho phép truy vấn metadata của VM image tương tự như truy xuất một image.

VM image được tạo từ Glance có thể được lưu trữ ở nhiều kiểu lưu trữ khác nhau, từ filesystem, tới object storage (Swift) và block storage (Cinder).

## Các thao tác quản lý image
#### 1. Upload image vào Glance
VM image có thể được import vào glance bằng câu lệnh

    openstack image create <name> --file <image_file> \
    --disk-format iso --container-format bare
  
Trong đó:
- `<image_file>` đường dẫn local tới file image cần upload
- `<name>` tên của image
  
Ví dụ upload một image của cirros 0.3.4 theo format qcow2 và cấu hình public access:
  
    openstack image create "cirros-ceph" --file ./cirros-0.3.4-x86_64-disk.img \
    --disk-format qcow2 --container-format bare --public
    
#### 2. List, show thông tin
 Để liệt kê danh sách hay hiện thị các thông tin chi tiết của image sử dụng câu lệnh:
 
    openstack image list
    openstack image show cirros-ceph
    

    
