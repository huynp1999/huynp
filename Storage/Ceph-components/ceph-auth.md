# Ceph authentication.
Client trong Ceph có thể hiểu là end-user, admin hoặc các service/daemon liên quan đến Ceph, ví dụ OSD, monitor hoặc Object Gateways. Và để xác định chính xác các loại client cũng như tránh khỏi can thiệp từ các bên thứ 3, Ceph cung cấp hệ thống xác thực tên `cephx` nhằm xác thực các user nằm trong hệ thống.

Xác thực mật mã sẽ yêu cầu tài nguyên cho việc tính toán, tuy nhiên ở mức độ thấp và không ảnh hưởng tới hiệu suất chung. Nếu môi trường kết nối mạng giữa client và server trong cluster đủ an toàn thì cũng có tùy chọn tắt cơ chế xác thực. Tuy nhiên việc này không được khuyến khích.

User yêu cầu ceph client liên hệ với một monitor.  Mỗi monitor đều có khả năng xác thực người dùng và phân phối key, do vậy không có "single point of failure" hoặc bottleneck khi sử dụng cephx. Monitor trả về một bộ dữ liệu xác thực gọi là ticket chứa session key để sử dụng các service của ceph. Session key được mã hóa với các tham số bí mật của user, do vậy chỉ có user đã được chỉ định mới có thể yêu cầu dịch vụ từ ceph monitor. Client sử dụng session key này để yêu cầu dịch vụ từ monitor, và monitor cung cấp cho user một ticket, ticket này sẽ xác thực người dùng để sử dụng osd. Ticket này giúp client có thể tương tác với bất kỳ osd hoặc mds. Ticket này có giới hạn thời gian.

Để sử dụng cephx, trước hết quản trị viên phải cấu hình các users. Theo hình dưới, user `client.admin` sẽ sử dụng lệnh `ceph auth get-or-create-key` để sinh ra username và khóa bí mật. Hệ thống sẽ sinh ra một username và khóa bí mật, lưu một bản sao lại cho mons và chuyển khóa bí mật lại cho user `client.admin`. Quá trình này mô tả client và mon chia sẻ khóa bí mật.	

![image](https://user-images.githubusercontent.com/83684068/129035406-35009cec-01e6-420a-9ce6-3522b4fe0237.png)

Để xác thực với các mon, người dùng cung cấp username cho mon, mon sẽ sinh ra một session key và mã hóa nó với khóa bí mật đã liên kết với tên người dùng. Sau đó mon sẽ gửi session key này lại cho người dùng. Sau đó người dùng sẽ giả mã bằng khóa chia sẻ đã nhận được từ bước trước. Session key này dùng để định danh người dùng ở phiên hiện tại. Sau đó người dùng sẽ yêu cầu một ticket đại diện cho người dùng được ký bởi session key. Monitor sinh ra một ticket, mã hóa nó với khóa bí mật của người dùng và chuyển nó lại cho người dùng. Người dùng giải mã ticket và dùng nó để ký lên yêu cầu gửi lên OSD và MDS.

![image](https://user-images.githubusercontent.com/83684068/129035522-d3b24d7c-a158-47a5-a5b6-b5394975c29c.png)


Giao thức xác thực cephx truyền thông giữa client và ceph server. Mỗi thông điệp được gửi giữa client và server được ký bởi ticket mà các monitor, OSD, MDS có thể xác thực bằng key chia sẻ:

![image](https://user-images.githubusercontent.com/83684068/129059709-595b5a64-4da3-4a21-a4b8-61c6fc4035be.png)

Toàn bộ quá trình được mô tả như sau:

![image](https://user-images.githubusercontent.com/83684068/129297598-d76fdb0c-04cd-4c8c-b309-1d83bfa50306.png)

Các bước thực hiện:
1. Một user muốn sử dụng dịch vụ lưu trữ ceph sẽ gửi một yêu cầu tạo user cho người quản trị
2. Admin của hệ thống ceph tứcclient.admin user, sử dụng lệnh để tạo user trên hệ thống.
3. Khi admin gọi lệnh tạo user, monitor sẽ tạo ra một secret key. Key này sẽ được monitor lưu lại, sau đó chuyển key này về cho admin và đồng thời chia sẻ cho các daemon trong hệ thống. Định dạng key có thể được kiểm tra ví dụ như

        # ceph auth get client.admin
        [client.admin]
                key = AQBFrwxhJuEiMxAACXVhyXj4G7y0zifxQp08XQ==
                
4. Admin nhận được key sẽ phải xuất ra dạng file để chuyển key này cho user (người yêu cầu sử dụng dịch vụ).
5. User sẽ sử dụng key được chia sẻ này để tương tác với hệ thống. User được sử dụng những quyền gì trong hệ thống sẽ do admin cấp phát.

## Các lệnh thao tác xác thực trên Ceph

Hiển thị toàn bộ các key authen của cụm Ceph

    # ceph auth list
    osd.0
            key: AQCirwxhIrc4FxAAuNSjOgf/lsQ8J86rNuEL5A==
            caps: [mgr] allow profile osd
            caps: [mon] allow profile osd
            caps: [osd] allow *
    osd.1
            key: AQCrrwxhny/nJRAABhyj2zmE3U1wJq3eenFWuw==
            caps: [mgr] allow profile osd
            caps: [mon] allow profile osd
            caps: [osd] allow *
    osd.2
            key: AQC2rwxhv9CcBhAAQhm23oohfluH5vGN1ShTEw==
            caps: [mgr] allow profile osd
            caps: [mon] allow profile osd
            caps: [osd] allow *
    ...
    ...
    client.admin
            key: AQBFrwxhJuEiMxAACXVhyXj4G7y0zifxQp08XQ==
            caps: [mds] allow *
            caps: [mgr] allow *
            caps: [mon] allow *
            caps: [osd] allow *
    ...
    ...
    client.rgw.ceph02
            key: AQBTswxh51F7EhAACmLxFHSIu9CvkUiMPh8WiQ==
            caps: [mon] allow rw
            caps: [osd] allow rwx
    mgr.ceph01
            key: AQDVsAxhUQGFJBAA4bUE65kS7XzfKd1pEIc8gw==
            caps: [mds] allow *
            caps: [mon] allow profile mgr
            caps: [osd] allow *

Tạo key 

    ceph auth get-or-create {key-name} mon {permission} osd {permission} mds {permission} > {key-name}.keyring

`caps` có thể hiểu là permission của key trên đối với từng service

Cập nhật permission key đã có sẵn

    ceph auth caps {key-name} mon {permission} osd {permission} mds {permission}

Xóa key
 
    ceph auth delete {key-name}
