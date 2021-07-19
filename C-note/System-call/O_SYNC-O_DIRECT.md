## Khác biệt giữa O_SYNC và O_DIRECT

|  O_DIRECT (*direct I/O*) | O_SYNC, O_DSYNC (*synchronized I/O*) |
| ------------------------ |--------------------------------------|
| Loại bỏ hoặc giảm thiểu sự tham gia của lớp cache và thực hiện các vào ra trực tiếp với disk.   |  Tương tác với disk thông qua cache    | 
|  Không có đảm bảo nào rằng hàm này sẽ return sau khi tất cả dữ liệu đã được chuyển.   | Đảm bảo chỉ return khi tất cả data được đồng bộ với disk (sự đảm bảo này còn phụ thuộc vào khả năng của OS)  |
| Tiết kiệm tài nguyên cho memory và CPU, để dành cho những tác vụ khác | Cần nhiều tài nguyên nhưng đảm bảo độ toàn vẹn của dữ liệu cao |
|  Direct I/O không cần đợi xác nhận nên sẽ sở hữu tốc độ đọc ghi tối đa  | Do phải chờ disk controller xác nhận việc quá trình truyền hoàn tất, nên tốc độ của synchronized I/O sẽ chậm hơn    |
| Tương tác với disk controller thông qua write-through và non-read-ahead mode  |   Áp dụng write-back, read-ahead mode   | 

## Benchmark

