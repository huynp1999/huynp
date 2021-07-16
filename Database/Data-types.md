Mỗi kiểu dữ liệu đều có các yêu cầu lưu trữ tương ứng, việc lựa chọn kiểu dữ liệu hợp lý không chỉ tiết kiệm dung lượng mà còn cải thiện hiệu năng cho ổ đĩa.

Giả sử, tạo ra một ứng dụng để quản lý các thiết bị cho một cá nhân. Một cá nhân thông thường sở hữu 4 thiết bị thông minh (2 điện thoại, 1 laptop và 1 PC) và thường thì rất hiếm khi có trường hợp nào sử dụng quá 100 thiết bị (không tính số âm). Như vậy đối với thông tin về số thiết bị, app này chỉ cần sử dụng kiểu dữ liệu là tinyint, với giá trị lưu trữ tối đa 255. Sử dụng tinyint (1 byte) giúp không gian bộ nhớ được tiết kiệm hơn 75% khi so với int (4 byte) và 87,5% khi so với bigint (8 byte). Đối với những lượng dữ liệu lớn lên đến Gigabyte, ngoài tiết kiệm không gian lưu trữ, lựa chọn kiểu dữ liệu hợp lý giúp gia tăng tốc độ xử lý cho đĩa như các hoạt động đọc, ghi, sao lưu, kiểm tra,...

## Các kiểu dữ liệu số trong MySQL
### Kiểu dữ liệu số

- TINYINT (1 byte)
  - Một số nguyên rất nhỏ.
- SMALLINT (2 byte)
  - Một số nguyên nhỏ.
- MEDIUMINT (3 byte)
  - Một số nguyên trung bình.
- INT (4 byte)
  - Một số nguyên trung bình.
- BIGINT (8 byte)
  - Một số nguyên lớn.
| Kiểu dữ liệu | Độ dài (số byte) | Giá trị nhỏ nhất (Có dấu) | Giá trị lớn nhất (Có dấu) | Giá trị nhỏ nhất (Không dấu) | Giá trị lớn nhất (Không dấu) |
|--------------|------------------|---------------------------|---------------------------|------------------------------|------------------------------|
| TINYINT | 1 | -128 | 0 | 127 | 255 |
| SMALLINT | 2 | -32768 | 0 | 32767 | 65535 |
| MEDIUMINT | 3 | -8388608 | 0 | 8388607 | 16777215 |
| INT | 4 | -2147483648 | 0 | 2147483647 | 4294967295 |
| BIGINT | 8 | -263 | 0 | 263-1 | 264-1 |

- FLOAT (4 byte)
  - Một số thập phân loại nhỏ có dấu chấm động. Tham số (M) dùng để xác định kích thước tối đa của phần nguyên (nằm bên trái dấu chấm) và (D) kích thước tối đa phần thập phân. Nếu (M,D) không được khai báo, giá trị được set dựa trên sức mạnh phần cứng. Phần thập phân có thể sử dụng tối đa 24 số.
- DOUBLE (8 byte)
  - Một số thập phân loại lớn có dấu chấm động. Với hai tham số (M,D) tương tự như FLOAT. Phần thập phân có thể sử dụng 53 số. REAL cũng tương tự như DOUBLE.
- DECIMAL
  - Một dấu thập phân có dấu chấm cố định. Được sử dụng để đảm bảo độ chính xác (precision), ví dụ như với dữ liệu tiền tệ.
  - Độ dài tối đa các số cho DECIMAL là 65.
  - Tham số (M,D) mặc định là (10,0), tức là là nó có thể lưu trữ một giá trị có 10 chữ số và 0 phần thập phân.

Ngoài ra, MySQL hỗ trợ tùy chọn chỉ định độ dài hiển thị:
- (N) tại đây N là một số nguyên hiển thị chiều rộng cho kiểu độ dài lên đến N chữ số.
- ZEROFILL các khoảng đệm (padding) được thay thế bởi số 0. Ví dụ với cột kiểu INT(4) ZEROFILL, số 1 sẽ hiển thị thành 0001.

### Kiểu dữ liệu Data và Time
- DATE
  - Sử dụng khi chỉ muốn lưu trữ thông tin ngày tháng năm.
  - Định dạng hiển thị YYYY-MM-DD, phạm vi '1000-01-01' tới '9999-12-31'.
- DATETIME (YYYY-MM-DD HH:MM:SS)\
  - Sử dụng khi cần giá trị lưu trữ cả thông tin ngày tháng năm và thời gian.
  - Định dạng hiển thị YYYY-MM-DD HH:MM:SS
  - Phạm vi '1000-01-01 00:00:00' tới '9999-12-31 23:59:59'.
- TIMESTAMP
  - Lưu trữ cả hai thông tin ngày tháng và thời gian. Giá trị này sẽ chuyển đổi từ múi giờ hiện tại sang UTC trong khi lưu trữ, và chuyển trở lại múi giờ hiện tại khi lấy dữ liệu ra.
  - Nếu không được chỉ định, cột TIMESTAMP đầu tiên trong bảng sẽ được xác định để tự động đặt thành ngày và giờ của sửa đổi gần đây nhất. Điều này giúp TIMESTAMP phù hợp với những hoạt động như INSERT và UPDATE.
  - Phạm vi '1970-01-01 00:00:01' UTC tới '2038-01-19 03:14:07' UTC
- TIME
  - MySQL lấy và hiển thị thời gian theo định dạng 'HH:MM:SS' (hoặc 'HHH:MM:SS' khi cần giá trị giờ lớn).
  - Phạm vi '-838:59:59' tới '838:59:59'.
  - Kiểu TIME không đơn thuần chỉ mô tả thời gian trong ngày (24 giờ), mà nó có thể là thời gian trôi qua hoặc khoảng thời gian giữa hai sự kiện (thậm trí có giá trị âm).
- YEAR(M)
  - Sử dụng 1-byte để mô tả giá trị. Có thể khai báo YEAR(2) hoặc YEAR(4) chỉ định rõ chiều rộng hiển thị là 2 hay 4 ký tự, mặc định là 4.
  - 
### Kiểu dữ liệu chuỗi trong MySQL
  - CHAR: chiều dài chuỗi cố định, nhanh hơn so với VARCHAR
  - VARCHAR: chiều dài chuỗi thay đổi
  - BLOB, TINYBLOB, MEDIUMBLOB, LONGBLOB: chuỗi được lưu ở dạng nhị phân
  - TEXT, TINYTEXT, MEDIUMTEXT, LONGTEXT: tương đương với BLOB nhưng sử dụng bộ ký tự khác, thay vì là nhị phân của BLOB
  - ENUM
