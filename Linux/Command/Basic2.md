# 1. Lệnh với text
## 1.1 sort
Dùng để sắp xếp file với những tùy chọn đa dạng:
- `-r` đảo ngược sắp xếp

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sort1.png)
- `-o` chuyển hướng kết quả sắp xếp đến một filename, tương tự `>`

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sort2.png)
- `-n` sắp xếp theo số thứ tự

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sort3.png)
## 1.2 uniq
Dùng để làm việc với các tên ký tự trùng lặp, thường yêu cầu một file sort là input.
- `-d` chỉ in những dòng bị trùng
- `-c` kèm theo số lần xuất hiện
- `-u` chỉ in những dòng không trùng 

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/uniq1.png)
## 1.3 split
Phân tách file với cú pháp `split [options] filename newfile`
- `-l` tách dựa trên số dùng
- `--verbose` thông báo sau khi tách

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/split1.png)
- `-b` tách thành các file có cùng dung lượng

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/split2.png)
- `-n` tách thành n file, mặc định là 2
## 1.4 tac
Chức năng in tương tự cat nhưng có thể ghép hoặc in đảo ngược file
- `r` gắn liền các dòng khi nối 2 file
## 1.5 nl
Dùng để đánh số các dòng với cú pháp `nl [option] [file]`
- `-v` chỉ định số bắt đầu, mặc định là 1
- `-s` thêm các chuỗi đằng sau số được đánh

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/nl1.png)

# 2. Các lệnh hiện thị
## 2.1 head
Mặc định in 10 dòng đầu tiên của một file.
- `-n` in số dòng tính từ đầu
- `-b` in theo số byte chỉ định
- `-q` đọc nhiều file
- `-v` hiển thị tên file được in

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/head.png)
## 2.2 tail
Mặc định in 10 dòng cuối cùng của một file.
- `-n` in số dòng tính từ cuối
- `-b` in theo số byte chỉ định
- `-q` đọc nhiều file
- `-f` kiểm tra những dòng mới được thêm vào theo thời gian thực, cho phép kiểm soát và sửa lỗi khi làm việc với log file

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/tail.png)
## 2.3 less
Là một câu lệnh hiện thị file hoặc output của một command theo từng trang một. Thường dùng với những file lớn.

Các câu lệnh trong less
- `f` hoặc `space` tới trang tiếp theo
- `b` lùi trang
- `enter` xem từng dòng một
- `/` hoặc `?` tìm kiếm theo chiều lên hoặc xuống
- `q` thoát
- `n` hoặc `N` tìm kết quả tiếp theo theo chiều lên hoặc xuống
- `g` hoặc `G` chuyển đến đầu hoặc cuối file
- `f` cập nhật file theo thời gian thực tương tự `tail -f`

Các option
- `-N` in số dòng được chỉ định
## 2.4 cut
Cắt các phần theo từng dòng trong file và in ra màn hình. Sẽ bị lỗi nếu không có option.
- `-b` cắt theo từng byte
  - `-b 1-` cắt từ byte đầu tiên đến byte cuối cùng của một dòng
  - `-b -3` cắt từ byte đầu tiên đến byte thứ 3 của một dòng
- `-c` cắt theo ký tự
- `-f` cắt theo từng vùng, kết hợp với `-d` để phân biệt từng vùng
