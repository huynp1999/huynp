# tc (Traffic Control)
Trình quản lý lưu lượng `tc` nằm trong gói cài đặt `iproute2`.

Cú pháp

    tc [ OPTIONS ] OBJECT { COMMAND | help }
    
Trong đó:
- OBJECT = { qdisc | class | filter }
- OPTIONS = { -s[tatistics] | -d[etails] | -r[aw] }

Ví dụ 1: tạo qdisc(1:0) theo HTB
  
    tc qdisc add    \ (1)
    >  dev eth0     \ (2)
    >  root         \ (3)
    >  handle 1:0   \ (4)
    >  htb            (5)
    
1. add qdisc (hoặc del).
2. chỉ định thiết bị (interface) sẽ được gán queue
3. đi ra thành tc.
4. `major:minor`
5. queing discipline, được làm rõ ở phần sau

Ví dụ 2: tạo class(1:6) từ qdisc(1:0), cùng kiểu HTB

    tc class add    \ 
    >  dev eth0     \ 
    >  parent 1:0   \ (1)
    >  classid 1:6  \ (2)
    >  htb          \ 
    >  rate 256kbit \ (3)
    >  ceil 512kbit   (3)
      
1. tạo từ handle nào
2. đặt handle định danh `major = parent, minor != 0`
3. đặt tốc độ min và max dành cho luồng

## HTB (Hierarchical Token Bucket)
Sử dụng cho các thiết lập mà có 1 lượng băng thông cố định muốn phân chia cho các mục đích khác nhau.
Ví dụ:
- Đặt 1 HTB qdisc trên root của eth0, chỉ định lớp 1:30 cho default, gốc được đặt là 1: để tham chiếu.
    
      tc qdisc add dev eth0 root handle 1: htb default 30
- Tạo lớp 1:1, là hậu duệ của root (1:), lớp này cũng gán 1 HTB qdisc.

      tc class add dev eth0 parent 1: classid 1:1 htb rate 6mbit burst 15k
- Từ 1:1, tạo tiếp các class con 1:10, 1:20
- Class 1:10 có tốc độ min 5mbit

      tc class add dev eth0 parent 1:1 classid 1:10 htb rate 5mbit burst 15k
- Class 1:20 có tốc độ min 3kbit, max 6mbit

      tc class add dev eth0 parent 1:1 classid 1:20 htb rate 3kbit ceil 6mbit burst 15k
