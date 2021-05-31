# DHCP (Dynamic Host Configuration Protocol)
Là giao thức tự động phân phối địa chỉ IP đến các thiết bị trong mạng, để từ đó có thể truy cập vào internet.\

## Cách thức hoạt động
DHCP hoạt động dựa trên mô hình client-server. Một thiết bị client yêu cầu địa chỉ IP tới Router hoặc một DHCP Server (host), sau đó host sẽ gán 1 địa chỉ IP khả dụng cho phép client truy cập vào Internet.

DHCP server quản lí pool của IP address và các thông số cấu hình như default gateway, domain name, name servers và time servers.

![image](https://user-images.githubusercontent.com/83684068/120138210-3fbbe880-c200-11eb-8999-1a9e559e8e39.png)

Cụ thể hơn, quy trình giao tiếp bằng các packet:
- Khi có một thiết bị Client khởi động, nó sẽ gửi broadcast packet **DHCP DISCOVER** tới Router hoặc một DHCP Linux Server (packet chứa MAC của Client)
  - Nếu client thấy DHCP server sau 4 lần tìm, nó sẽ phát ra 1 địa chỉ IP riêng cho mình trong dãy 169.254.0.0 đến 169.254.255.255. Trong khi vẫn duy trì phát tín hiệu Broadcast.
- Nếu tìm được, DHCP Server sẽ tìm địa chỉ IP khả dụng trong pool chỉ định, rồi cấp phát lại cho thiết bị bằng gói **DHCP OFFER.
- Client gửi broadcast gói tin **DHCP request** để chấp nhận IP được cấp
- Cuối cùng, Server gửi gói tin **DHCP ACK** để xác nhận lại với Client đã có IP kèm theo hạn sử dụng IP đến khi có địa chỉ mới

## Các hình thức gán địa chỉ
- **Dynamic allocation**
  - Các Client chỉ được sử dụng IP theo 1 khoảng thời gian, sau đó sẽ được Server lấy lại và làm mới cho một địa chỉ khác
- **Automatic allocation**
  - Client được gán vĩnh viễn một IP cố định
  - DHCP server tạo một bảng địa chỉ IP để có thể ưu tiên gán các IP đã đặt trước đó
- **Manual allocation (static allocation)**
  - DHCP server gán IP theo địa chỉ MAC cụ thể của từng client.
