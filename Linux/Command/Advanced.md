# grep
Grep là một câu lệnh quan trọng trong Linux. Dùng để tìm các dòng chứa từ khoá trong một file cho trước.

Cú pháp: `grep 'word' [file]`
- `-r` tìm kiếm tất cả các file trong thư mục và thư mục con hiện tại
- `-i` tìm theo cả trường hợp ký tự viết hoa
- `-c` số lần xuất hiện của từ khoá
- `-n` từ khoá xuất hiện dòng số bao nhiêu
- `-v` in các dòng mà **không có** từ khoá
- `-w` chỉ in dòng có đúng từ khoá
  - `grep -w 'america' text.txt` sẽ chỉ tìm theo đúng từ _america_ chứ không có _american, americano_
- `-l` chỉ hiện tên file có chứa từ khoá
- `--color` tô màu từ khoá trong kết quả

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/grep2.png)
# sed
Sed được dùng để lọc văn bản, sửa đổi nội dung một file, đặt nội dung vào một file mới.

Cú pháp: `sed [option] 'commands' [file]`

Các command:
- `sed 's/pattern/replace_string/' file`	thay thế chuỗi đầu tiên xuất hiện trong mỗi dòng
- `sed 's/pattern/replace_string/g' file`	thay thế tất cả các lần xuất hiện trong mỗi dòng
  - `/2 thay thế 2 lần xuất hiện đầu tiên trong mỗi dòng
  - `/p` để lọc ra những dòng cụ thể chứ keyword
  - `/d` để không in ra những dùng cụ thể, in còn lại
- `sed '1,3s/pattern/replace_string/g' file`	Thay thế tất cả các lần xuất hiện chuỗi trong một loạt các dòng
- `sed -i 's/pattern/replace_string/g' file`	Lưu các thay đổi sau khi thay thế
- `-i.bkp` để tạo một bản sao lưu trước khi ghi đè

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/sed1.png)
# awk
Là một loại ngôn ngữ script dùng để thao tác với dữ liệu, tìm kiếm và xử lý file. Có thể tìm kiếm một hoặc nhiều file để xem những dòng nào bao gồm những pattern cần tìm kiếm và sau đó thực hiện những action.

Cú pháp: `awk pattern actions file`
- `'{print}'` in ra từng dòng
- `'{if(statement){do}}'` cú pháp điều kiện

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/awk1.png)
- `'{sub((" ","-")} 1'` thay thế chuỗi hoặc ký tự
- `'/keyword/'` lọc ký tự 

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/awk.png)
- `'{s+=$1} END {print s}'` tính tổng trường

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/awk2.png)

Các trường
- `$0` toàn bộ văn bản
- `$1` trường đầu tiên, giữa các trường mặc định là `tab` hoặc `space`
- `$NF` trường cuối cùng
