# Truy xuất trong MySQL
## Các kiểu dữ liệu số trong MySQL
- Kiểu dữ liệu số
  - INT, TINYINT, SMALLINT, MEDIUMINT, BIGINT
  - FLOAT
  - DOUBLE
  - DECIMAL
- Kiểu dữ liệu Data và Time
  - DATE (YYYY-MM-DD)
  - DATETIME (YYYY-MM-DD HH:MM:SS)
  - TIMESTAMP
  - TIME
  - YEAR(M)
- Kiểu dữ liệu chuỗi trong MySQL
  - CHAR: chiều dài chuỗi cố định, nhanh hơn so với VARCHAR
  - VARCHAR: chiều dài chuỗi thay đổi
  - BLOB, TINYBLOB, MEDIUMBLOB, LONGBLOB: chuỗi được lưu ở dạng nhị phân
  - TEXT, TINYTEXT, MEDIUMTEXT, LONGTEXT: tương đương với BLOB nhưng sử dụng bộ ký tự khác, thay vì là nhị phân của BLOB
  - ENUM

## Ví dụ
Có sẵn một database tên `test123`, truy cập vào sử dụng nó

    use teset123;
    
Tạo một bảng thông tin về sinh viên trong database này, bao gồm các biến về mã sinh viên, họ tên, tuổi và điểm trung bình

    create table sinhvien ( mssv INT, hoten VARCHAR(255), tuoi INT, dtb FLOAT);
    
