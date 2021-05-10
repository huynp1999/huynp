# Stream
Là quá trình truyền input và nhận output trong Linux. 

Ba loại stream:
- standard input – thường được truyền từ bàn phím
- standard output – hiển thị output của lệnh, thường sẽ là ra terminal
- standard error – hiện thị lỗi của lệnh ở output

# Redirection
Hai cách để chuyển hướng dữ liệu ra file, thay vì ra màn hình:
- `>` truyền hướng output ra một file. Nếu file chưa có thì sẽ được tạo, nếu có sẵn thì sẽ bị ghi đè lên dữ liệu cũ mà không được cảnh báo
- `>>` tương tự như `>` nhưng không ghi đè mà sẽ ghi tiếp vào dòng cuối cùng của file

Ví dụ: `echo "abc" >> file.txt`
# Piping

`command 1 | command 2 | command 3 | ...`
Ví dụ: cat file.txt | uniq
