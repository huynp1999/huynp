# NAT (Network Address Translation)
Là một kỹ thuật cho phép một hoặc nhiều địa chỉ IP nội miền chuyển đổi sang một hoặc nhiều địa chỉ IP ngoại miền.
 
NAT được thực hiện tại các Router hoặc Server biên, kết nối giữa 2 mạng.

![image](https://user-images.githubusercontent.com/83684068/120141004-db038c80-c205-11eb-86e9-c1ed5b7c2e96.png)

## Cơ chế hoạt động 
Khi gửi một gói tin từ nội miền ra ngoài, NAT sẽ thực hiện thay đổi địa chỉ [IP private](https://github.com/huynp1999/huynp/blob/master/Network/Basic/IPv4.md) (unregistered) thành IP public (registered) bên trong gói tin.
Tương tự, ngược lại đối với các gói tin từ ngoài vào trong mạng nội bộ.

- NAT cho phép người dùng bảo mật được thông tin IP máy tính, cũng như vừa tiết kiệm được số lượng IPv4 cần sử dụng.

- Cũng vì vậy mà NAT yêu cầu nhiều tài nguyên CPU làm tăng khả năng trễ trong quá trình switching, và cũng có thể gây ra lỗi với một số ứng dụng cần sử dụng IP

## Các khái niệm
