# ARP (Address Resolution Protocol)
Là một phương thức phân giải hoặc ánh xạ giữa địa chỉ lớp network (IPv4) với địa chỉ lớp datalink (MAC).

## Cấu trúc bản tin ARP
![image](https://camo.githubusercontent.com/2f7dcd904c165ab4c4c22058c4414c1a3fffc072/687474703a2f2f696d6775722e636f6d2f5a6d4b6f3570552e6a7067)
Một số trường cần quan tâm:
- Operation code
  - ARP requets = 1, ARP reply = 2, RARP request = 3, RARP reply = 4
- Sender hardware address (SHA)
  - MAC của máy gửi
- Sender protocol address (SPA)
  - IP của máy gửi
- Target hardware address (THA)
  - MAC máy cần tìm
- Target protocol address (TPA)
  - IP máy cần tìm

## Cơ chế hoạt động
<img src="https://gsephrioth.github.io/assets/img/TCP-IP/Figure7.3.png" alt="drawing" width="700"/>

Trường hợp máy tính A muốn giao tiếp với một máy B trong cùng mạng LAN, tuy nhiên lại chỉ biết IP:
1. Máy A kiểm tra cache xem đã lưu thông tin ánh xạ trước đó chưa.
2. Nếu chưa, máy A gửi ARP request trong miền Broadcast đến toàn bộ các máy trong mạng, với IP đích là IP của máy B và MAC đích là ff:ff:ff:ff:ff:ff (broadcast MAC).
3. Các thiết bị trong mạng đều nhận được gói tin ARP request, tuy nhiên chỉ máy nào đúng IP mới gửi lại ARP reply kèm trường SHA trong miền Unicast.
4. Máy A nhận được gói tin reply và update trường SHA vào ARP cache của mình. Không cần dùng tới ARP request vào lần sau.


