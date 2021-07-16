# Truy xuất trong MySQL
### Tạo và nhập bảng dữ liệu
Có sẵn một database tên `test123`, truy cập vào sử dụng nó

    use test123;
    
Tạo một bảng thông tin về sinh viên trong database này, bao gồm các biến về mã sinh viên, họ tên, tuổi và điểm trung bình

    create table sinhvien ( mssv INT, hoten VARCHAR(255), tuoi INT, dtb FLOAT(3,2));
    
Nhập liệu theo cú pháp

    insert into table_name (mssv, hoten, tuoi,...) values (23, "Nguyen Van An", 24,...)
    
Bảng dữ liệu:

    mysql> SELECT * FROM sinhvien;     
    
    +------+---------------+------+------+
    | mssv | hoten         | tuoi | dtb  |
    +------+---------------+------+------+
    |   23 | Nguyen Van An |   24 | 8.12 |
    |    2 | Cao Van Cuong |   21 | 7.40 |
    |   69 | Tran Thi Binh |   20 | 7.00 |
    +------+---------------+------+------+
    3 rows in set (0,00 sec)

    
    
### Lọc dữ liệu
Sử dụng thêm câu lệnh `WHERE [condition]`
    
    SELECT * FROM sinhvien where dtb > 7.3;
    
    +------+---------------+------+------+
    | mssv | hoten         | tuoi | dtb  |
    +------+---------------+------+------+
    |   23 | Nguyen Van An |   24 | 8.12 |
    |    2 | Cao Van Cuong |   21 | 7.40 |
    +------+---------------+------+------+
    2 rows in set (0,00 sec)

Sắp xếp theo alphabet hoặc theo các toán tử logic:
    
    mysql> SELECT * FROM sinhvien where dtb > 7.3 order by mssv;

    +------+---------------+------+------+
    | mssv | hoten         | tuoi | dtb  |
    +------+---------------+------+------+
    |    2 | Cao Van Cuong |   21 | 7.40 |
    |   23 | Nguyen Van An |   24 | 8.12 |
    +------+---------------+------+------+
    2 rows in set (0,00 sec)

### Chỉnh sửa, quản lý bảng dữ liệu
Thêm một cột, đằng sau một cột cụ thể. Nếu không có AFTER mặc định sẽ được thêm vào sau cột cuối cùng

    mysql> ALTER TABLE sinhvien add COLUMN `ten` VARCHAR(30) AFTER `hoten`;
    Query OK, 0 rows affected (0,61 sec)
    Records: 0  Duplicates: 0  Warnings: 0

    mysql> SELECT * FROM sinhvien;
    +------+---------------+------+------+------+
    | mssv | hoten         | ten  | tuoi | dtb  |
    +------+---------------+------+------+------+
    |   23 | Nguyen Van An | NULL |   24 | 8.12 |
    |    2 | Cao Van Cuong | NULL |   21 | 7.40 |
    |   69 | Tran Thi Binh | NULL |   20 | 7.00 |
    +------+---------------+------+------+------+
    3 rows in set (0,00 sec)

Tách cột dữ liệu thành 2 cột mới (tách theo ký tự " ")

    UPDATE sinhvien SET ten = SUBSTRING_INDEX(hoten, ' ', -1);
    UPDATE sinhvien SET ho = SUBSTRING_INDEX(hoten, ' ', 2);
    ALTER TABLE sinhvien DROP COLUMN hoten;
    
    mysql> SELECT * FROM sinhvien;
    +------+------------+-------+------+------+
    | mssv | ho         | ten   | tuoi | dtb  |
    +------+------------+-------+------+------+
    |   23 | Nguyen Van | An    |   24 | 8.12 |
    |    2 | Cao Van    | Cuong |   21 | 7.40 |
    |   69 | Tran Thi   | Binh  |   20 | 7.00 |
    +------+------------+-------+------+------+
    3 rows in set (0,00 sec)

### Backup/restore dữ liệu
Cú pháp tạo file backup cho một hay nhiều database:

    sudo mysqldump -u [user] -p [database_1] [database_2] > [filename].sql
    
Phục hồi dữ liệu từ file backup

    mysql -u [user] -p [database_name] < [filename].sql
    
- Lưu ý, nếu không có thì cần phải tạo database trước khi phục hồi dữ liệu
