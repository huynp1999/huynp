# Các kiểu dữ liệu số trong MySQL
Mỗi kiểu dữ liệu đều có các yêu cầu lưu trữ tương ứng, việc lựa chọn kiểu dữ liệu hợp lý không chỉ tiết kiệm dung lượng mà còn cải thiện hiệu năng cho ổ đĩa.

## 1. Kiểu dữ liệu số
### 1.1 Kiểu số nguyên

| Kiểu dữ liệu | Độ dài (số byte) | Giá trị nhỏ nhất (Có dấu) | Giá trị lớn nhất (Có dấu) | Giá trị nhỏ nhất (Không dấu) | Giá trị lớn nhất (Không dấu) |
|--------------|------------------|---------------------------|---------------------------|------------------------------|------------------------------|
| TINYINT | 1 | -128 | 0 | 127 | 255 |
| SMALLINT | 2 | -32768 | 0 | 32767 | 65535 |
| MEDIUMINT | 3 | -8388608 | 0 | 8388607 | 16777215 |
| INT | 4 | -2147483648 | 0 | 2147483647 | 4294967295 |
| BIGINT | 8 | -2^(63) | 0 | 2^(63)-1 | 2^(64)-1 |

#### 1.1.1 Khác biệt giữa các kiểu số nguyên
Giả sử, tạo ra một ứng dụng để quản lý các thiết bị cho một cá nhân. Một cá nhân thông thường sở hữu 4 thiết bị thông minh (2 điện thoại, 1 laptop và 1 PC) và thường thì rất hiếm khi có trường hợp nào sử dụng quá 100 thiết bị (không tính số âm). Như vậy đối với thông tin về số thiết bị, app này chỉ cần sử dụng kiểu dữ liệu là tinyint, với giá trị lưu trữ tối đa 255. Sử dụng tinyint (1 byte) giúp không gian bộ nhớ được tiết kiệm hơn 75% khi so với int (4 byte) và 87,5% khi so với bigint (8 byte). Đối với những lượng dữ liệu lớn lên đến Gigabyte, ngoài tiết kiệm không gian lưu trữ, lựa chọn kiểu dữ liệu hợp lý giúp gia tăng tốc độ xử lý cho đĩa như các hoạt động đọc, ghi, sao lưu, kiểm tra,...

### 1.2 Kiểu số thập phân
- FLOAT (4 byte)
  - Một số thập phân loại nhỏ có dấu chấm động. Tham số (M) dùng để xác định kích thước tối đa của phần nguyên (nằm bên trái dấu chấm) và (D) kích thước tối đa phần thập phân. Nếu (M,D) không được khai báo, giá trị được set dựa trên sức mạnh phần cứng. Phần thập phân có thể sử dụng tối đa 24 số.
- DOUBLE (8 byte)
  - Một số thập phân loại lớn có dấu chấm động. Với hai tham số (M,D) tương tự như FLOAT. Phần thập phân có thể sử dụng 53 số. REAL cũng tương tự như DOUBLE.

| Kiểu dữ liệu | Độ dài (Số Bytes) | Giá trị nhỏ nhất (Có dấu) | Giá trị lớn nhất (Có dấu) | Giá trị nhỏ nhất (Không dấu) | Giá trị lớn nhất (Không dấu) |
|--------------|------------------|---------------------------|---------------------------|------------------------------|------------------------------|
| FLOAT | 4 | -3.402823466E+38 |  -1.175494351E-38 |  1.175494351E-38  | 3.402823466E+38 |
| DOUBLE | 8 | -1.7976931348623157E+ 308 | -2.2250738585072014E- 308 | 0, and 2.2250738585072014E- 308  | 1.7976931348623157E+ 308 |

- DECIMAL
  - Một dấu thập phân có dấu chấm cố định. Được sử dụng để đảm bảo độ chính xác (precision), ví dụ như với dữ liệu tiền tệ.
  - Độ dài tối đa các số cho DECIMAL là 65.
  - Tham số (M,D) mặc định là (10,0), tức là là nó có thể lưu trữ một giá trị có 10 chữ số và 0 phần thập phân.

Ngoài ra, MySQL hỗ trợ tùy chọn chỉ định độ dài hiển thị:
- (N) tại đây N là một số nguyên hiển thị chiều rộng cho kiểu độ dài lên đến N chữ số.
- ZEROFILL các khoảng đệm (padding) được thay thế bởi số 0. Ví dụ với cột kiểu INT(4) ZEROFILL, số 1 sẽ hiển thị thành 0001.

## 2. Kiểu dữ liệu về thời gian
### 2.1 Kiểu dữ liệu thời gian đầy đủ
- DATE
  - Sử dụng khi chỉ muốn lưu trữ thông tin ngày tháng năm.
  - Định dạng hiển thị YYYY-MM-DD, phạm vi '1000-01-01' tới '9999-12-31'.
- DATETIME (YYYY-MM-DD HH:MM:SS)
  - Sử dụng khi cần giá trị lưu trữ cả thông tin ngày tháng năm và giờ.
  - Định dạng hiển thị YYYY-MM-DD HH:MM:SS
  - Phạm vi '1000-01-01 00:00:00' tới '9999-12-31 23:59:59'.
