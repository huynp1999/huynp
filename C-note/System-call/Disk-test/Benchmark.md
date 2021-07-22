O_SYNC (thông số  tương tự với fsync())

| Buffer size | Write rate | Write time |
| --- |:------:|:-----:|
| 40MB    |    38MB/s | 1s |
| 80MB    |     38MB/s | 2s |
| 128MB    |     30.50MB/s | 4s |
| 512MB    |     32.53MB/s | 15s |
| 1GB    |    31.77MB/s | 30s |
| 2GB    |    32.88MB/s | 58s |

O_DSYNC (thông số  tương tự với fdatasync())

| Buffer size | Write rate | Write time |
| --- |:------:|:-----:|
| 40MB    |     38MB/s | 1s |
| 80MB    |     73MB/s | 1s |
| 128MB    |     61MB/s | 2s |
| 512MB    |     61MB/s | 8s |
| 1GB    |     50.16MB/s | 19s |
| 2GB    |    30.12 MB/s | 63s |

O_DIRECT

| Buffer size | Write rate | Write time |
| --- |:------:|:-----:|
| 40MB    |    40MB/s | <1s |
| 80MB    |     76MB/s | 1s |
| 128MB    |     61MB/s | 2s |
| 512MB    |     54.22MB/s | 9s |
| 1GB    |     59.56MB/s | 16s |
| 2GB    |     50.18MB/s | 39s |

## Nhận xét
Có thể thấy tốc độ trung bình khi sử dụng O_DIRECT là cao nhất, như đã nói tại [đây](https://github.com/huynp1999/huynp/blob/master/C-note/System-call/O_SYNC-O_DIRECT.md), O_DIRECT bỏ qua hoặc ít bị phụ thuộc vào kernel buffer và có thể ghi thẳng dữ liệu xuống thiết bị vật lý (quá trình còn được gọi là DMA (Direct Memory Access)).

O_SYNC và O_DSYNC ngược lại, chúng cần copy dữ liệu từ user buffer sang kernel buffer trong quá trình ghi. Do vậy mà cần nhiều thời gian hơn, tốc độ truyền cũng bị giảm so với O_DIRECT.

Khi so sánh giữa O_SYNC và O_DSYNC, thì O_DSYNC có tốc độ trung bình cao hơn vì flag này chỉ flush những metadata cần thiết cho quá trình đọc lần sau. Còn O_SYNC sẽ flush tất cả metadata mà không phân biệt, do vậy mà tốc độ truyền sẽ chậm hơn O_DSYNC
