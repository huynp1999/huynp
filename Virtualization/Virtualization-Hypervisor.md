# Virtualization
Hay còn gọi là ảo hóa, là một công nghệ được nằm ở tầng trung gian giữa hệ thống phần cứng máy tính và phần mềm chạy trên nó.
Cho phép sử dụng tối đa công suất của ổ cứng hoặc một máy tính vật lý bằng cách phân phối cho nhiều người dùng hoặc nhiều môi trường độc lập.

Ví dụ:
- Có 3 server vật lý riêng biệt với những chức năng riêng của nó là: mail server, web server và các lagacy app nội bộ
- Tuy nhiên mỗi server chỉ dùng 30% công suất của chúng

![image](https://user-images.githubusercontent.com/83684068/122864278-878ce600-d34e-11eb-8cb2-e337e45ce756.png)

- Với ảo hóa, có thể tách mail server thành 2 phần riêng biệt với chức năng khác nhau
- Thậm chí, mailserver vẫn có thể tách được lần nữa để tận dụng tối đa tài nguyên sẵn có, từ 60% lên đến 90%

![image](https://user-images.githubusercontent.com/83684068/122864482-ebafaa00-d34e-11eb-8f77-6cd22d4f5e8a.png)

- Như vậy sẽ giảm được chi phí về phần cứng, chi phí bảo trì và làm mát cho các hệ thống server

## 1. Mục tiêu chính của ảo hóa
- **Availability:** giúp các ứng dụng hoạt động liên tục bằng cách giảm thiểu, loại bỏ downtime khi gặp sự cố
- **Scalability:** khả năng tùy biến, thu hẹp hoặc mở rộng mô hình server dễ dàng mà không làm gián đoạn ứng dụng
- **Optimization:** sử dụng triệt để nguồn tài nguyên phần cứng và tránh lãng phí 
- **Management:** khả năng quản lý tập trung thuận tiện

## 2. Thành phần chính của ảo hóa
Một hệ thống ảo hóa bắt buộc phải có đầy đủ các thành phần: tài nguyên vật lý, phần mềm ảo hóa, máy chủ ảo và hệ điều hành khách.

![](https://raw.githubusercontent.com/khanhnt99/CCNA-LINUX-tips/master/Untitled%20Diagram.png)

- **Tài nguyên vật lý chính (Host machine/Host hardwave)**
  - Là các nguyên như CPU, RAM, ổ đĩa cứng, card mạng… được phân chia cho các máy ảo.
- **Phần mềm ảo hóa (Hypervisor)**
  - Cung cấp truy cập cho mỗi máy chủ ảo đến tài nguyên của máy chủ vật lý.
  - Lập kế hoạch và phân chia tài nguyên vật lý cho các máy chủ ảo.
  - Cung cấp giao diện quản lý cho các máy chủ ảo.
- **Hệ điều hành khách (Guest Operating System)**
  - Được cài đặt trên một máy chủ ảo, thao tác như ở trên hệ điều hành thông thường.
- **Mảy ảo (Virtual Machine)**
  - Hoạt động như một máy chủ vật lý thông thường với tài nguyên riêng, giao diện riêng, hệ điều hành riêng.

## 3. Ring
Hierarchial Protection Domains (Protection Rings) là cơ chế nhằm bảo vệ dữ liệu và chức năng của 1 chương trình tránh khỏi nguy cơ lỗi hoặc bị truy cập trái phép.

<img src="https://user-images.githubusercontent.com/83684068/123500359-bc0ee380-d667-11eb-8f5c-9a68e10e95ad.png" alt="drawing" width="450"/>

Mỗi một vòng ring tương đương với một quyền hạn (level) để truy cập tài nguyên hệ thống. Như vậy, ring 0 có đặc quyền cao nhất, tương tác trực tiếp với phần cứng CPU, Memory,...

## 4. Phân loại ảo hóa
- RAM virtualization
- CPU virtualization
- Network virtualization
- Device I/O virtualization
## 5. Các mức độ ảo hóa trong CPU virtualization
Một số chỉ thị của guest OS ở ring 3 (user level) phải được thực hiện trong ring 0. Để làm được như vậy, yêu cầu các chỉ thị phải được translate xuống hardware ngay khi hệ thống đang hoạt động. Các giải pháp được đưa ra nhằm giải quyết vấn đề này gồm: Full virtualization sử dụng binary translation, hardware assist virtualization và paravirtualization.
### 5.1 Ảo hóa toàn phần (full virtualization)
Các chỉ thị trên guest OS sẽ không bị biến đổi mà được dịch nhị phân ở virtualization layer (ring 0). Bằng cách này Guest OS hoàn toàn không nhận ra nó đang nằm trên một lớp ảo hóa.

Tuy nhiên, ảo hóa toàn phần có thể gặp một số vấn đề về hiệu năng và hiệu quả trong sử dụng tài nguyên hệ thống.

![image](https://user-images.githubusercontent.com/83684068/123499875-f2e2fa80-d663-11eb-828b-8260c0fd02a8.png)

### 5.2 Ảo hóa song song (Paravirtualization)
Trong phương pháp này, hypervisor sẽ cung cấp hypercall interface. Guest OS sẽ được chỉnh sửa kernel code để thay thế các chỉ thị bằng các hypercall này. Do kernel code của guest OS phải chỉnh sửa nên giải pháp này không thể sử dụng được một số hệ điều hành mã nguồn đóng như windows. Và do guest OS sử dụng hypercall nên sẽ biết mình đang nằm trên một virtualization layer.

![image](https://user-images.githubusercontent.com/83684068/123500638-c6ca7800-d669-11eb-87ae-4886cfaa6eb9.png)

### 5.3 Hardware Assisted Virtualization
Phương pháp này đều hướng đến việc xây dựng một CPU mode mới dành riêng cho virtualization layer gọi là root mode (ring -1). Bằng cách này, các chỉ thị từ guest OS sẽ được tự động đi xuyên qua virtualization layer và cũng không cần kỹ thuật dịch nhị phân vì guest OS đã nằm ở ring 0

![image](https://user-images.githubusercontent.com/83684068/123500723-3e98a280-d66a-11eb-83c0-af4a1da8adf5.png)

# Hypervisor
Là một chương trình phần mềm quản lý một hoặc nhiều máy ảo (VM). Hypervisor được sử dụng để tương tác với các máy ảo và giới hạn số lượng tài nguyên hệ thống cho mỗi máy ảo sử dụng.
Các hypervisor cho phép mỗi VM hoặc guest OS giao tiếp với lớp tài nguyên phần cứng vật lý bên dưới, chẳng hạn như CPU, RAM và ổ cứng.

## 1. Phân loại Hypervisor

![image](https://user-images.githubusercontent.com/83684068/123501638-a225ce80-d670-11eb-80f9-93ea94a08dc1.png)

### 1.1 Native Hypervisor (Bare metal)
Hypervisor ở dạng native sẽ chạy trực tiếp trên phần cứng. Nó nằm giữa phần cứng và một hoặc nhiều guest OS.
Nó được khởi động trước cả hệ điều hành và tương tác trực tiếp với kernel.

Điều này mang lại hiệu suất cao nhất có thể vì không có host OS chạy song song nào cạnh tranh tài nguyên máy tính với nó.
Tuy nhiên, cũng đồng nghĩa với việc hệ thống chỉ có thể chạy các máy ảo vì hypervisor luôn chạy ngầm bên dưới.

### 1.2 Hosted Hypervisor
Hypervisor dạng hosted được cài đặt trên một host OS chủ.
Hoạt động như một phần mềm thông thường trên máy tính. Hầu hết các hosted hypervisor có thể quản lý và chạy nhiều máy ảo cùng một lúc.

Lợi thế của một hosted hypervisor là có thể được bật, tạm dừng hoặc thoát ra khi cần thiết, giải phóng tài nguyên cho máy chủ.
Tuy nhiên, vì hoạt động thông qua một hệ điều hành trung gian nên hiệu suất đem lại có thể không bằng một native hypervisor.
