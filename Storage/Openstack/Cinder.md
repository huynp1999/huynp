# Cinder
Là dịch vụ Block storage của OpenStack, cung cấp tài nguyên lưu trữ (volume) tới VM của Nova. Điều này được thực hiện thông qua LVM hoặc qua các plugin driver. Mô tả ngắn gọn về Cinder thì nó có chức năng ảo hóa việc quản lý các thiết bị block storage. End user có thể tạo, truy xuất và sử dụng volume thông qua Horizon interface, cli, hoặc thông qua trực tiếp REST API đó mà không yêu cầu bất kỳ kiến thức nào về nơi lữu trữ của họ của được triển khai như nào hoặc là loại thiết bị nào.

## Các thao tác quản lý image
#### 1. Tạo volume
Câu lệnh này sẽ tạo một LV trong VG `cinder-volumes` để từ đó cung cấp tới VM
    openstack volume create --size <size> <name>
    
Trong đó
- `<size>` volume size (GB)
- `<name>` tên volume
- `--image <id>` ngoài ra có thể dùng tạo volume từ image

#### 2. List các volume
    openstack volume list
#### 3. Gắn volume vào VM

    openstack server add volume <instance_name> <volume_name> \
    --device </dev/vdX>
    
Trong đó:
- `<instance_name>` tên hoặc id vm
- `<volume_name>` tên hoặc id volume
- `</dev/vdX>` gắn volume vào như một ổ đĩa ảo nên có thể chỉ định tên cho thiết bị như `vba,b,c...`

#### 4. Xoá volume
    openstack volume delete <volume_name>
