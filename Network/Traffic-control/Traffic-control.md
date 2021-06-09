# TC (Traffic Control)
TC là một tập hợp các công cụ kiểm soát hàng đợi trong việc nhận và truyền gói tin trên một router.

ví dụ như quyết định xem gói nào sẽ được chấp nhận, ở tốc độ nào, vào interface nào, và sẽ ra với tốc độ bao nhiêu

## Các giải pháp được TC cung cấp
 - Giới hạn băng thông ở tốc độ cho trước - TBF, HTB
 - Giới hạn băng thông theo 1 user, dịch vụ hoặc khách hàng cụ thể - HTB, classifier trong `filter`
 - Tối đa hóa thông lượng TCP, ưu tiên truyền các gói ACK - wondershaper.
 - Dự trữ băng thông cho 1 ứng dụng hoặc người dùng cụ thể - HTB, classifying
 - Ưu tiên các luồng có khả năng trễ - PRIO (trong HTB)
 - Cân bằng tải băng thông - HTB
 - Loại bỏ một loại lưu lượng cụ thể - `filter` có policier để thực hiện drop

## Các phần tử trong TC
- Shaping: trì hoãn các gói tin ở đầu ra để đáp ứng tốc độ mong muốn.
- Scheduling: sắp xếp thử tự các gói tin ở đầu ra
- Classifying: phân loại hoặc tách lưu lượng truy cập vào hàng đợi (queue)
- Policing: đo lường và giới hạn lưu lượng truy cập trong queue cụ thể 
- Dropping: loại bỏ toàn bộ gói, luồng hoặc hàng đợi 

## Các thành phần tương ứng

|Traditional element|Linux component|
|-------------------|---------|
|shaping| `class` cho khả năng định hình|
|scheduling| bộ lập biểu `qdisc`|
|classifying|`filter` thực hiện việc phân loại |
|policing| `policier`, là 1 phần của `filter`|
|dropping| `drop`, được sử dụng bởi `policy` |
|marking| `dsmark` trong `qdisc` dùng để đánh dấu|

- `qdisc`
  - Là một bộ lập biểu dành cho các interface đầu ra. Hoạt động mặc định theo FIFO (First In First Out), hoặc tùy theo các rule được cấu hình
  - classful qdisc: có thể chứa các `class` trong bên, kèm theo `filter`
  - classless qdisc: không chứa các `class`, không kèm theo `filter`
  - `root qdisc` và `ingress qdisc` là nơi mà các gói tin sẽ phải đi qua trong quá trình truyền vào và ra trên các interface
- `class` 
  - Tồn tại bên trong classful qdisc, có thể chứ nhiều class con
  - Mỗi `class` đều có thể gán thêm `filter`, dùng để phân loại hoặc drop luồng
- `filter`
  - Phần loại các gói tin tại hàng đợi đầu ra theo các rule
  - Ví dụ:
    - Tất cả các gói từ ip 10.1.1.2 đến port 80 sẽ được class 1:11 xử lý
   
          tc filter add dev eth0 protocol ip parent 1: prio 1 u32 match ip src 10.1.1.2/32 match ip sport 80 0xffff flowid 1:11     
- `classifier`
  - Cho phép người dùng phân loại gói tin dựa theo thuộc tính, phổ biến `u32`
  - Là một phần của `filter`
- `policier`
  - Là một phần của `filter`
- `drop`
  - Là một phần của `policier`

- Handle
  - tất cả các class và classful qdisc cần 1 mã định danh duy nhất.
  - Mã định danh duy nhất này được biết đến như 1 handle (bộ xử lí) và gồm 2 thành phần:
    - major number: Tất cả các đối tượng có cùng nguồn gốc phải có chung số `major`
    - minor number: xác định đối tượng là `qdisc` nếu `minor = 0`, còn giá trị khác là `class`
  - `root qdisc` - 1:0
