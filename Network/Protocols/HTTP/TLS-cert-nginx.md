# Cấu hình chứng chỉ TLS trên NGINX với Let’s Encrypt
Let’s Encrypt là phần mềm mã nguồn mở cung cấp mã hóa SSL/TLS miễn phí. Let’s Encrypt đóng vai trò tương tự như một Certificate Authority (CA) tự động.

Chứng chỉ số do Let’s Encrypt cấp được hầu hết các trình duyệt hiện nay tin cậy. Ngoài ra, Let’s Encrypt còn cung cấp khả năng tự động hóa việc cấp và gia hạn chứng chỉ.

### Cách thức hoạt động
- Trước khi cấp chứng chỉ, Let’s Encrypt cần xác thực quyền sở hữu tên miền.
- Let’s Encrypt trên server sẽ tạo một file tạm thời (token) với các thông tin bắt buộc trong đó.
- Sau đó, máy chủ xác thực Let’s Encrypt thực hiện một yêu cầu HTTP để truy xuất file và xác thực token, xác nhận bản ghi DNS nơi chứa tên miền.

### Điều kiện tiên quyết
Như vậy, để có thể sử dụng được Let’s Encrypt cần tuân theo những điều kiện tiên quyết sau:
- Phải sở hữu một tên miền đã được đăng ký
- Phải có bản ghi DNS, nơi chứa tên miền được phân giải
- Server đã được cài đặt NGINX

## Cấu hình
- #### 1. Cài đặt Let’s Encrypt client, certbot

      sudo apt-get install certbot
      apt-get install python3-certbot-nginx

- #### 2. Cấu hình NGINX
  - Tạo một file theo format `[domain‑name.conf]` trong thư mục `/etc/nginx/conf.d` (ví dụ www.example.com.conf)
  - Thêm vào những trường thông tin sau

        server {
          listen 80 default_server;
          listen [::]:80 default_server;
          root /var/www/html;
          example example.com www.example.com;
          
   - Trong đó `listen 80` là port được sử dụng (HTTP), `root` là nơi lưu website, `example` là tên server kèm theo tên miền
   - Lưu file và xác thực lại cấu hình
   
          nginx -t && nginx -s reload

- #### 3. Nhận chứng chỉ TLS
  - certbot có sẵn plug-in NGINX cho phép tái cầu hình hoặc làm mới bất cứ khi nào cần thiết
           
        sudo certbot --nginx -d example.com -d www.example.com
        
  - Sau khi nhập địa chỉ email và đồng ý với các điều khoản dịch vụ của Let’s Encrypt, quá trình tạo chứng chỉ hoàn tất
  - NGINX reload với các cài đặt mới. certbot tạo một thông báo cho biết đã tạo chứng chỉ thành công và đưa ra nơi lưu trữ của chứng chỉ trên server của người dùng.
        
        Congratulations! You have successfully enabled https://example.com and https://www.example.com 

        -------------------------------------------------------------------------------------
        IMPORTANT NOTES: 

        Congratulations! Your certificate and chain have been saved at: 
        /etc/letsencrypt/live/example.com/fullchain.pem 
        Your key file has been saved at: 
        /etc/letsencrypt/live/example.com//privkey.pem
        Your cert will expire on 2017-12-12.
        
- #### 4. Tự động gia hạn chứng chỉ
  - Chứng chỉ Let's Encrypt sẽ bị hết hạn trong 90 ngày, do vậy việc gia hạn nên được cài đặt tự động.
  - Sử dụng `crontab` và check vào mỗi 12h trưa hàng ngày.
         
        crontab -e
        0 12 * * * /usr/bin/certbot renew --quiet  
