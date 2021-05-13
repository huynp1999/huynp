# Nén dữ liệu
Là cách mà các dữ liệu được đóng gói và nén giúp giảm bớt dung lượng, tiết kiệm thời gian và băng thông internet, cũng như giảm thiểu rủi ro trong quá trình truyền dữ liệu.

## tar - gunzip
Là một lệnh phổ biến nhất để đóng gói dữ liệu trong Linux.

Khi gói dữ liệu bằng tar sẽ có kết quả với đuôi `.tar`. Còn nén sẽ cần Gzip và cuối cùng sẽ có đuôi là `.tar.gz`.

Cài đặt: `apt-get install tar`

Các option:
- `-c` tạo file đóng gói mới (.tar)
- `-v` show quá trình nén lên màn hình 
- `-f` tên file
- `-z` nén file bằng gzip (.tar.gz)
- `-j` nén file bằng bz2 (.tar.bz2) sẽ nén nhiều hơn gzip nhưng cần nhiều thời gian nén và giải nén
- `-t` xem dữ liệu được nén trong file
- `-x` giải nén
- `-C` giải nén vào một thư mục

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/tar1.png)
## rar
Là công cụ nén làm việc với đuôi .rar

Cài đặt: `sudo apt install unrar/rar`

Các option:
- `a` nén file
- `e` xem và giải nén file
- `l` list các file bên trong file nén
- `t` test dữ liệu toàn vẹn
- `u` thêm file vào trong file nén
- `-p` đặt password

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/rar1.png)
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/rar2.png)
## zip
Là công cụ nén làm việc với đuôi .zip

Cú pháp:
- Nén: `zip file.zip filename.txt`
- Giải nén: `unzip file.zip`

Các option:
- `-d` xóa file trong file nén
- `-u` thêm file vào file nén
- `-m` xóa file gốc sau khi nén
- `-r` nén thư mục
- `-x` nén nhưng loại trừ những file


