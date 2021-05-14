# Quyền và sở hữu
Trong mô hình bảo mật của Unix, một user sở hữu file và thư mục có thể quản lý quyền access đối với chúng. 
Do tính đa người dùng, một user cũng có thể thuộc về một group nào đó gồm nhiều user khác. Với nhiều người dùng, tính an toàn của hệ thống sẽ là điều đáng quan ngại nếu như không được quản lý đúng cách.
Để tăng tính hiệu quả trong bảo mật, linux chia ủy quyền thành 2 lớp:
- Ownership (chủ sở hữu)
- Permission (quyền)

## Ownership
Mỗi file hay thư mục trên Linux đều được gán bởi 3 loại chủ sở hữu là user, group, other.

### User
Theo như mặc định trên Linux thì người tạo ra file hay thư mục nào đó thì sẽ trở thành chủ sở hữu (owner) của chính nó.

### Group
Một nhóm có thể chứa nhiều user cùng một lúc. Tất cả người dùng trong một nhóm sẽ có cùng quyền truy cập vào file hay thư mục đó.
- Ví dụ có một tài liệu học tập cho một lớp học mà bạn không muốn cho lớp khác biết, chỉ muốn chia sẻ trong lớp.
Thay vì bạn cấp quyền cho từng người trong lớp thì bạn có thể gom tất những người trong lớp thành một nhóm và gán quyền cho nhóm người dùng đó
Như vậy chỉ có nhóm đó nghĩa là những người trong lớp có quyền truy cập vào file, các lớp khác tức là ngoài nhóm không có quyền.

### Other
Bất kỳ user nào không thuộc vào 2 đối tượng phía trên.
- Xét với ví dụ trên, các bạn lớp khác chính là thuộc nhóm Other bởi không thuộc trong nhóm hay sở hữu tài liệu nào cả

## Permission
Là công cụ để Linux phân biệt 3 loại người dùng trên.

Trong đó, mỗi một file hay thư mục trong Linux đều có 3 quyền đọc, ghi, thực thi được xác định cho 3 chủ sở hữu ở trên.
- **Đọc**: nếu là một file thì quyền này cho phép user mở file và đọc. Nếu là một thư mục thì nó cho phép user liệt kê danh sách file hay thư mục trong đó
- **Ghi**: user không có quyền ghi sẽ không thể sửa đổi nội dung đối với file, và không thể thêm, xóa và đổi tên các file đối với thư mục
- **Thực thi**: user không có quyền thực thi sẽ không thể chạy file hoặc truy cập (cd) vào thư mục

##
Để xem permission của một file: `ls -l`



Trong đó:
- `d` = directory
- `r` = read permission
- `w` = write permission
- `x` = execute permission
- `-` = no permission 

![Alt](https://www.guru99.com/images/permission(1).png)

# Phân quyền
Khi không muốn cho nhóm người dùng truy cập file nữa, sử dụng `chmod` (change mode):

Cú pháp: `chmod [permissions] [filename]`

Các option được chia thành 2 cách:
## Cách 1 (số)
Cách quyền sẽ được đại diện bằng số theo bảng sau:

| Số            | Quyền                  | Ký tự |
| :------------:| -----------------------|-------|
| 1             | No permission          | ---   |
| 2             | Execute                | --x   |
| 3             | Execute + Write        | -w-   |
| 4             | Read                   | r--   |
| 5             | Read + Execute         | r-x   |
| 6             | Read + Write           | rw-   |
| 7             | Read + Write + Execute | rwx   |

Ví dụ với `chmod 764` sẽ lần lượt cấp 7 cho user, 6 cho group và 4 cho other.

## Cách 2 (ký tự)
Các ký tự toán học:
- `+` thêm quyền
- `-` xóa quyền
- `=` phân quyền và ghi đè lên lần phân quyền trước

Các chủ sở hữu được đại diện bởi:
- `u` 	user/owner
- `g` 	group
- `o` 	other
- `a` 	all 

Ví dụ với `chmod u=rw-` thì quyền w của user sẽ mất do bị ghi đè.

# Thay đổi quyền sở hữu và group
Khi cần thay đổi quyền sở hữu của một file hoặc thư mục: `chmod [username] [filename]`

Thay đổi quyền sở hữu của user và group: `chown [user:group] [filename]`

Thay đổi quyền của group: `chgrp [groupname] [filename]`
