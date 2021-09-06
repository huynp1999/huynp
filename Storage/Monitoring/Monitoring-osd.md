Tính sẵn sàng và độ tin cậy cao đòi hỏi khả năng chịu lỗi trong việc quản lý các vấn đề về phần cứng lẫn phần mềm.
Ceph không có *single point-of-failure* và vẫn có thể phục vụ dữ liệu khi ở chế độ "degraded".
Data placement trong Ceph sử dụng một lớp điều hướng để đảm bảo rằng dữ liệu không phụ thuộc hay liên kết với các địa chỉ OSD cụ thể.
Như vậy thì việc quản trị các lỗi hệ thống đòi hỏi phải tìm đến các Placement Group (PGs) và các OSD bên dưới để tìm ra gốc rễ của vấn đề.

## Monitoring OSD
Các trạng thái của một OSD trong cluster có thể là:
- `in` trong cluster
- `out` ngoài cluster
- `up` đang hoạt động
- `down` không hoạt động

Với một OSD đang nằm trong cụm `in`:
- Nếu ở trạng thái `up` thì nó có thể đọc ghi dữ liệu bình thường, với đầy đủ các thông tin về dung lượng bộ nhớ có thể xem bằng `ceph osd df tree`.
        
        Ví dụ với osd.0 ở trạng thái up nằm trong cluster
        ID  CLASS WEIGHT  REWEIGHT SIZE    RAW USE DATA    OMAP    META     AVAIL   %USE VAR  PGS STATUS TYPE NAME
         -1       3.00000        -  60 GiB 3.2 GiB 224 MiB 180 KiB  3.0 GiB  57 GiB 5.37 1.00   -        root default
        -33       1.00000        -  20 GiB 1.1 GiB  75 MiB  44 KiB 1024 MiB  19 GiB 5.37 1.00   -            host ceph01
          0   hdd 1.00000  1.00000  20 GiB 1.1 GiB  75 MiB  44 KiB 1024 MiB  19 GiB 5.37 1.00 256     up         osd.0


- Nếu ở trạng thái `down`, Ceph sẽ migrate các PG của nó sang các OSD khác và cũng như ngừng phân phối PG cho OSD này (PGS=0 tức là không ghi dữ liệu vào đây nữa). Các thông tin còn lại về dung lượng bộ nhớ như SIZE, AVAIL, %USE vẫn được duy trì do vẫn nằm trong cluster.
 
        Ví dụ với osd.0 khi bị down nhưng vẫn nằm trong cluster
        ID  CLASS WEIGHT  REWEIGHT SIZE    RAW USE DATA    OMAP    META     AVAIL  %USE VAR  PGS STATUS TYPE NAME
         -1       3.00000        -  60 GiB 3.2 GiB 219 MiB 180 KiB  3.0 GiB  57 GiB 5.36 1.00   -       root default
        -33       1.00000        -  20 GiB 1.1 GiB  73 MiB  44 KiB 1024 MiB  19 GiB 5.36 1.00   -           host ceph01
          0   hdd 1.00000  1.00000  20 GiB 1.1 GiB  73 MiB  44 KiB 1024 MiB  19 GiB 5.36 1.00   0   down        osd.0

Với một OSD đang nằm ngoài cụm `out`:
- Dù ở trạng thái `up` hay `down` thì cũng sẽ không còn ghi dữ liệu vào đây nữa (PGS = 0), Các thông tin khác cũng không còn được lưu trữ do đã nằm ngoài và không còn thuộc quản lý của cluster.

        Ví dụ với osd.0 ở trạng thái down và nằm ngoài cluster
        ID  CLASS WEIGHT  REWEIGHT SIZE    RAW USE DATA    OMAP    META     AVAIL  %USE VAR  PGS STATUS TYPE NAME
         -1       3.00000        -  40 GiB 2.1 GiB 148 MiB 136 KiB  2.0 GiB 38 GiB 5.36 1.00   -        root default
        -33       1.00000        -     0 B     0 B     0 B     0 B      0 B    0 B    0    0   -            host ceph01
          0   hdd 1.00000        0     0 B     0 B     0 B     0 B      0 B    0 B    0    0   0   down         osd.0
        

Nếu một OSD đang ở trạng thái `down`, cũng đồng nghĩa với `out`.

Kiểm tra tổng quan các OSD, câu lệnh sẽ cho biết tổng số `x` OSD, bao nhiêu `up` (y), bao nhiêu `in` (z) và epoch là số lần map được thay đổi?

    # ceph osd stat
    x osds: y up, z in; epoch: eNNNN

Nếu số OSD `in` lớn hơn `up` thì dùng lệnh sau để làm rõ cái nào không hoạt động: (kham khảo tại [đây](https://docs.ceph.com/en/latest/rados/troubleshooting/troubleshooting-osd/#osd-not-running) nếu không bật thủ công lại đuợc):

    ceph osd tree

Có thể bật lại thủ công bằng câu lệnh `sudo systemctl start ceph-osd@1`, tuy nhiên thông thường khi OSD được set trạng thái `down` thì có nghĩa chúng cần thời gian restart và phục hồi trở lại, cụ thể những trường hợp:
1. Do vừa start hoặc restart cluster nên nó có thể chưa sẵn sàng hoạt động được ngay, vì các PG cần thời gian khởi tạo và các OSD đang trong quá trình liên kết với nhau.
2. Thêm hoặc xóa OSD, CRUSH cần thời gian phân phát PG cho các OSD khác.
3. Cluster map vừa được sửa đổi.





