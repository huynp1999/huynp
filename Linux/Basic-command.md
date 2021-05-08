# Câu lệnh chung
- `[command] --help` xem mô tả về một câu lệnh
- `sudo` (superuser do) đứng trước các câu lệnh, cho phép chạy với quyền admin
- `whoami` hiển thị username, trong trường hợp sử dụng nhiều user
- `echo "Hello"` in ra màn hình
  - `echo "Hello" > file.txt` sẽ ghi _Hello_ vào cuối file.txt
# Wildcard
- `*` chọn tất cả tên các file và thư mục
  - `mv dir/*` di chuyển toàn bộ bên trong thư mục nguồn
  - `ls *.txt` liệt kê toàn bộ file có đuôi txt

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/wildcard1.png)
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

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sort1.png)
- `-o` chuyển hướng kết quả sắp xếp đến một filename, tương tự `>`

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sort2.png)
- `-n` sắp xếp theo số thứ tự

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sort3.png)
## uniq
Dùng để làm việc với các tên ký tự trùng lặp, thường yêu cầu một file sort là input.
- `-d` chỉ in những dòng bị trùng
- `-c` kèm theo số lần xuất hiện
- `-u` chỉ in những dòng không trùng 

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/uniq1.png)
## split
Phân tách file với cú pháp `split [options] filename newfile`
- `-l` tách dựa trên số dùng
- `--verbose` thông báo sau khi tách

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/split1.png)
- `-b` tách thành các file có cùng dung lượng

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/split2.png)
- `-n` tách thành n file, mặc định là 2
## tac
Chức năng in tương tự cat nhưng có thể ghép hoặc in đảo ngược file
- `r` gắn liền các dòng khi nối 2 file
## nl
Dùng để đánh số các dòng với cú pháp `nl [option] [file]`
- `-v` chỉ định số bắt đầu, mặc định là 1
- `-s` thêm các chuỗi đằng sau số được đánh

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/nl1.png)
