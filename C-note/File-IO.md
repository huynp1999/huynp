Khi chương trình kết thúc thì toàn bộ dữ liệu sẽ bị mất, làm việc với file cho phép lưu trữ và copy dễ dàng, nhất là đối với những tập dữ liệu lớn.

#### Các thao tác cơ bản
Khai báo con trỏ kiểu FILE và mở file
    
    FILE *fptr;
    fptr = fopen("directory","mode");

Các mode 
| Mode  | Mô tả |
| --- |:------:|
|   r  |  đọc    |
|   w |  ghi    |
|  a   |  ghi vào cuối file    |
|  r+/w+ |  ghi và đọc    |

Các hàm xử lý file trong thư viện C:

| Hàm | Mô tả |
| ------------- |:-------------:|
| fopen()      | right foo     |
| fprintf()      | right bar     |
| fscanf()      | right baz     |
|  fputc()     |  ghi một ký tự vào file   |
|  fgetc()     |  đọc một ký tự từ file   |
|    fclose()   |    đóng file |
|   fseek()    |  chỉ định vị trí con trỏ tập tin   |
|   rewind()    |  đặt con trỏ tập tin vào đầu tập tin   |


