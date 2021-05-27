# STP (Spanning tree protocol)
Spanning Tree Protocol (STP) là một giao thức ngăn chặn loop trong các trường hợp dự phòng.

Hai loại loop trên layer 2:
- **Broadcast storm**
  - PC A tiến hành gửi một broadcast frame vào hệ thống
  - Switch X nhận được frame này nó sẽ đẩy ra tất cả các port đến Switch Y.
  - Switch Y nhận được broadcast frame này lại tiếp tục gửi ra tất cả các port trừ port nhận vào và cứ thế tạo thành vòng lặp giữa giữa SwX và SwY
  - Broadcast frame được nhân bản và flood đến một mức độ Switch không còn khả năng xử lý thì sẽ bị treo.

![Alt](https://itforvn.com/wp-content/uploads/2017/09/Spanning-Tree-v%C3%A0-cach-thuc-hoat-dong-2.png)

- Trùng Frame
  - PC A gửi một unicast frame đến PC B khi mà địa chỉ MAC của B chưa được cập nhật, hoặc vừa được xoá khỏi bảng MAC của Switch
  - Switch sẽ xử lý các frame này như một broadcast frame và flood ra tất cả các port trừ port nhận vào.
  - Switch X và Switch Y đều thực hiện flood frame này ra nhiều port khiến PC B phải xử lí frame này 2 lần.
 
![Alt](https://itforvn.com/wp-content/uploads/2017/09/Spanning-Tree-v%C3%A0-cach-thuc-hoat-dong-3.png)

Như vậy STP được tạo ra để bầu chọn và block port để tránh những trường hợp loop như trên.

## Cơ chế hoạt động
1. Bầu chọn Root-bridge
2. Lựa chọn Root-port trên các switch còn lại 
3. Lựa chọn các Designated-port
4. Block các port còn lại

![Alt](https://vnpro.vn/upload/user/images/Th%C6%B0%20Vi%E1%BB%87n/ccc.jpg)

### 1. Bầu chọn Root-bridge
Trong một tiến trình STP, các Switch sẽ giao tiếp với nhau thông qua các gói tin BPDU (Bridge Protocol Data Unit)  được gửi từ Root-bridge. BPDU chứa giá trị quan trọng Bridge-ID của các switch, dùng để dịnh danh mỗi Switch khi tham gia tiến trình STP.
- Đầu tiên sẽ so sánh xem Switch nào có số Priority thấp nhất sẽ được đặt làm Root-Bridge
- Nếu có Priority bằng nhau thì sẽ tiến tới so sánh MAC, Sw nào có MAC nhỏ nhất sẻ làm Root-Bridge.
  - Priority (2byte) có giá trị từ 0 – 65535 (mặc định là 32768)
  - MAC address (6byte)
- Sau khi đã bầu chọn được Root-Bridge thì chỉ có Switch root mới gửi BPDU ra khỏi cổng để duy trì tiến trình STP (gửi 2s/lần). Các SW con nhận, bổ sung và forward thông tin này.
### 2. Lựa chọn Root-port
- Root-port là port có đường về Root-bridge có tổng cost nhỏ nhất.
- Mỗi non-Rootswitch chỉ có 1 Root-port
- Path-cost là giá trị cost trên từng cổng của Switch.
- Nguyên tắc tính path-cost: tính từ Root-switch -> switch muốn tính
  - Đi vào: cộng vào tổng cost
  - Đi ra: không cộng
- Nếu tổng cost bằng nhau sẽ xét đến port-ID
  - Port-ID cấu thành từ port-priority (0-255 mặc định là 128) và port-number(là số vị trí vật lý)
### 3. Lựa chọn Designated-port
- Tất cả các port của Root-switch đều là Designated port
- Đối diện với Root-port luôn là Designated port (không có ý nghĩa ngược lại).
- Là port cung cấp đường về Root-switch trên phân đoạn mạng đang xét mà có tổng path-cost là nhỏ nhất.
### 4. Block port
- Port còn lại không có vai trò là Root hoặc Designated sẽ bị Block.
- Khi 1 trong các phân đoạn khác bị đứt thì phân đoạn port block sẽ được mở ra để chạy.
- Khi phân đoạn trên có lại thì phân đoạn block sẽ tiếp tục bị block lại

![Alt](https://vnpro.vn/upload/user/images/Th%C6%B0%20Vi%E1%BB%87n/ddd.jpg)

## Các trạng thái hoạt động
Các trạng thái khi Switch khởi động:
- Disable: down
- Blocking: nhận BDPU, ko gửi BPDU, không học MAC, không forward frame
- Listening: nhận BDPU, gửi BPDU, không học MAC, không forward frame
- Leaning: nhận BDPU, gửi BPDU, học MAC, không forward frame
- Forwarding: nhận BDPU, gửi BPDU, học MAC, forward frame
