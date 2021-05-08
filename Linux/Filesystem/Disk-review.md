# `df`
Được sử dụng khi cần xem thông tin tổng quát về dung lượng của các phân vùng.

Output của lệnh `df` cho ra sáu 6 cột:
- Filesystem: tên file hệ thống.
- 1K-blocks: số kilobyte còn trống dành cho filesystem
- Used: số kilobyte block đã dùng
- Available: số block còn trống
- Use%: tỉ lệ sử dụng
- Mounted on: vị trí mà filesystem được mount trong hệ thống

`-h` (human-readable) sẽ convert các số liệu dễ đọc hơn với người dùng
![Alt](https://github.com/huynp1999/huynp/blob/master/pic/df1.png)

# `du`
Liệt kê quá trình sử dụng không gian bộ nhớ của các cây thư mục. Hữu dụng khi muốn tìm ra chính xác nơi chiếm nhiều tài nguyên nhất.

`-s` sẽ cho ra dung lượng tổng của  thư mục đích, ví dụ cần xem /etc đã sử dụng bao nhiêu dung lượng:

![Alt](https://github.com/huynp1999/huynp/blob/master/pic/du.png)
