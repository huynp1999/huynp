## Khác biệt giữa O_SYNC và O_DIRECT

|  O_DIRECT (*direct I/O*) | O_SYNC, O_DSYNC (*synchronized I/O*) |
| ------------------------ |--------------------------------------|
| Loại bỏ hoặc giảm thiểu sự tham gia của lớp cache và thực hiện các vào ra trực tiếp với disk.   |  Tương tác với disk thông qua cache    | 
|  Không có đảm bảo nào rằng hàm này sẽ return sau khi tất cả dữ liệu đã được chuyển.   | Đảm bảo chỉ return khi tất cả data được đồng bộ với disk (sự đảm bảo này còn phụ thuộc vào khả năng của OS)  |
| Tiết kiệm tài nguyên cho memory và CPU, để dành cho những tác vụ khác | Cần nhiều tài nguyên hơn |
| Dành cho những dữ liệu không quan trọng, hoặc có thể khôi phục được | Dành cho những dữ liệu yêu cầu tính toàn vẹn cao |
|  Direct I/O không cần đợi xác nhận nên sẽ sở hữu tốc độ đọc ghi tối đa  | Do phải chờ disk controller xác nhận việc quá trình truyền hoàn tất, nên tốc độ của synchronized I/O sẽ chậm hơn    |
| Tương tác với disk controller thông qua write-through và non-read-ahead mode  |   Áp dụng write-back, read-ahead mode   | 

## Benchmark
Sử dụng `fio` để test hiệu suất ghi (tương tự như đọc) giữa hai kiểu direct và sync I/O.

Fio job file:

    [global]
    bs=1M
    ioengine=sync
    iodepth=4
    size=2g
    direct=[0/1]
    runtime=60
    filename=/home/huynp/fio/t
    sync=[0/1]

    [rand-write]
    rw=randwrite
    stonewall

Kiểm tra hiệu năng với sync I/O (sync = 1 tức là sử dụng O_SYNC):
    
    WRITE: bw=22.2MiB/s (23.3MB/s), 22.2MiB/s-22.2MiB/s (23.3MB/s-23.3MB/s), io=1333MiB (1398MB), run=60016-60016msec
    
Còn với direct I/O (direct = 1, sync = 0)

    WRITE: bw=42.2MiB/s (44.2MB/s), 42.2MiB/s-42.2MiB/s (44.2MB/s-44.2MB/s), io=2048MiB (2147MB), run=48537-48537msec
    
Xét về tốc độ ghi khi sử dụng sync bị giảm gần nửa so với khi sử dụng direct, bởi sync cần xác nhận của disk controller mỗi khi đẩy dữ liệu xuống.

Xét về tài nguyên CPU và MEM khi sử dụng sync:

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/s.png)

Còn với direct I/O:

![](https://github.com/huynp1999/huynp/blob/master/pic/storage/direct.png)

Có thể thấy, do direct I/O bỏ qua hoặc ít phụ thuộc vào buffer/cache nên lượng tài nguyên free còn thừa nhiều hơn. Tương tự, sử dụng sync cũng sẽ yêu cầu sử dụng nhiều %CPU usage hơn.
