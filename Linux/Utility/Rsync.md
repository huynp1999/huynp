# Rsync
Rsync (Remote Sync) là một công cụ dùng để sao chép và đồng bộ file/thư mục, ví dụ như đồng bộ dữ liệu trên local hoặc giữa các server với nhau.

Các đặc điểm chính:
- Hỗ trợ copy giữ nguyên thông số của files/folder như Permissions, TimeStamp, Owner,....
- Sử dụng giao thức remote-update, chỉ transfer những dữ liệu đã được thay đổi, do vậy mà nhanh hơn scp
- Áp dụng phương pháp nén và giải nén khi transfer, do đó mà tiết kiệm băng thông do sử dụng 
- Không yêu cầu quyền super-user.

Cú pháp: `rsync [option] [source] [destination]`

Các option:
- `-v` hiển thị trạng thái lên màn hình
- `-r` copy dữ liệu nhưng không đảm bảo thông số của file và thư mục
- `-a` copy dữ liệu đồng thời giữ nguyên được tất cả các thông số của file và thư mục
- `-z` nén dữ liệu khi transfer, tiết kiệm băng thông nhưng tốn thêm một chút thời gian
- `-h` hiện thị kết quả dễ học
- `--delete` xóa dữ liệu ở destination nếu source không tồn tại dữ liệu đó.
- `--include '*'` gồm những file cụ thể
- `--exclude '*'` loại trừ ra những dữ liệu không muốn truyền đi
- `--progress` hiển thị thông tin tiến trình transfer

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/rs.png)

Khi cần làm việc với remote server, ví dụ ở đây có địa chỉ là `192.168.50.9`
- `rsync -avzh --progress root@192.168.50.9:/root/testdir /root/testdir`
Như vậy sẽ đồng bộ giữa 2 thư mục `/testdir` của server và local.
