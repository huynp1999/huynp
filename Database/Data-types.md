Mỗi kiểu dữ liệu đều có các yêu cầu lưu trữ tương ứng, việc lựa chọn kiểu dữ liệu hợp lý không chỉ tiết kiệm dung lượng mà còn cải thiện hiệu năng cho ổ đĩa.

Giả sử, tạo ra một ứng dụng để quản lý các thiết bị cho một cá nhân. Cá nhân này sở hữu tổng cộng 4 thiết bị thông minh là 2 điện thoại, 1 lap 

## Các kiểu dữ liệu số trong MySQL
- Kiểu dữ liệu số
  - INT, TINYINT, SMALLINT, MEDIUMINT, BIGINT
  - FLOAT, DOUBLE
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
