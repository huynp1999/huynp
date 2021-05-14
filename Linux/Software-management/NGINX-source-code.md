# Install from source code
Trong nhiều trường hợp, các package có thể sẽ không tương thích hoặc không có sẵn, vậy để cài đặt được phần mềm cần phải làm việc với source code của nó. Cài đặt từ source code cũng cho phép
custom và chỉnh sửa các tính năng, phiên bản tùy chọn theo người dùng.

# NGINX server
Là một phần mềm web server mã nguồn mở. Ban đầu được dùng để phục vụ web HTTP, bây giờ cũng được dùng làm reverse proxy, HTTP load balancer và email proxy như IMAP, POP3, và SMTP.

NGINX quản lý những threads tương đồng nhau trong một tiến trình (process), mỗi tiến trình hoạt động lại chứa các thực thể nhỏ hơn gọi là worker connections.
Mỗi một worker connection có thể xử lý 1024 yêu cầu tương tự nhau, nhờ vậy mà NGINX có khả năng xử lý hàng ngàn kết nối cùng lúc.

# Cài đặt NGINX từ source code
Bởi NGINX được viết từ C nên cần phải cài đặt trình biên dịch C:
- `sudo apt install -y build-essential git tree`

Tải về source code của NGINX và giải nén:
- `wget https://nginx.org/download/nginx-1.19.2.tar.gz && tar zxvf nginx-1.19.2.tar.gz`

Thư viện dành cho những module:
1. PCRE version 8.44
- `wget https://ftp.pcre.org/pub/pcre/pcre-8.44.tar.gz && tar xzvf pcre-8.44.tar.gz`

2. zlib version 1.2.11
- `wget https://www.zlib.net/zlib-1.2.11.tar.gz && tar xzvf zlib-1.2.11.tar.gz`

3. OpenSSL version 1.1.1g
- `wget https://www.openssl.org/source/openssl-1.1.1g.tar.gz && tar xzvf openssl-1.1.1g.tar.gz`

Cài đặt các tùy chọn:
- `sudo apt install -y perl libperl-dev libgd3 libgd-dev libgeoip1 libgeoip-dev geoip-bin libxml2 libxml2-dev libxslt1.1 libxslt1-dev`
Thư viện dành cho những module:
1. PCRE version 8.44
- `wget https://ftp.pcre.org/pub/pcre/pcre-8.44.tar.gz && tar xzvf pcre-8.44.tar.gz`

2. zlib version 1.2.11
- `wget https://www.zlib.net/zlib-1.2.11.tar.gz && tar xzvf zlib-1.2.11.tar.gz`

3. OpenSSL version 1.1.1g
- `wget https://www.openssl.org/source/openssl-1.1.1g.tar.gz && tar xzvf openssl-1.1.1g.tar.gz`

Cài đặt các tùy chọn:
- `sudo apt install -y perl libperl-dev libgd3 libgd-dev libgeoip1 libgeoip-dev geoip-bin libxml2 libxml2-dev libxslt1.1 libxslt1-dev`

Copy **man**ual vào thư mục /usr/share/man/man8/:
- ```
sudo cp ~/nginx-1.19.2/man/nginx.8 /usr/share/man/man8
sudo gzip /usr/share/man/man8/nginx.8
```
Kiểm tra hoạt động của manual
- ```
ls /usr/share/man/man8/ | grep nginx.8.gz
man nginx
```

Cấu hình, biên dịch và cài đặt:
```
./configure --prefix=/etc/nginx \
            --sbin-path=/usr/sbin/nginx \
            --modules-path=/usr/lib/nginx/modules \
            --conf-path=/etc/nginx/nginx.conf \
            --error-log-path=/var/log/nginx/error.log \
            --pid-path=/var/run/nginx.pid \
            --lock-path=/var/run/nginx.lock \
            --user=nginx \
            --group=nginx \
            --build=Ubuntu \
            --builddir=nginx-1.19.2 \
            --with-select_module \
            --with-poll_module \
            --with-threads \
            --with-file-aio \
            --with-http_ssl_module \
            --with-http_v2_module \
            --with-http_realip_module \
            --with-http_addition_module \
            --with-http_xslt_module=dynamic \
            --with-http_image_filter_module=dynamic \
            --with-http_geoip_module=dynamic \
            --with-http_sub_module \
            --with-http_dav_module \
            --with-http_flv_module \
            --with-http_mp4_module \
            --with-http_gunzip_module \
            --with-http_gzip_static_module \
            --with-http_auth_request_module \
            --with-http_random_index_module \
            --with-http_secure_link_module \
            --with-http_degradation_module \
            --with-http_slice_module \
            --with-http_stub_status_module \
            --with-http_perl_module=dynamic \
            --with-perl_modules_path=/usr/share/perl/5.26.1 \
            --with-perl=/usr/bin/perl \
            --http-log-path=/var/log/nginx/access.log \
            --http-client-body-temp-path=/var/cache/nginx/client_temp \
            --http-proxy-temp-path=/var/cache/nginx/proxy_temp \
            --http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
            --http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
            --http-scgi-temp-path=/var/cache/nginx/scgi_temp \
            --with-mail=dynamic \
            --with-mail_ssl_module \
            --with-stream=dynamic \
            --with-stream_ssl_module \
            --with-stream_realip_module \
            --with-stream_geoip_module=dynamic \
            --with-stream_ssl_preread_module \
            --with-compat \
            --with-pcre=../pcre-8.44 \
            --with-pcre-jit \
            --with-zlib=../zlib-1.2.11 \
            --with-openssl=../openssl-1.1.1g \
            --with-openssl-opt=no-nextprotoneg \
            --with-debug

make
sudo make install
```

Liên kết `/usr/lib/nginx/modules` tới thư mục chuẩn của các nginx module `/etc/nginx/modules`:
- `sudo ln -s /usr/lib/nginx/modules /etc/nginx/modules`

Tạo group và user, kiểm tra:
- ```
sudo adduser --system --home /nonexistent --shell /bin/false --no-create-home --disabled-login --disabled-password --gecos "nginx user" --group nginx
sudo tail -n 1 /etc/passwd /etc/group /etc/shadow
```

Kiểm tra phiên bản và các lỗi nếu xảy ra:
```
sudo nginx -V
sudo nginx -t
```

Tạo file .service dành cho systemd với nội dung:
```
[Unit]
Description=nginx - high performance web server
Documentation=https://nginx.org/en/docs/
After=network-online.target remote-fs.target nss-lookup.target
Wants=network-online.target

[Service]
Type=forking
PIDFile=/var/run/nginx.pid
ExecStartPre=/usr/sbin/nginx -t -c /etc/nginx/nginx.conf
ExecStart=/usr/sbin/nginx -c /etc/nginx/nginx.conf
ExecReload=/bin/kill -s HUP $MAINPID
ExecStop=/bin/kill -s TERM $MAINPID

[Install]
WantedBy=multi-user.target
```

Khởi động nginx mỗi khi boot:
- ```
sudo systemctl enable nginx.service
sudo systemctl start nginx.service
```

