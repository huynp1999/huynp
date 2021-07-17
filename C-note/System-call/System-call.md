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
Mặc định, `write` system call được trả về sau khi tất cả dữ liệu đã được sao chép từ user space vào cache trong system space. Không có gì đảm bảo rằng dữ liệu đã thực sự được lưu trữ. Trong trường hợp này, `fsync` và system call khác cùng loại được sử dụng để đảm bảo dữ liệu thực sự được chuyển từ cache vào ổ cứng. Các system call này được trả chỉ khi nào dữ liệu đã tới được nơi lưu trữ cố định, nếu phần cứng xảy ra lỗi sẽ được báo cáo lại.

`fsync()` chuyển (flush) tất cả dữ liệu đã được sửa đổi của file tại bộ đệm nhờ file descriptor *fd* tham chiếu đến ổ cứng. Điều này nhằm truy xuất tất cả thông tin đã thay đổi ngay cả sau khi hệ thống gặp sự cố hoặc sau khi khởi động lại. Call sẽ chặn cho đến khi thiết bị báo rằng quá trình truyền đã hoàn tất. Nó cũng flush các thông tin metadata được liên kết với tệp.

`fdatasync()` tương tự như `fsync()`, nhưng chỉ flush metadata nào cần thiết truy xuất dữ liệu tiếp theo. Mục tiêu của `fdatasync` nhằm giảm tải cho disk trong trường hợp ứng dụng không yêu cầu đồng bộ hóa **tất cả** metadata với disk.

#### 2.1.1 Khác biệt giữa 2 hàm fsync và fdatasync
Ví dụ có hai loại metadata, một loại cung cấp các thay đổi về timestamp (lần truy cập cuối cùng, lần sửa đổi cuối cùng), và loại còn lại cung cấp các thay đổi về file length.
- Có thể thấy, timestamp không cần thiết cho quá trình truy xuất file, vậy nên `fdatasync()` sẽ chỉ flush file length metadata
- Còn đối với `fsync()` sẽ flush cả hai loại, mà không cần quan tâm tới mục đích sử dụng của chúng.

Như vậy, `fdatasync()` sẽ phần nào giảm tải cho disk trong trường hợp mà ứng dụng không yêu cầu đồng bộ hóa **tất cả** metadata xuống disk.
### 2.2 Open system call
`open()` system call sẽ mở file được chỉ định theo đường dẫn. Nếu file không tồn tại, có thể thêm tag tùy chọn `O_CREAT` để tạo file mới và mở nó.
Giá trị trả về của `open()` là một file descriptor (FD). Từ FD này, các syscall khác như read, write,... có thể khai thác sử dụng file đã được mở.

- `O_SYNC`
  - Cung cấp đồng bộ hóa toàn vẹn cho **file** I/O.
  - Sau khi quá trình ghi được trả về, flush dữ liệu và tất cả metadata đến phần cứng. (tức là sau mỗi lần dữ liệu được thay đổi sẽ là một lần call đến `fsync`).
- `O_DSYNC`
  - Cung cấp đồng bộ hóa toàn vẹn cho **dữ liệu** I/O.
  - Tại thời điểm dữ liệu được trả về, dữ liệu đầu ra sẽ được chuyển sang phần cứng bên dưới, cùng với bất kỳ metadata nào cần thiết cho lần truy xuất dữ liệu sau đó (tức là sau mỗi lần dữ liệu được thay đổi sẽ là một lần call đến `fdatasync`).
- `O_DIRECT` 
  - Linux cho phép ứng dụng bỏ qua cache mà truyền trực tiếp từ buffer của user space tới disk
  - Nhìn chung hiệu suất bị sẽ bị giảm nhưng lại trở nên hữu ích trong các trường hợp đặc biệt, chẳng hạn như khi ứng dụng muốn tự dùng cache riêng.
  - Flag `O_DIRECT` cũng có thể tự flush data file, nhưng không có được sự đảm bảo về metadata giống như `O_SYNC`.
  - Để đảm bảo I/O đồng bộ, `O_DIRECT` phải được sử dụng cùng `O_SYNC` hoặc `fsync`.
  - Do có đặc điểm như vậy mà `O_DIRECT` có thể dùng trong việc test hiệu năng disk, hoặc cũng phù hợp với những dữ liệu không cần dùng tới trong tương lai gần nhằm giảm thiểu những rủi ro có thể xảy ra trong quá trình truyền từ cache xuống disk.

