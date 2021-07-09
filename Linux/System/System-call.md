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
Các system call phổ biến có thể kể đến `open`, `read`, `write`, `close`, `wait`, `exec`, `fork`, `exit` và `kill`. Ngoài ra, Linux còn có hơn 300 call khác có thể xem tại [**đây**](https://man7.org/linux/man-pages/man2/syscalls.2.html).

### Open system call
`open()` system call sẽ mở file được chỉ định theo đường dẫn. Nếu file không tồn tại, có thể thêm tag tùy chọn `O_CREAT` để tạo file mới và mở nó.
Giá trị trả về của `open()` là một file descriptor (FD). Từ FD này, các syscall khác như read, write,... có thể khai thác sử dụng file đã được mở.

- `O_SYNC`
  - Các thao tác ghi trên **file** sẽ hoàn thành theo các yêu cầu về tính toàn vẹn của tệp I / O được đồng bộ hóa hoàn thành (khác với dữ liệu I/O được đồng bộ hóa hoàn thành toàn vẹn do O_DSYNC cung cấp.)
  - Tại thời điểm dữ liệu ghi được trả về, dữ liệu đầu ra cùng với metadata sẽ được chuyển đến phần cứng (tức là sau mỗi lần dữ liệu được thay đổi sẽ là một lần call đến `fsync`).
- `O_DSYNC`
  - Các thao tác ghi trên **dữ liệu** sẽ hoàn thành theo các yêu cầu của tính toàn vẹn dữ liệu I/O được đồng bộ hóa hoàn thành
  - Tại thời điểm dữ liệu được trả về, dữ liệu đầu ra sẽ được chuyển sang phần cứng bên dưới, cùng với bất kỳ metadata nào được yêu cầu để truy xuất dữ liệu đó (tức là sau mỗi lần dữ liệu được thay đổi sẽ là một lần call đến `fdatasync`).
- `O_DIRECT` 
  - Giảm thiểu ảnh hưởng của cache đến I/O file. Nhìn chung hiệu suất bị sẽ bị giảm nhưng lại trở nên hữu ích trong các trường hợp đặc biệt, chẳng hạn như khi ứng dụng muốn tự dùng cache riêng. I/O file được thực hiện trực tiếp đến/đi từ cache của user space.
  - Flag `O_DIRECT` tự truyền dữ liệu đồng bộ, nhưng không có được sự đảm bảo về metadata giống như `O_SYNC`.
  - Để đảm bảo I/O đồng bộ, `O_SYNC` phải được sử dụng cùng `O_DIRECT`.

Khác biệt giữa
- `O_SYNC` cung cấp tính toàn vẹn của **file** I/O được đồng bộ hóa, nghĩa là hoạt động ghi sẽ flush dữ liệu và tất cả metadata đến phần cứng.
- `O_DSYNC` cung cấp tính toàn vẹn **dữ liệu** I/O được đồng bộ hóa, nghĩa là hoạt động ghi sẽ flush dữ liệu vào phần cứng bên dưới, và chỉ cập nhật metadata nào cần thiết cho lần đọc. Như vậy sẽ giảm tải cho ổ cứng trong trường hợp mà ứng dụng không yêu cầu tính toàn vẹn của **file**

Ví dụ có hai metadata, một cho biết về thời gian chỉnh sửa cuối cùng (last modification timestamp) và một cho biết độ dài file.
- Trong quá trình ghi, tất cả các hoạt động ghi sẽ update lại timestamp, và khi có dữ liệu được thêm vào cuối file sẽ update vào length
- Trong quá trình đọc, timestamp là không cần thiết, nhưng length thì có. Như vậy `O_DSYNC` sẽ chỉ flush length metadata thay vì flush cả timestamp metadata giống như `O_SYNC`
