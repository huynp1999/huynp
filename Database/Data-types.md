Mỗi kiểu dữ liệu đều có các yêu cầu lưu trữ tương ứng, việc lựa chọn kiểu dữ liệu hợp lý không chỉ tiết kiệm dung lượng mà còn cải thiện hiệu năng cho ổ đĩa.

Giả sử, tạo ra một ứng dụng để quản lý các thiết bị cho một cá nhân. Một cá nhân thông thường sở hữu 4 thiết bị thông minh (2 điện thoại, 1 laptop và 1 PC) và thường thì rất hiếm khi có trường hợp nào sử dụng quá 100 thiết bị (không tính số âm). Như vậy đối với thông tin về số thiết bị, app này chỉ cần sử dụng kiểu dữ liệu là tinyint, với giá trị lưu trữ tối đa 255. Sử dụng tinyint (1 byte) giúp không gian bộ nhớ được tiết kiệm hơn 75% khi so với int (4 byte) và 87,5% khi so với bigint (8 byte). Đối với những lượng dữ liệu lớn lên đến Gigabyte, ngoài tiết kiệm không gian lưu trữ, lựa chọn kiểu dữ liệu hợp lý giúp gia tăng tốc độ xử lý cho đĩa như các hoạt động đọc, ghi, sao lưu, kiểm tra,...

## Các kiểu dữ liệu số trong MySQL
### Kiểu dữ liệu số

- TINYINT (1 byte)
  - Một số nguyên rất nhỏ. Giá trị có dấu -128 -> 127. Giá trị không dấu 0 -> 255
- SMALLINT (2 byte)
  - Một số nguyên nhỏ. Giá trị có dấu -32768 -> 32767. Giá trị không dấu 0 -> 65535
- MEDIUMINT (3 byte)
  - Một số nguyên trung bình. Giá trị có dấu -8388608 -> 8388607. Giá trị không dấu 0 -> 16777215
- INT (4 byte)
  - Một số nguyên trung bình. Giá trị có dấu -2147483648 -> 2147483647. Giá trị không dấu 0 -> 4294967295
- BIGINT (8 byte)
  - Một số nguyên lớn. Giá trị có dấu -9223372036854775808 -> 9223372036854775807.Giá trị không dấu 0 -> 18446744073709551615
- FLOAT (4 byte)
  - Một số thập phân loại nhỏ có dấu chấm động. Tham số (M) dùng để xác định kích thước tối đa của phần nguyên (nằm bên trái dấu chấm) và (D) kích thước tối đa phần thập phân. Nếu (M,D) không được khai báo, giá trị được set dựa trên sức mạnh phần cứng. Phần thập phân có thể sử dụng tối đa 24 số.
  - Giá trị có dấu -3.402823466E+38 -> -1.175494351E-38. Giá trị không dấu 0 và 1.175494351E-38 ->	3.402823466E+38
- DOUBLE (8 byte)
  - Một số thập phân loại lớn có dấu chấm động. Với hai tham số (M,D) tương tự như FLOAT. Phần thập phân có thể sử dụng 53 số. REAL cũng tương tự như DOUBLE.
  - Giá trị có dấu -1.7976931348623157E+308 -> -2.2250738585072014E-308.
  - Giá trị không dấu 0 và 2.2250738585072014E-308 -> 1.7976931348623157E+308
- DECIMAL
  - Một dấu thập phân có dấu chấm cố định. Được sử dụng để đảm bảo độ chính xác (precision), ví dụ như với dữ liệu tiền tệ.
  - Độ dài tối đa các số cho DECIMAL là 65.

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
