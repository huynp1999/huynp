# DNS (Domain Name System)
Hệ thống phân giải tên miền là một hệ thống chuyển đổi các tên miền website sang một địa chỉ IP dạng số tương ứng với tên miền đó và ngược lại.

Về chức năng, DNS có thể được hiểu như một “phiên dịch viên”, khi người dùng đăng nhập vào một website, thay vì phải nhớ và nhập một dãy số địa chỉ IP của hosting, thì chỉ cần nhập tên website là trình duyệt tự động nhận diện.

## 4 loại server tham gia vào trong hệ thống phân giải tên miền

- **DNS Recursive resolver**
  - Điểm dừng đầu tiên trong quá trình truy vấn DNS và là cầu nối trung gian giữa client và các DNS nameserver
  - Nếu không có trong cache, nó sẽ cần hỏi đến root nameserver
- **Root Nameserver**
  - Là DNS server quan trọng nhất trong hệ thống cấp bậc của DNS.
  - Khi nhận được yêu cầu từ DNS recursive resolver, server này sẽ đưa ra các các top-level domain name servers (TLD nameserver) cụ thể chịu trách nhiệm quản lý.
- **TLD Nameserver**
  - Chịu trách nhiệm quản lý toàn bộ thông tin của một phần mở rộng tên miền chung, ví dụ như .com, .org, .net
- **Authoritative Nameserver**
  - Là nơi chính thức chứa thông tin tên miền gắn với địa chỉ nào. Nó sẽ trả lại recursive resolver địa chỉ IP cần thiết tìm thấy trong danh mục các bản ghi của nó.

## Ví dụ về nuyên tắc hoạt động
![Alt](https://news.cloud365.vn/wp-content/uploads/2020/02/6a4a49_50da300f2194485f99e844f2b47d96f3mv2.png)

- Trước hết, chương trình trên máy người dùng gửi yêu cầu tìm kiếm địa chỉ IP ứng với tên miền beta.example.com tới local DNS server thuộc mạng của nó.
- DNS local này kiểm tra trong cơ sở dữ liệu, nếu có nó sẽ gửi trả lại địa chỉ IP của máy có tên miền nói trên.
- Nếu không, local DNS sẽ hỏi lên các máy chủ tên miền ở mức cao nhất (Root DNS). Root DNS sẽ gửi cho local địa chỉ của DNS quản lý các tên miền có đuôi .com.
- Từ đây, máy chủ tên miền quản lý các tên miền .com sẽ trả lại địa chỉ của máy chủ quản lý tên miền example.com.
- Local DNS tiếp tục hỏi máy chủ quản lý tên miền example.com này và nhận địa chỉ IP của tên miền beta.example.com.
- Local DNS chuyển thông tin tìm được đến máy của người dùng.
- Người dùng sử dụng địa chỉ IP này để kết nối đến server chứa trang web có địa chỉ beta.example.com.

## Các loại bản ghi
- **SOA**
   + `Start of Authority records`: thông tin về vùng DNS: name server chính, email người quản trị tên miền, số seri tên miền, chu kỳ update,...
- **A**
   + `Address Mapping Records`: ánh xạ 1 `domain name` thành 1 địa chỉ Ipv4.
- **AAAA**
   + `IP Version 6 Address records`: ánh xạ 1 `domain name` thành địa chỉ IPv6
- **NS**
   + `Name Server records`: Lưu thông tin về name server
   + Định danh cho 1 máy chủ có thẩm quyền về 1 zone nào đó.
- **CNAME**
   + `Canonical Name records`: chỉ định các tên miền phụ
   + Ví dụ như www.example.com là tên miền phụ của exmaple.com
- **HINFO**
   + `Host infomation records`: thu thập thông tin tổng quát về máy chủ
   + Ghi loại CPU và hệ điều hành
- **PTR**
   + `Reverse-lookup Pointer records`: ngược lại với bản ghi A, truy vấn tên miền dựa trên địa chỉ IP
- **MX**
   + `Mail exchanger record`: MX chỉ định 1 máy chủ trao đổi thư cho 1 tên miền DNS.
   + Sử dụng bởi giao thức SMTP để định tuyến email đến máy chủ thích hợp
