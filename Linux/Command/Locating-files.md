### find
Là một câu lệnh làm việc với file hierarchy. Dùng để tìm file, thư mục và thực thi những hoạt động lên chúng.

Cú pháp: 
- `find [where to start searching] [-options] [filename]`

Các option:
- `-exec CMD` thực thi câu lệnh khác với kết quả tìm được
- `-name` tìm theo tên
- `-emty` tìm file hoặc thư mục trống
- `-size +N/-N` tìm theo kích thước (+N tức là >N và ngược lại)
- `-user` tìm theo chủ sở hữu

Ví dụ với một file hierarchy như sau:
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/find1.png)
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/find2.png)

### locate
Có chức năng tương tự như find, nhưng `locate` có cấu trúc ngắn gọn và tìm kiếm theo database của riêng nó là `mlocate`. Database này cũng cần được update thường xuyên bằng câu lệnh:
`sudo updatedb`

Cú pháp:
- `locate [option] [filename]`

Các option:
- `-n` giới hạn kết quả tìm kiếm
- `-c` số lượng kết quả tìm được
- `-i` tìm theo cả chữ hoa và chữ thường

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/location.png)
### whereis
Là một tiện ích tìm kiếm vị trí các file nhị phân, nguồn, hướng dẫn sử dụng của một câu lệnh.

Cú pháp:
- `whereis [option] [filename]`

Các option:
- `-p` chỉ tìm binary
- `-s` chỉ tìm source
- `-m` chỉ tìm hướng dẫn (manual)

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/whereis.png)

Có thể thấy
- `bash:` là câu lệnh cần lấy thông tin
- `/bin/bash` đường dẫn tới file nhị phân
- `etc/bash.bashrc` đường dẫn tới file nguồn
- `/usr/share/man/man1/bash.1.gz` đường dẫn tới file hướng dẫn sử dụng
