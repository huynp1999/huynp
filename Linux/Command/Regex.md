# Regular Expression
Là các ký tự đặc biệt giúp tìm kiếm dữ liệu, phù hợp với dữ liệu phức tạp

Có 3 loại regex:
1. Regex cơ bản
2. Regex dạng khoảng (interval)
3. Regex mở rộng

## 1. Regex cơ bản
Thường được sử dụng với các câu lệnh như `tr`, `sed`, `vi` và `grep`:
- `.`     khớp bất kỳ kí tự, bao gồm cả ký tự đặc biệt
- `^`	    đầu chuỗi
- `$`	    cuối chuỗi
- `*`	    khớp với 0 hoặc nhiều lần ký tự trước, không bao gồm ký tự đặc biệt
  - `mv dir/*` di chuyển toàn bộ bên trong thư mục nguồn
  - `ls *.txt` liệt kê toàn bộ file có đuôi txt
- `+`	    khớp với 1 hoặc nhiều lần ký tự trước
- `\`	    đại diện cho ký tự đặc biệt
- `()`    nhóm biểu thức chính quy
- `?`	    khớp tối đa 1 kí tự
  - `ls text?.txt` liệt kê các file có tên text1,text2,...
- `[]`	  khớp với bất kì kí tự nào nằm trong dấu ngoặc vuông
  - `cp [Ff]ile.txt` copy File hoặc file 
- `[^ ]`  khớp với bất kì kí tự nào không có trong ngoặc vuông
- `(abc)`	khớp với các kí tự abc theo một thứ tự chính xác

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/wildcard1.png)
## 2. Regex dạng khoảng
Kiểm soát số lần xuất hiện của một ký tự trong một chuỗi.

- `{n}`	    khớp với ký tự xuất hiện chính xác 'n' lần
- `{n, m}`	khớp với ký tự xuất hiện 'n' lần nhưng không quá m
- `{n,}`	  chỉ khớp với ký tự xuất hiện 'n' lần trở lên

Ngoài ra còn có thể đại diễn cho một chuỗi hoặc một danh sách các mục:
```
echo a{0..10}b
a0b a1b a2b a3b a4b a5b a6b a7b a8b a9b a10b
```
## 3. Regex mở rộng
Chứa các kết hợp của nhiều câu lệnh khác.

- `\+`	Khớp với một hoặc nhiều lần xuất hiện của ký tự trước
- `\?`	Khớp 0 hoặc một lần xuất hiện của ký tự trước


