# Các lệnh hiện thị
## head
Mặc định in 10 dòng đầu tiên của một file.
- `-n` in số dòng tính từ đầu
- `-b` in theo số byte chỉ định
- `-q` đọc nhiều file
- `-v` hiển thị tên file được in

## tail
Mặc định in 10 dòng cuối cùng của một file.
- `-n` in số dòng tính từ cuối
- `-b` in theo số byte chỉ định
- `-q` đọc nhiều file
- `-f` kiểm tra những dòng mới được thêm vào, cho phép kiểm soát và sửa lỗi khi làm việc với log file

## less
Là một câu lệnh hiện thị file hoặc output của một command theo từng trang một. Thường dùng với những file lớn.

Các câu lệnh trong less
- `f` hoặc `space` tới trang tiếp theo
- `b` lùi trang
- `enter` xem từng dòng một
- `/` hoặc `?` tìm kiếm theo chiều lên hoặc xuống
- `q` thoát
- `n` hoặc `N` tìm kết quả tiếp theo theo chiều lên hoặc xuống

Các option
- `-N` in số dòng được chỉ định
- `+F` kiểm tra những dòng mới được thêm vào, cho phép kiểm soát và sửa lỗi khi làm việc với log file
## cut
Cắt các phần theo từng dòng trong file và in ra màn hình. Sẽ bị lỗi nếu không có option.
- `-b` cắt theo từng byte
  - `-b 1-` cắt từ byte đầu tiên đến byte cuối cùng của một dòng
  - `-b -3` cắt từ byte đầu tiên đến byte thứ 3 của một dòng
- `-c` cắt theo ký tự
- `-f` cắt theo từng vùng, kết hợp với `-d` để phân biệt từng vùng
