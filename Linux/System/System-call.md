# System call
## 1. Định nghĩa
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

## 2. Flush data trong system call
Các system call phổ biến có thể kể đến `open`, `read`, `write`, `close`, `wait`, `exec`, `fork`, `exit` và `kill`. Ngoài ra, Linux còn có hơn 300 call khác có thể xem tại [**đây**](https://man7.org/linux/man-pages/man2/syscalls.2.html). Trong bài này chỉ tập trung đến các call và tag dùng trong việc flush dữ liệu từ cache xuống disk.

### 2.1 Fsync, fdatasync system call
`fsync()` chuyển (flush) tất cả dữ liệu đã được sửa đổi của file tại bộ đệm nhờ file descriptor *fd* tham chiếu đến ổ cứng. Điều này nhằm truy xuất tất cả thông tin đã thay đổi ngay cả sau khi hệ thống gặp sự cố hoặc sau khi khởi động lại. Call sẽ chặn cho đến khi thiết bị báo rằng quá trình truyền đã hoàn tất. Nó cũng flush các thông tin metadata được liên kết với tệp.

`fdatasync()` tương tự như `fsync()`, nhưng chỉ flush metadata nào cần thiết truy xuất dữ liệu tiếp theo. Mục tiêu của `fdatasync` nhằm giảm tải cho disk trong trường hợp ứng dụng không yêu cầu đồng bộ hóa **tất cả** metadata với disk.

Ví dụ: các thay đổi đối với thời gian (lần truy cập cuối cùng, lần sửa đổi cuối cùng) không yêu cầu flush vì chúng không cần thiết để việc đọc dữ liệu tới. Mặt khác, một thay đổi đối với kích thước tệp sẽ yêu cầu flush metadata

### 2.2 Open system call
`open()` system call sẽ mở file được chỉ định theo đường dẫn. Nếu file không tồn tại, có thể thêm tag tùy chọn `O_CREAT` để tạo file mới và mở nó.
Giá trị trả về của `open()` là một file descriptor (FD). Từ FD này, các syscall khác như read, write,... có thể khai thác sử dụng file đã được mở.

- `O_SYNC`
  - Cung cấp đồng bộ hóa toàn vẹn cho **file** I/O.
  - Nghĩa là hoạt động ghi sẽ flush dữ liệu và tất cả metadata đến phần cứng. (tức là sau mỗi lần dữ liệu được thay đổi sẽ là một lần call đến `fsync`).
- `O_DSYNC`
  - Cung cấp đồng bộ hóa toàn vẹn cho **dữ liệu** I/O.
  - Tại thời điểm dữ liệu được trả về, dữ liệu đầu ra sẽ được chuyển sang phần cứng bên dưới, cùng với bất kỳ metadata nào được yêu cầu để truy xuất dữ liệu đó (tức là sau mỗi lần dữ liệu được thay đổi sẽ là một lần call đến `fdatasync`).
  - Giảm tải cho ổ cứng trong trường hợp mà ứng dụng không yêu cầu đồng bộ hóa **tất cả** metadata với disk.
- `O_DIRECT` 
  - Linux cho phép ứng dụng bỏ qua cache mà truyền trực tiếp từ user space tới disk
  - Nhìn chung hiệu suất bị sẽ bị giảm nhưng lại trở nên hữu ích trong các trường hợp đặc biệt, chẳng hạn như khi ứng dụng muốn tự dùng cache riêng.
  - Flag `O_DIRECT` tự truyền dữ liệu đồng bộ, nhưng không có được sự đảm bảo về metadata giống như `O_SYNC`.
  - Để đảm bảo I/O đồng bộ, `O_DIRECT` phải được sử dụng cùng `O_SYNC` hoặc `fsync`.

#### 2.2.1 Khác biệt
Khác biệt giữa `O_SYNC` và `O_DSYNC` cũng tương tự như `fsync()` và `fdatasync()`, có thể xem ở mục 2.1.

Về phần `O_DIRECT` là *direct I/O* còn `O_SYNC` và `O_DSYNC` thuộc kiểu *synchronized I/O*:
- Từ cái tên đã cho thấy `O_DIRECT` khác biệt ở chỗ ghi trực tiếp vào vào disk từ user space, thay vì phải thông qua một lớp cache như của *synchronized I/O*.
- Do có đặc điểm như vậy mà `O_DIRECT` có thể dùng trong việc test hiệu năng disk, hoặc cũng phù hợp với những dữ liệu không cần dùng tới trong tương lai gần nhằm giảm thiểu những rủi ro có thể xảy ra trong quá trình truyền từ cache xuống disk. Điều này cũng tiết kiệm cache cho những dữ liệu cần dùng thường xuyên.
### 2.3 Flush call trong InnoDB



