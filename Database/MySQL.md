# MySQL
MySQL là một hệ thống quản trị cơ sở dữ liệu quan hệ (RDBMS) mã nguồn mở và hoạt động theo mô hình client-server.
MySQL quản lý dữ liệu thông qua các bảng quan hệ chứa dữ liệu.
MySQL có cùng một cách truy xuất và mã lệnh tương tự với ngôn ngữ SQL.

## Cài đặt, cấu hình và truy vấn

Cài đặt:
    
    sudo apt install mysql-server
Mở MySQL:

    sudo mysql
Hoặc nếu đã đặt password cho root:

    sudo mysql -u root -p
    
**Thao tác với user**
- Tạo người dùng mới:

      CREATE USER 'huy'@'localhost' IDENTIFIED BY 'password';
    
  - Với `huy` và `password` là tên người dùng và mật khẩu
  - `localhost` là vị trí tạo user, ở đây có nghĩa là tạo nội bộ
- Xóa người dùng:
    
      DROP USER 'username'@'localhost';
- List user:

      SELECT user,authentication_string,plugin,host FROM mysql.user;
      
      +------------------+-------------------------------------------+-----------------------+-----------+
      | user             | authentication_string                     | plugin                | host      |
      +------------------+-------------------------------------------+-----------------------+-----------+
      | root             | *8FA5DF56B884163592F52AC60C5B60641D1FD0CB | mysql_native_password | localhost |
      | mysql.session    | *THISISNOTAVALIDPASSWORDTHATCANBEUSEDHERE | mysql_native_password | localhost |
      | mysql.sys        | *THISISNOTAVALIDPASSWORDTHATCANBEUSEDHERE | mysql_native_password | localhost |
      | debian-sys-maint | *B26DE0662ADEFE863A8813F074A50BD296422F73 | mysql_native_password | localhost |
      | huy              | *196BDEDE2AE4F84CA44C47D54D78478C7E2BD7B7 | mysql_native_password | localhost |
      +------------------+-------------------------------------------+-----------------------+-----------+
      5 rows in set (0,00 sec)
**Thao tác với database**
- List database:

      show databases;
      
      +--------------------+
      | Database           |
      +--------------------+
      | information_schema |
      | abcdxyz            |
      | mysql              |
      | performance_schema |
      | sys                |
      +--------------------+
      5 rows in set (0,06 sec)
- Tạo database mới

      CREATE DATABASE IF NOT EXISTS test123;

- Xóa database

      DELETE DATABASE IF EXISTS abcdxyz;
      show databases;
      
      +--------------------+
      | Database           |
      +--------------------+
      | information_schema |
      | mysql              |
      | performance_schema |
      | sys                |
      | test123            |
      +--------------------+
      5 rows in set (0,00 sec)
      
- Cấp quyền cho user `huy` truy cập vào database `test123`

       GRANT ALL PRIVILEGES ON test123.* TO 'huy'@'localhost';
       
  - Thay vì `ALL` có thể tùy chọn từng loại query mà user có thể thực hiện trong database, ví dụ như `SELECT,INSERT,UPDATE,...`
  - Có thể thay `test123` bằng `*`, tương ứng với việc cấp quyền cho user truy cập vào tất cả các database