#### 2.2.1 Khác biệt giữa 3 flag 
Khác biệt giữa `O_SYNC` và `O_DSYNC` cũng tương tự như `fsync()` và `fdatasync()`, khác biệt ở đây là 2 flag này thuộc `open()` system call nên sẽ mở file trước.

Về phần `O_DIRECT`, là *direct I/O* còn `O_SYNC` và `O_DSYNC` thuộc kiểu *synchronized I/O*:
- *Direct I/O* loại bỏ hoặc giảm thiểu sự tham gia của lớp cache và thực hiện các I/O thẳng tới disk, trong khi *synchronized I/O* tương tác với disk thông qua cache.
- *Direct I/O* và disk controller tương tác với nhau thông qua *write-through* và *non-read-ahead* mode, còn *synchronized I/O* áp dụng [*write-back*, *read-ahead*](https://github.com/huynp1999/huynp/blob/master/Linux/Filesystem/RAID/RAID-card-function.md#data-write-policies) mode. (?)


### 2.3 Liên hệ trong InnoDB flushing
Trước tiên, flush là quá trình đẩy tất cả các sửa đổi file đang nằm trong nơi lưu trữ tạm thời như cache pages, xuống một nơi cố định là disk. Flushing cần thiết cho việc checkpoint và giải phóng vùng nhớ sau một khoảng thời gian data được lưu trữ tại cache.

Các phương pháp flush được sử dụng trong InnoDB gồm:

|  Method |  |
| ------------- |-------------|
| `fsync/fdatasync`      | Là option mặc định của `innodb_flush_method`. Với các nền tảng hỗ trợ `fdatasync()` system call, InnoDB sẽ sử dụng nó để thay thế cho `fsync()`. Cụ thể v2 system call này xem tại mục 2.1.    |
| `O_DSYNC`      | Dùng để mở và flush các log file và kết hợp với `fsync()` để flush các data log file. InnoDB không sử dụng `O_DSYNC` trực tiếp vì có vấn đề trên nhiều bản Unix.     |
|   `littlesync`   |  Option này được sử dụng để test hiệu năng và hiện không được hỗ trợ.  |
|   `nosync`   |   Option này được sử dụng để test hiệu năng và hiện không được hỗ trợ. |
|  `O_DIRECT`   |  Option này sử dụng `O_DIRECT` để mở data file, kèm theo `fsync()` để flush data và log file. Sở dĩ flag này cần `fsync()` là vì một số file system như XFS chỉ sync metadata bằng `fsync()`.    |
|    `O_DIRECT_NO_FSYNC`  | Dùng `O_DIRECT` để flush I/O nhưng không kèm theo `fsync()` nên metadata sẽ không được sync. Nếu flag này được dùng với một số file system như XFS hoặc EXT4 có thể dẫn đến sự cố crash cho MySQL. Nhìn chung, O_DIRECT nên được áp dụng đối với các hệ thống có [battery-backed](https://en.wiktionary.org/wiki/battery-backed) hỗ trợ cho cache, hoặc sở hữu tốc độ I/O cao (SSD).  |
 

### Tài liệu tham khảo
- https://linux.die.net/man/3/open
- https://linux.die.net/man/2/open
- https://man7.org/linux/man-pages/man2/open.2.html
- https://linux.die.net/man/2/fdatasync
- https://dev.mysql.com/doc/refman/8.0/en/innodb-parameters.html#sysvar_innodb_flush_method
- https://linuxkbs.blogspot.com/2014/01/what-are-exactly-odirect-osync-flags.html
- https://blog.toadworld.com/2017/10/19/data-flushing-mechanisms-in-innodb
- https://lwn.net/Articles/457667/
- https://stackoverflow.com/questions/5055859/how-are-the-o-sync-and-o-direct-flags-in-open2-different-alike
- https://stackoverflow.com/questions/41440492/why-mysql-still-use-fsync-to-flush-the-data-when-the-option-is-o-direct
