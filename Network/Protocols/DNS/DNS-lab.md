# LAB
Trên máy chủ DNS thực hiện cài đặt BIND 9:
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/DNS/bind.PNG)

Trong đó, có 3 file chính dùng để cấu thành một DNS server:
- `/etc/named.conf`
- `/var/named/*.forward`
- `/var/named/*.reverse`

## 1. File cấu hình core `/etc/named.conf`
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/DNS/named1.PNG)

Trong đó có một số trường đáng quan tâm như:
- `listen-on port 53` interface nào lắng nghe port 53
- `directory` thư mục chứa dữ liệu DNS, cụ thể hơn là file forward và reverse
- `allow-query` cho phép dải địa chỉ nào được truy vấn vào DNS
- `forwarder` khi không có trong cache thì phải hỏi ở đâu
- `recursion` giao tiếp với các DNS server khác và trả về địa chỉ IP
- `dnssec-validation` do các DNS trong lab là local server nên chưa có đăng ký ngoài mạng thật, phải để là “no”


**Các zone**

![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/DNS/named2.PNG)

Gồm có 2 loại zone là forward và reverse.
- Forward: phân giải tên miền thành IP
- Reverse: phân giải IP thành tên miền
## 2. File forward `/var/named/*.forward`
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/DNS/named3.PNG)

Các trường thông tin của bản ghi SOA cho biết:
- `Serial` cho biết thời gian cập nhật bản ghi cuối cùng.
  - Với Linux là ngày tháng năm của bản cập nhật, còn Windows sẽ bắt đầu từ 1 và +1 với mỗi lần cập nhật
- `Refresh` chu kỳ cập nhật (mặc định là 1 ngày)
- `Retry` trong trường hợp lỗi không quét được cập nhật sẽ cố thử lại
- `Expire` thời gian giữ các bản ghi, khi bị mất kết nối giữa các server. Sau đó xoá trắng
- `TTL` thời gian các bản ghi tồn tại trong cache sau khi xoá trắng

Ý nghĩa các bản ghi xem tại [đây](https://github.com/huynp1999/huynp/blob/master/Network/Protocols/DNS/DNS.md)

## 3. File reverse `/var/named/*.reverse`
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/DNS/named4.PNG)

Thường được dùng trong các hệ thống email, yêu cầu cần phải đăng ký bản ghi ngược để có thể kiểm tra spam và nhận email

## 4. Kiểm tra hoạt động
![Alt](https://raw.githubusercontent.com/huynp1999/huynp/master/pic/network/DNS/nslookup.PNG)

Như vậy có thể thấy nameserver ở cả trong zone và ngoài Internet đều được phân giải thành IP. Ví dụ như với website 24h.com.vn có địa chỉ IP là 125.212.247.245
