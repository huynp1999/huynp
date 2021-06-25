# Database (cơ sở dữ liệu)
Là một tập hợp của những data (dữ liệu) có liên quan với nhau.
Database được duy trì dưới dạng tập hợp các tập tin trong hệ điều hành, hoặc được lưu trữ trong các hệ quản trị cơ sở dữ liệu.

Tùy theo hệ điều hành mà database được phân ra:
- Linux: MySQL, Mariadb
- Windows: SQL Server – MSSQL

Phân loại database theo mục đích sử dụng
- Database dạng file: dữ liệu được lưu dưới dạng file có thể là .mdb của Foxpro, Access, hay một số định dạng file khác như text, ascii, .dbf
- Database quan hệ: Các nguồn dữ liệu (thực thể) khác nhau sẽ được quy hợp, liên kết và lưu trữ trong cùng một bảng dữ liệu
- Database hướng đối tượng: bổ sung thêm các tính năng hướng đối tượng như lưu trữ các hành vi của đối tượng.
- Database bán cấu trúc: ác thông tin mô tả dữ liệu, đối tượng được trình bày trong các thẻ tag. Với ưu điểm lưu trữ được hầu hết các loại dữ liệu khác nhau.

# SQL
SQL (Structured Query Language) có nghĩa là ngôn ngữ truy vấn dữ liệu, là loại ngôn ngữ máy tính nhằm để thao tác lưu trữ và truy xuất dữ liệu được lưu trữ trong một cơ sở dữ liệu quan hệ.
SQL là ngôn ngữ chung mà bất cứ hệ thống cơ sở dữ liệu quan hệ (RDBMS) nào cũng phải đáp ứng, như: Oracle Database, SQL Server, MySQL,...

Mọi thứ trong cơ sở dữ liệu sẽ được quy ra thành nhiều bảng và có mối quan hệ với nhau. SQL giúp quản lý hiệu quả và truy vấn thông tin nhanh hơn, bảo trì thông tin dễ dàng hơn.
Việc này được làm thông qua các query, truy vấn và lấy dữ liệu từ các bảng dữ liệu.

## Các câu lệnh truy vấn trong SQL
![image](https://user-images.githubusercontent.com/83684068/123363105-04f96600-d59c-11eb-805a-a2a5f1fd323f.png)

DDL là ngôn ngữ định nghĩa dữ liệu. Các truy vấn DDL bao gồm:
- `CREATE` tạo một bảng, một View của bảng, hoặc đối tượng khác trong Database.
- `ALTER` sửa đổi một đối tượng Database đang tồn tại, ví dụ như một bảng.
- `DROP` xóa toàn bộ một bảng, một View của bảng hoặc đối tượng khác trong một Database.

DML là ngôn ngữ thao tác dữ liệu. Các truy vấn DML bao gồm:
- `SELECT` Lấy các bản ghi cụ thể từ một hoặc nhiều bảng.
- `INSERT` Tạo một bản ghi.
- `UPDATE` Sửa đổi các bản ghi đang tồn tại trong một bảng.
- `DELETE` Xóa các bản ghi.

DCL là ngôn ngữ điều khiển dữ liệu. Các truy vấn DCL bao gồm:
- `GRANT` Trao một quyền tới người dùng.
- `REVOKE` Thu hồi quyền đã trao cho người dùng.


# NoSQL
Trái lại với SQL, NoSQL là cơ sở dữ liệu dạng phân tán và không quan hệ với nhau.
Các dữ liệu được lưu duới nhiều dạng dữ liệu như biểu đồ, cặp khóa-giá trị,... Phù hợp với các cơ sở dữ liệu lớn, cần mở rộng nhanh nhưng không cần độ tin cậy.

Các hệ thống cơ sở dữ liệu NoSQL: MongoDB, Redis, Neo4j, Cassandra,...
