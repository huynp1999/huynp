# SNMP (Simple Network Management Protocol)
Là giao thức tầng ứng dụng dùng để quản lý và giám sát các thiết bị mạng.
SNMP cung cấp ngôn ngữ chung cho các thiết bị mạng để chuyển tiếp thông tin quản lý trên nhiều loại phần cứng và phần mềm.

![image](https://user-images.githubusercontent.com/83684068/119965446-7c0b0100-bfd4-11eb-95c2-cfaafadd226e.png)

SNMP hoạt động tối ưu nhất là trong các mỗi trường mạng rộng lớn.
Việc đăng nhập thủ công và riêng lẻ vào hàng trăm hoặc nghìn node sẽ cực kỳ mất thời gian và tốn nhiều tài nguyên. 
Trong khi đó, SNMP cho phép người quản trị mạng quản lý và theo dõi hàng trăm hoặc nghìn node từ một giao diện duy nhất, thay vì phải đăng nhập thủ công và riêng lẻ vào từng node.

**SNMPv3** là phiên bản mới nhất, gồm các cải tiến bảo mật để xác thực, mã hóa và bảo vệ các gói tin trên đường truyền.
Tuy tăng cường bảo mật nhưng nó cũng khiến việc cấu hình trở nên khó khăn hơn, cũng như yêu cầu nhiều tài nguyên để xứ lý.

## Cơ chế hoạt động
Các thông tin quản lý SNMP được gửi và nhận giữa những Managers (trình quản lý) và Agents (các tác nhân).
- Managers được cài đặt trên **chủ thể quản lý (Managing Entity)**
- Agents được cài đặt trên các **thiết bị được quản lý (Managed devices)**
  - Có thể là những router, switch, máy in, v.v.

![image](https://user-images.githubusercontent.com/83684068/119968526-ccd02900-bfd7-11eb-9aba-13e5828bd6dc.png)

Giao tiếp giữa máy khách và máy chủ xoay quanh việc **kéo** và **đẩy** (Pull and Push Technologies)
- Kéo (Pull) là loại giao tiếp phổ biến nhất, ví dụ như khi phần mềm quản lý mạng gửi yêu cầu thu thập phản hồi từ các thiết bị được quản lý.
- Đẩy (Push), cho phép thiết bị được quản lý reponse SNMP khi có yêu cầu

## Các loại bản tin quản lý
1. GetRequest: được Manager -> Agent gửi đi để yêu cầu dữ liệu
2. GetNextRequest: được gửi từ Manager -> Agent yêu cầu lấy 1 giá trị OID tiếp theo trong hệ thống phân cấp MIB.
3. GetBulkRequest: Được gửi từ Manager -> Agent để lấy theo từng khối dữ liệu
4. SetRequest: gửi từ Manager -> Agent để đưa ra các cấu hình lệnh.
5. Response: Được gửi từ Agent để trả lời Request
6. Trap: 1 cảnh báo không đồng bộ được gửi bởi Agent -> Manager chỉ ra lỗi hoặc sự cố đã xảy ra.
7. InformRequest: xác nhận đã nhận được thông báo lỗi Trap
8. Report: cho phép Manager xác định loại sự cố đã được thông báo từ Agent
