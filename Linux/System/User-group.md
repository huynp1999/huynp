# 1.User và group
Hệ điều hành Linux là hệ điều hành đa người dùng nên việc quản lý user và group là một phần quan trong trong việc quản lý hệ thống nói chung.

Group là tập hợp của nhiều user, được tạo ra nhằm mục đính hỗ trợ [phân quyền](https://github.com/huynp1999/huynp/blob/master/Linux/Filesystem/File-permissions.md) và tránh rủi ro vận hành. Mỗi user trên linux bắt buộc phải thuộc một nhóm chính (primary group) và có thể là nhiều nhóm phụ khác (secondary group).
### 1.1 Quản lý
Mỗi user được gắn cho một UID riêng, bắt đầu từ 1000 trở lên. Tại mỗi user lại nắm giữ nhiều ID của các nhóm đang tham gia.

Danh sách user: `/etc/passwd`
Danh sách group: `/etc/group`
### 1.2 Tạo và xoá
- **User**
  - Tạo: `useradd [username]`  và đặt mặt khẩu `passwd [username]`
  - Xoá: `userdel [username]`

- **Group**
  - Tạo: `groupadd [groupname]`
  - Xoá: `groupdel [groupname]`

Thêm user vào group:
- Tạo mới và thêm: `useradd -a -G newgroup username`
- Có sẵn và thêm: `usermod -a -G newgroup username1`

# 2. Root user
- Lệnh su 

Su là một công cụ chuyển đổi người dùng (switch user)

Cú pháp: `su [username]`

Mặc định nếu không ghi username sẽ tự hiểu là chuyển sang root, 

- Lệnh sudo

Sudo là một cơ chế quản lý quyền, phụ thuộc vào `/etc/sudoers` mà xác định user nào được phép thực hiện loại lệnh quản lý nào.
Mặc định, chỉ người dùng root mới có thể thực thi lệnh sudo. Người dùng root cần chỉnh sửa file cấu hình `/etc/sudoers` để cho phép những user thường khác thực thi lệnh sudo.


### So sánh
Vậy `su` và `sudo` giống nhau về cách mượn quyền root để thực thi.

Tuy nhiên `su` sẽ chuyển hoàn toàn sang root user dẫn tới nhiều rủi ro về tính bảo mật và ổn định của hệ thống do người dùng toàn quyền quyết định. Cấp đặc quyền bằng `sudo` sẽ ít nguy hiểm và được ưu tiên hơn.

