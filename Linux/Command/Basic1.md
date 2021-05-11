# 1. Câu lệnh chung
- `[command] --help` xem mô tả về một câu lệnh
- `man [command]` xem cách sử dụng về một câu lệnh
- `sudo` (superuser do) đứng trước các câu lệnh, cho phép chạy với quyền admin
- `whoami` hiển thị username, trong trường hợp sử dụng nhiều user
- `echo "Hello"` in ra màn hình
# 2. Lệnh với thư mục và file
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

## 2.1 cat
Là một lệnh phổ biến trong linux với các chức năng như đọc, tạo, điều hướng file.

Cú pháp `cat [option] [file]`
- `| more |less` dùng khi đọc một file có dung lượng lớn
- `-n` đánh số dòng, tương tự như câu lệnh `nl`
- `-e` đánh ký tự $ vào cuối dòng, dùng để ghép tất cả các dòng thành một
- `>` ghi đè lên một file
- `>>` ghi tiếp vào dòng cuối cùng của một file
- `;` đọc nhiều file cùng lúc

Kết hợp với ống lệnh, ví dụ tạo file3 với input là file1 và file2 kết hợp đồng thời với sắp xếp

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/cat2.png)
## 2.2 join
Dùng để ghép 2 file hoặc một vùng cho trước, yêu cầu phải đánh số dòng tại input (`nl`)

Cú pháp `join [option] file1 file2`
- `-a` ghép 2 file lệch số dòng

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/join2.png)
- `-v` chỉ in ra dòng bị lệch
- `-t` sử dụng ký tự để tách các cột được ghép
## 2.3 paste
Dùng để ghép 1 file với các file khác theo từng cột dữ liệu

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/paste2.png)
Cú pháp `join [option] file1 ...`
- `-d` chọn ký tự ngăn giữa các cột thay vì `tab` ở mặc định

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/paste1.png)

