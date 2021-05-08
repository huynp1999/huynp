# Mount point
Tất cả các phân vùng được gắn vào hệ thống thông qua một mount point, từ đó xác định vị trí hệ thống tệp dữ liệu. Thông thường, tất cả các phân vùng được kết nối thông qua root (/).

## Mounting
Cú pháp `mount [partition] [directory]`
Ví dụ khi cắm usb:

`mount /dev/usb /home/usb`

để có thể truy cập vào bộ nhớ của usb thông qua thư mục `/home/usb`

## Unmounting
Dùng khi ngắt kết nối thiết bị khỏi hệ thống, hoặc khi muốn check bằng fsck.
Ví dụ khi rút usb:


`umount /dev/usb /home/usb`

Tương tự như khi ấn `eject` ở giao diện GUI. Điều này giảm rủi ro lỗ hoặc làm hỏng thiết bị phần cứng.
