# Glance
Image service (code-name Glance) cung cấp dịch vụ dành cho người dùng tải lên và truy xuất các vào kho dữ liệu, nơi mà được sử dụng với các dịch vụ khác.
Trong đó sẽ bao gồm *image* và *metadata*.

## Image
Glance bao gồm các dịch vụ về lưu trũ, đăng ký và truy xuất image của máy ảo (VM).
Glance sử dụng RESTful API cho phép truy vấn metadata của VM image tương tự như truy xuất một image.

VM image được tạo từ Glance có thể được lưu trữ ở nhiều kiểu lưu trữ khác nhau, từ filesystem, tới object storage (Swift) và block storage (Cinder).
