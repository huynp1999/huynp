# Các thuật toán mã hóa
Mã hóa là một công nghệ hoạt động bằng cách xáo trộn dữ liệu, nhằm tránh khỏi các bên ngoài ý muốn đọc được.

Có nhiều loại thuật toán mã hóa tuy nhiên chúng đều dựa trên 2 phương pháp chủ yếu là:
- Mã hóa khóa đối xứng (symmetric encryption)
- Mã hóa khóa bất đối xứng (asymmetric encryption)

Mỗi hệ thống mã hóa có ưu nhược điểm riêng. Trong các ứng dụng mã hóa hiện tại, người ta thường kết hợp các ưu điểm của cả hai loại mã hóa này. 
## Mã hóa đối xứng
Mã hóa đối xứng sử dụng cùng một khóa để mã hóa/giải mã.
- Cơ chế xử lý nhanh nhưng độ an toàn không cao
- Cần ít sức mạnh tính toán
- Ít tiêu tốn tài nguyên mạng
- Phù hợp với những dữ liệu lớn

### Triple DES (Triple Data Encryption Standard)
- Triple DES sử dụng ba khóa mã hoá riêng lẻ với 56 bit mỗi khóa. Tổng độ dài khóa lên tới 168 bit, tăng đáng kể bảo mật so với DES.
- Tuy nhiên đã dần bị loại bỏ khi thuật toán AES được phát triển.
### Twofish
- Khoá có độ dài lên đến 256 bit
- Một nửa bit của khóa được sử dụng làm khóa mã hóa thực và nửa còn lại được sử dụng để tuỳ chỉnh thuật toán mã hóa
- Sử dụng miễn phí, nhưng không được đặt làm tiêu chuẩn và yếu thế hơn AES
### AES (Advanced Encryption Standard)
- Được nhiều tổ chức đặt làm tiêu chuẩn và sử dụng rộng rãi nhất hiện nay.
- Hoạt động hiệu quả ở dạng 128 bit, cũng có loại khoá khác như 192 và 256 bit cho các tác vụ lớn.
- AES được cho là có thể tất cả các cuộc tấn công, ngoại trừ tấn công vét cạn (brute force).
- Bản rõ trước tiên được chuyển thành các khối, và mã hóa được áp dụng cho từng khối. Quá trình mã hóa bao gồm các quá trình con khác nhau như byte con, dịch chuyển hàng, trộn cột và thêm khóa tròn
## Mã hóa bất đối xứng
Trong khi đó, mã hóa bất đối xứng sử dụng nhiều khóa để mã hóa và giải mã dữ liệu. Quy trình mã hoá bao gồm hai khóa mã hóa riêng biệt có liên quan đến nhau về mặt toán học, gọi là “khóa công khai” và khóa còn lại là “khóa bí mật”.
- Yêu cầu tính toán nhiều và xử lý chậm hơn
- Độ an toàn và tính thuân tiện trong quản lý khóa cao.

### Ứng dụng
Alice và Bob cung cấp nhiều khóa công khai cho mọi người và giữ một khóa bí mật duy nhất cho bản thân.

2 phương thức ứng dụng:
- **Bảo mật**: Alice chỉ muốn gửi cho đúng người nhận là Bob, mà không phải là ai khác
  - Alice sử dụng khoá công khai của Bob để mã hoá, Bob nhận được bản mã và sẽ chỉ có Bob sử dụng được khoá bí mật của mình để giải mã.

- **Xác thực**: Bob muốn xác thực đây là bản mã được tạo ra bởi Alice, mà không phải của ai khác
  - Alice sử dụng khoá bí mật của mình để mã hoá, như vậy chỉ có Alice mới có thể tạo ra bản mã đó và Bob có thể sử dụng khoá công khai của Alice để xác thực điều này.

### RSA
