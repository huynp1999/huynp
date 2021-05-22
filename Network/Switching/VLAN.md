# VLAN
VLAN là viết tắt của Virtual Local Area Network hay còn gọi là mạng LAN ảo.
Một VLAN được định nghĩa là một nhóm logic các thiết bị mạng và được thiết lập dựa trên các yếu tố như chức năng, phòng ban,... của một công ty.

![Alt](https://vnpro.vn/upload/user/images/Th%C6%B0%20Vi%E1%BB%87n/V%C3%AD%20d%E1%BB%A5%20v%E1%BB%81%20VLAN.jpg)

Các thiết bị này có thể không cần kết nối vật lý, switch vật lý cũng được chia thành nhiều logic switch cho mỗi VLAN.

Ví dụ:
- Một công ty có 3 bộ phận là: Engineering, Marketing, Accounting, mỗi bộ phận trên lại trải ra trên 3 tầng.
- Để kết nối các máy tính trong một bộ phận với nhau thì ta cần lắp cho mỗi bộ phận trên mỗi tầng một switch.
- Vậy để kết nối 3 tầng trong công ty cần phải dùng tới 9 switch.
- Cách làm này rất tốn kém mà lại không thể tận dụng được hết số cổng (port) có sẵn trên switch.
- Chính vì vậy, giải pháp VLAN ra đời nhằm giải quyết vấn đề trên mà vẫn tiết kiệm được tài nguyên.

## Các khái niệm trong VLAN
- Static VLAN (VLAN Tĩnh)
  - Được tạo ra bằng cách áp đặt các cổng Switch vào một VLAN.
  - Như vậy, các thiết bị thuộc cổng Switch đó cũng thuộc về VLAN định trước.
- Dynamic VLAN (VLAN Động)
  - Sử dụng 1 server lưu trữ địa chỉ MAC của các thiết bị trong VLAN
  - Khi 1 thiết bị gắn vào Switch, Switch sẽ lấy địa chỉ MAC của thiết bị và kiểm tra trên server, nếu có sẽ được tự động cho vào VLAN
- Trunk:
  - Là một đường kết nối giữa các VLAN với nhau thông qua các Switch
  - Kĩ thuật này cho phép dùng 1 đường kết nối vật lí chung để dữ liệu của nhiều VLAN đi qua
  - Gồm có 2 giao thức trunking:
    - 802.1Q (dot1q): một giao thức phổ biến, tiêu chuẩn và được hỗ trợ bởi nhiều nhà phát triển
    - ISL: giao thức riêng của Cisco, không có nhiều loại Switch hỗ hợ
##  VLAN Trunking Protocol (VTP)
Là một giao thức hoạt động ở tầng datalink trong mô hình OSI

![Alt](https://vnpro.vn/wp-content/uploads/2015/09/vtp-domain.png)

Cơ chế hoạt động trong VTP:
1. VTP thêm bớt và chỉnh sửa các VLAN
2. VTP gửi thông điệp quảng bá "VTP domain" 5 phút 1 lần hoặc khi có sự thay đổi xảy ra trong cấu hình VLAN
3. Thông điệp VTP bao gồm: rivision number, VLAN name, VLAN number, thông tin switch có cổng gắn với mỗi VLAN
4. Với mỗi lần sửa đổi, số revision sẽ tăng lên, cho phép client dễ dàng theo dõi các sự kiện xảy ra
5. Các VTP client sẽ được đồng bộ với những thay đổi trên VTP server

Bên cạnh đó còn có VTP trasparent, đóng vai trò chỉ forward thông điệp quảng và mà không đồng bộ với chúng


## Routing VLAN
Khi thiết bị trong 1 VLAN A muốn liên lạc với thiết bị khác trong VLAN B cầng phải trải qua các thủ tục định tuyến

Các mode hoạt động:
- Trunk: dùng cho các Switch hoặc Router với nhau
- Access: dùng với computer.
- Dynamic: để cho interface tự cấu hình mode
  - Dynamic auto: tự động lấy mode của interface đối diện, mặc định là access mode (nếu cả 2 interface đều để auto thì cả 2 đều là access)
  - Dynamic desireable: tự động lấy mode phù hợp, thường là trunk
