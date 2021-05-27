# Etherchannel
Là một kỹ thuật nhóm hai hay nhiều đường kết nối truyền tải dữ liệu vật lý (Link Aggregation) thành một đường ảo duy nhất (Logic), có Port ảo thậm chí cả MAC ảo nhằm mục đích tăng tốc độ truyền dữ liệu và khả năng dự phòng (Redundancy) cho hệ thống.

![Alt](https://images.viblo.asia/full/2b893980-26d3-49bf-894f-d60d2b8f15df.gif)

- EtherChannel có thể bó từ 2 đến 8 link FE, GE, 10GE thành 1 link logical và quản lý các port thuộc EtherChannel như 1 port duy nhất
- Switch hoặc thiết bị ở 2 đầu EtherChannel phải hiểu và sử dụng công nghệ EtherChannel để đảm bảo hoạt động đúng và chống loop
- Sử dụng thuật toán hash để quyết định đường link truyền dữ liệu
- Nếu một trong các link thuộc EtherChannel bị down thì traffic sẽ tự động chuyển sang link khác trong channel
- Yêu cầu 2 switch phải tương đồng về Tốc đô, băng thông, full duplex, Native VLAN và các VLANs, Switchport mode

## Phân loại
Có 2 loại giao thức cài đặt EtherChannel:
- **LACP (Link Aggregation Control Protocol)**
  - Là giao thức cấu hình EtherChannel chuẩn quốc tế IEEE 802.3ad và có thể dùng được cho hầu hết các thiết bị thuộc các hãng khác nhau, LACP hỗ trợ ghép tối đa 16 Link vật lý thành một Link luận lý (8 Port Active – 8 Port Passive).
  - LACP có 3 chế độ:
    - On: Chế độ cấu hình EtherChannel tĩnh, chế độ này thường chỉ được dùng trong môi trường lab, bởi khi cấu hình phụ thuộc vào con người nên hoàn toàn không có bước thương lượng trao đổi chính sách giừa 2 bên, dẫn đến khả năng Loop cao và bị STP Block.
    - Active: Chế độ tự động – Tự động thương lượng với đối tác
    - Passive: Chế độ bị động – Chờ được thương lượng    
- **PAgP (Port Aggregation Protocol)**
  - Là giao thức cấu hình EtherChannel độc quyền của các thiết bị hãng Cisco và chỉ hỗ trợ ghép tối đa 8 Link vật lý.
  - PAgP cũng có 3 chế độ tương tự LACP, chỉ khác tên gọi:
    - On
    - Desirable
    - Auto

Cú pháp
  - `(config-if)#channel-group 1 mode [on/desirable/active/passive/auto]`
Câu lệnh kiểm tra
  - `show etherchannel summary`

# STP (Spanning tree protocol)
