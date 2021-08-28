## PG state
Khi mà trạng thái của cluster không còn là `HEALTH OK`, ngoài trạng thái hoạt động của OSD thì sẽ cần kiểm tra cả trạng thái của các PG (PG state). Cụ thể trong những trường hợp sau:
1. Vừa tạo một pool và PG chưa được chỉ định.
2. Các PG đang trong thời gian khôi phục (recovery).
3. Vừa thêm hoặc xoá OSD trong cluster.
4. CRUSH map vừa được sửa đổi và các PG đang migrating với location mới.
5. Các bản sao (replica) một PG đang không nhất quán.
6. Ceph đang sử dụng các bản sao của một PG.
7. Ceph không còn đủ dung lượng lưu trữ cho quá trình migrate

