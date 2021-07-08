# System call
Trong kiến trúc Linux, không gian bộ nhớ được chia thành hai phần là user space và kernel space. 
Do vậy mà cũng tồn tại hai chế độ (mode) là user mode và kernel mode.
Các chỉ lệnh được gọi từ chương trình như đóng mở file (fopen, fclose), hoặc in thông tin (printf) chỉ có thể thực thi và truy cập vùng nhớ ở tầng user mà không được truy cập vùng nhớ của kernel.
Cơ chế phân tách user space với kernel space nhằm tránh người dùng tự ý truy cập tài nguyên của kernel, giúp quản lý và bảo vệ kernel cũng như toàn bộ hệ thống.

Để user thực thi yêu cầu xuống kernel, kernel cung cấp cho user space các API (còn gọi là các dịch vụ) là system call.
System call là cửa ngõ vào kernel, cho phép tiến trình trên tầng user yêu cầu kernel thực thi tác vụ cho mình.
Những dịch vụ này có thể là tạo một tiến trình mới (fork), thực thi I/O (read, write), hoặc tạo ra một pipe cho giao tiếp liên tiến trình (IPC).

![image](https://user-images.githubusercontent.com/83684068/124892365-026b2780-e004-11eb-93f7-b430fe8fdabd.png)

Giả sử, với một chương trình đơn giản có tác vụ đọc dữ liệu trong một file A, và sao chép nó qua một file B.
Để chương trình này hoạt động bình thường, nó cần phải đọc được file A (system call 1: đọc file).
Nếu có lỗi xảy ra, chương trình phải xuất một dòng báo lỗi ra màn hình cho người dùng (system call 2: ghi) và thoát chương trình (system call 3: thoát).
Nếu không có lỗi sẽ tiến hành tạo file thứ B nếu không có sẵn (system call 4: tạo file) và thực hiện sao chép (system call 5: ghi file).

## Phân loại các system call
Các system call phổ biến có thể kể đến `open`, `read`, `write`, `close`, `wait`, `exec`, `fork`, `exit` và `kill`. Ngoài ra, Linux còn có hơn 300 call khác có thể xem tại ![**đây**](https://man7.org/linux/man-pages/man2/syscalls.2.html).

### Open system call
`open()` system call sẽ mở file được chỉ định theo đường dẫn. Nếu file không tồn tại, có thể thêm tag tùy chọn `O_CREAT` để tạo file mới và mở nó.
Giá trị trả về của `open()` là một file descriptor (FD). Từ FD này, các syscall khác như read,write,... có thể khai thác sử dụng file đã được mở.
