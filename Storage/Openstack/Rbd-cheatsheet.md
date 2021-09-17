# Công cụ rbd
Công cụ rbd được dùng để thao tác với image của RBD ([Rados Block Device](https://github.com/huynp1999/huynp/blob/master/Storage/Ceph-components/ceph-rbd.md)).
RBD image về cơ bản là một block device tương tự như ổ cứng, cdrom,... Image này sẽ được tách (striped) thành nhiều object và lưu được lưu phân tán trong RADOS cluster.

## Các thao tác với RBD image
Tạo một image mới có dung lượng 100GB, từ một pool:
    
    rbd create mypool/myimage --size 102400
Xoá image:

    rbd rm mypool/myimage
List image của một pool:

    rbd ls -p mypool
    
### 1. Thao tác với image snapshot     
Tạo snapshot của một image:

    rbd snap create mypool/myimage@mysnap
List snapshot của một image:
 
    rbd snap ls mypool/myimage
Phục hồi image từ snapshot:    
    
    rbd snap rollback mypool/myimage@mysnap
Xoá một snapshot của một image:

    rbd snap rm mypool/myimage@mysnap
Xoá toàn bộ snapshot của một image:

    rbd snap purge mypool/myimage
### 2. Thao tác với trash
Thay vì xoá hẳn thì có thể xoá tạm thời volume/image vào thùng rác:
    
    rbd trash mv mypool/myimage
Lấy danh sách các image đã bị xoá:

    $ rbd trash ls mypool
    36c371d5245c1 myimage
Khôi phục volume từ thùng rác (option `--image` nếu muốn rename image):

    rbd trash restore mypool/36c371d5245c1 --image restoreimage

### 3. RBD layering
Tính năng layering trong RBD cho phép tạo nhiều copy-on-write clone (CoW) của một block device snapshot.
Layering được sử dụng như trong trường hợp cần clone snapshot của một image thuộc một VM, và ta sẽ không muốn snapshot gốc bị ảnh hưởng mà chỉ thao tác trên clone của nó.
Lúc này snapshot của VM gốc sẽ là `parent`, còn snapshot được clone cho instance mới sẽ gọi là `child`.

![image](https://user-images.githubusercontent.com/83684068/133724015-01978e74-7420-4dde-9e58-adb9293c1c2c.png)

Parent snapshot luôn luôn là `read-only`, một mặt để tránh ảnh hưởng từ các clone của nó, mặt khác lại có thể giúp việc cloning nhanh chóng hơn.
Nhìn từ phía người dùng, child snapshot sẽ không khác gì một rbd image thông thường mà có thể snapshot, đọc/ghi, resize,...

Tính năng layering có thể được bật khi tạo một image mới:

    rbd snap create mypool/myimage --image-feature layering

Image cần được bật bảo vệ trước khi thực hiện clone:

    rbd snap protect mypool/myimage@mysnap
Tiến hành clone `myimage` cho `childimage1` thông qua snapshot `mysnap`

    rbd clone mypool/myimage@mysnap mypool2/childimage1
List các child của snapshot

    rbd children mypool/myimage@mysnap
Muốn xoá một parent snapshot, cần gỡ (`flatten`) hoặc xoá (`rm`) các child ra khỏi nó trước :

    $ rbd snap unprotect mypool/myimage@mysnap
    Cannot unprotect: Still in use by mypool2/childimage2
    $ rbd children mypool/myimage@mysnap
    mypool2/childimage1
    mypool2/childimage2
    $ rbd flatten mypool2/childimage1
    $ rbd rm mypool2/childimage2
    $ rbd snap rm mypool/myimage@mysnap
    Cannot remove a protected snapshot: pool/image@snap
    $ rbd snap unprotect mypool/myimage@mysnap
    $ rbd snap rm mypool/myimage@mysnap

### 4. Striping
Như đã biết, một rbd image sẽ được phân tán ra khắp RADOS cluster, vậy nên các request đọc/ghi tới image cũng được chuyển tới nhiều node trong cluster.
Điều này có thể gây ra rủi ro nghẽn cổ chai đối với các image lớn và có lượng truy xuất cao.

Striping có thể được điều chỉnh nhờ các option khi tạo một image mới:
- `--object-size`: chỉ định size của object khi chia (mặc định 4MB, min 4K, max 32M)
- `--stripe_unit`: số byte được ghi liền kề của một object, trước khi chuyển sang object tiếp theo (default stripe_unit = object-size)