- TIMESTAMP
  - Lưu trữ cả hai thông tin ngày tháng và giờ. Giá trị này sẽ chuyển đổi từ múi giờ hiện tại sang UTC trong khi lưu trữ, và chuyển trở lại múi giờ hiện tại khi lấy dữ liệu ra.
  - Nếu không được chỉ định, cột TIMESTAMP đầu tiên trong bảng sẽ được xác định để tự động đặt thành ngày và giờ của sửa đổi gần đây nhất. Điều này giúp TIMESTAMP phù hợp với những hoạt động như INSERT và UPDATE.
  - Phạm vi '1970-01-01 00:00:01' UTC tới '2038-01-19 03:14:07' UTC

#### 2.1.1 Khác biệt giữa DATETIME và TIMESTAMP
Cả 2 đều hiển thị ngày tháng năm và thời gian. Nhưng TIMESTAMP ưu việt hơn tại ở cách dữ liệu khi lưu trữ sẽ được convert thành UTC. UTC là chuẩn giờ quốc tế hoạt động dựa trên đồng hồ nguyên tử (loại đồng hồ chính xác nhất hiện nay), điều này đảm bảo cho dữ liệu khi lấy ra sau một khoảng thời gian mà vẫn chạy chính xác.

Hơn nữa, TIMESTAMP hỗ trợ tự động đặt ngày giờ của sửa đổi gần đây nhất. Điều này giúp TIMESTAMP phù hợp với những hoạt động như INSERT và UPDATE.

### 2.2 Kiểu dữ liệu thời gian riêng
- TIME
  - MySQL lấy và hiển thị thời gian theo định dạng 'HH:MM:SS' (hoặc 'HHH:MM:SS' khi cần giá trị giờ lớn).
  - Phạm vi '-838:59:59' tới '838:59:59'.
  - Kiểu TIME không đơn thuần chỉ mô tả thời gian trong ngày (24 giờ), mà nó có thể là thời gian trôi qua hoặc khoảng thời gian giữa hai sự kiện (thậm trí có giá trị âm).
- YEAR(M)
  - Sử dụng 1-byte để mô tả giá trị. Có thể khai báo YEAR(2) hoặc YEAR(4) chỉ định rõ chiều rộng hiển thị là 2 hay 4 ký tự nhưng không khác nhau về giá trị, mặc định là 4.
 

## 3. Kiểu dữ liệu chuỗi trong MySQL
### 3.1 Kiểu VAR và VARCHAR

- CHAR
  - Chứa chuỗi không phải nhị phân (non-binary strings). Độ dài là cố định theo khai báo. Khi lưu trữ chúng được độn thêm bên phải (right-padded) để có độ dài theo chỉ định
  - Khoảng trắng phía trước (Trailing spaces) được loại bỏ. Phạm vi các ký tự từ 0 -> 255.
- VARCHAR
  - Chứa các chuỗi không phải nhị phân (non-binary strings). Chuỗi có chiều dài thay đổi.
  - Phạm vi các ký tự từ 0 -> 65,535

#### 3.1.1 Khác biệt giữa VAR và VARCHAR
Nhìn chung, kiểu dữ liệu CHAR và VARCHAR là tương tự nhau. Một số điểm khác nhau ở cách chúng được lưu trữ và truy xuất. Chúng cũng khác nhau về chiều dài tối đa và giữ lại hay không khoảng trắng phía trước (trailing spaces). Hơn nữa, CHAR độ dài cố định nên tốc độ truy xuất cũng nhanh hơn.

![image](https://user-images.githubusercontent.com/83684068/125927311-72ba2714-e8da-4c67-822a-69ec43a1e3df.png)

### 3.2 Kiểu BLOB và TEXT
BLOB và TEXT đều không cần chỉ định độ dài. Thay vào đó sẽ được chia thành những kiểu dữ liệu cụ thể như TINY, MEDIUM, LONG.
- BLOB
  - BLOB được sử dụng để lưu trữ các lượng dữ liệu nhị phân lớn, chẳng hạn như dữ liệu file hình ảnh hoặc các loại tệp khác.
  - chuỗi được lưu ở dạng nhị phân
- TEXT
  - tương đương với BLOB nhưng sử dụng bộ ký tự riêng (nonbinary strings) thay vì là nhị phân như của BLOB.
  - TEXT thường được sử dụng các dữ liệu văn bản

| Loại | Độ dài|
| --- | --- |
| TINYBLOB/TINYTEXT | Chiều dài tối đa 256 ký tự. |
| MEDIUMBLOB/MEDIUMTEXT | Chiều dài tối đa 16777215 ký tự. |
| LONGBLOB/MEDIUMTEXT | Chiều dài tối đa 4294967295 ký tự. |

### 3.3 Kiểu ENUM
- ENUM
  - Một kiểu chỉ định hằng số. ENUM là một đối tượng chuỗi có giá trị được chọn từ một danh sách các giá trị được cho trước (có thể là NULL) ở thời điểm tạo ra bảng. Ví dụ:

        CREATE TABLE shirts (
            name VARCHAR(40),
            size ENUM('small', 'medium', 'large'));
        INSERT INTO shirts (name, size) VALUES ('dress','large'), ('t-shirt','medium'),
          ('polo','small');
        SELECT name, size FROM shirts;
        +-------------+--------+
        | name        | size   |
        +-------------+--------+
        | dress       | large  |
        | t-shirt     | medium |
        | polo        | small  |
        +-------------+--------+
