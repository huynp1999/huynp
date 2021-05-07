# Câu lệnh chung
- `[command] --help` xem mô tả về một câu lệnh
- `sudo` (superuser do) đứng trước các câu lệnh, cho phép chạy với quyền admin
- `whoami` hiển thị username, trong trường hợp sử dụng nhiều user
- `echo "Hello"` in ra màn hình
  - `echo "Hello" > file.txt` sẽ ghi _Hello_ vào cuối file.txt
# Wildcard
- `*` chọn tất cả các file và thư mục
  - `mv dir/*` di chuyển toàn bộ bên trong thư mục nguồn
  - `ls *.txt` liệt kê toàn bộ file có đuôi txt
- `?`: chọn tất cả ký tự trong tên
  - `ls text?.txt` liệt kê các file có tên text1,text2,...
# Lệnh với thư mục và file
- `ls` liệt kê các file và thư mục
  - `-l` liệt kê chi tiết hơn với permission, size, owner,...
  - `-a` hiện thư mục ẩn
  - `-d */` chỉ hiện thư mục
- `mkdir [name]` tạo thư mục
  - `-p` tạo nhiều thư mục con liên tiếp
- `cp [file] [dir]` copy
  - `-r` copy thư mục vào thư mục
- `mv` di chuyển hoặc có thể là đổi tên thư mục hoặc file trống
- `rm` xóa file
  - `-rf` xóa thư mục
-  `grep` tìm kiếm một đoạn text trong file hoặc thư mục

# Lệnh với text
## sort
Dùng để sắp xếp file với những tùy chọn đa dạng:
- `-r` đảo ngược sắp xếp
- `-o` chuyển hướng kết quả sắp xếp đến một filename, tương tự `>`
- `-n` theo số thứ tự
## uniq
Dùng để làm việc với các tên ký tự trùng lặp, thường yêu cầu một file sort là input.
- `-d` chỉ in những dòng bị trùng
- `-c` kèm theo số lần xuất hiện
- `-u` chỉ in những dòng không trùng 
## 

