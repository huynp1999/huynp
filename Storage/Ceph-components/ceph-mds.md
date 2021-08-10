# Ceph MDS (Metadata Server)

Ceph MDS là daemon cho Ceph filesystem (CephFS). Ceph MDS cho phép Client mount 1 POSIX filesystem ở bất cứ kích thước nào. MDS không đưa dữ liệu tới người dùng, OSD làm việc đó. MDS cung cấp một filesystem chia sẻ với lớp cache thông minh;, giảm đáng kể lượng đọc và ghi.

Mỗi CephFS file system đều yêu cầu ít nhất một MDS, và trong đó, chỉ có 1 ceph MDS daemon hoạt động tại 1 thời điểm. MDS không lưu dữ liệu local. Nếu 1 MDS daemon lỗi, ta có thể tạo lại trên bất cứ hệ thống nào mà cluster có thể truy cập. Các metadata server daemon được cấu hình là active-passive. Primary MDS là acive, còn các node khác chạy standby. 

![image](https://user-images.githubusercontent.com/83684068/128802314-2fed41ca-a800-4649-a745-4e75ca08ad58.png)
