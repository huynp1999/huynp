# Vim
Là một phần mềm chỉnh sửa văn bản mã nguồn mở, với nhiều ưu điểm như gọn nhẹ, tùy biến cao, nhiều plugin nhưng cũng có một số hạn chế với người mới sử dụng.

Cài đặt: `$ sudo apt-get install vim`
Mở file bằng vim: `vim [file]`

# Vimtutor Ba chế độ
Có 3 chế độ trong vim:
- NORMAL - dùng các câu lệnh mà không làm ảnh hưởng tới phần văn bản đang gõ
- INSERT - chỉnh sửa code, văn bản trong chế độ này, nhưng không thể dùng phím tắt hoặc lệnh.
- VISUAL - chế độ chọn, dùng để chọn nhanh phần văn bản để xử lý.

Thay đổi chế độ:
- i - chuyển sang chế độ INSERT
- v - chuyển sang chế độ VISUAL
- V   chuyển sang chế độ VISUAL LINE (chọn hàng thay vì chọn từ như VISUAL)
- Esc - chuyển sang chế độ NORMAL

Di chuyển trỏ chuột:
- h - di chuyển con trỏ chuột sang trái
- j - di chuyển con trỏ chuột xuống dưới
- k - di chuyển con trỏ chuột lên trên
- l - di chuyển con trỏ chuột sang phải
- $ - di chuyển con trỏ chuột xuống cuối dòng
- 0 - di chuyển con trỏ chuột về đầu dòng
- :2 - di chuyển đến dòng thứ 2
- gg - di chuyển con trỏ chuột về đầu văn bản
- G - di chuyển con trỏ chuột xuống cuối văn bản
- Ctrl-y - cuộn lên văn bản một dòng
- Ctrl-e - cuộn xuống văn bản một dòng
- Ctrl-u - cuộn lên văn bản nửa màn hình
- Ctrl-d - cuộn xuống văn bản nửa màn hình

Thao tác với văn bản:
- x - Xóa phần đã chọn
- y - Copy phần văn văn bản đã chọn
- p - Paste phần văn bản đã lưu
- d - Delete văn bản
  - d2w - Xóa 2 từ đăng sau con trỏ (delete ... word)
  - d$ - Xóa đến cuối dòng
  - d3b - Xóa 2 từ đằng trước con trỏ (delete ... backwards)
  - dt) - Xóa đến kí tự ")" (delete till ...)
  - d2j - Xóa 2 dòng bên dưới (delete ... j là xuống)
  - d2h - Xóa 2 chữ bên trải (delete ... h là qua trái)
  - dd - Xóa dòng hiện tại của con trỏ
- u: Undo 
- Ctrl-r: Redo

Tìm kiếm:
- `/` hoặc `?[keyword]` tìm kiếm thuận hoặc ngược
- `N` hoặc `n` để chuyển đến kết quả trước hoặc tiếp theo
- `Ctrl+O` quay trở lại nơi bắt đầu

Thay thế:
- `:s/old/new/g` thay thế chuỗi "old bằng "new" trong toàn bộ nội dung file
  - `/g` thay thế toàn bộ mỗi dòng, `/1` thay thế từ đầu tiên mỗi dòng
  - `:s/` tìm trong toàn bộ các dòng, `:1,4s/` chỉ tìm và thay thế từ dòng 1 đến 4
 
Thực thi các lệnh bên ngoài, ví dụ như của shell:
- `:!` nhập và thực thi lệnh từ bên ngoài
- `:w [filename]` tương tự như save as, lưu File hiện tại với tên khác.
- `:r` chèn nội dung file khác vào nơi con trỏ
  - `:r !ls` chèn output của lệnh `ls` vào nơi con trở

Thoát và lưu:
- `:w` lưu văn bản
- `:wq` lưu và thoát văn bản (hoặc sử dụng ZZ)
- `:q!` Thoát không lưu
