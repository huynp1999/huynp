## Thao tác với file
Ngôn ngữ C hỗ trợ đọc và ghi dữ liệu từ các tập tin. Những file này được lưu trong ổ cứng của hệ thống máy tính: như vậy dữ liệu sẽ được lưu lại cố định ngay cả sau khi dừng chương trình hoặc tắt máy tính. Từ các file này có thể thao tác bình thường với con trỏ, cấu trúc, chuỗi, ký tự,... Làm việc với file cho phép lưu trữ và copy dễ dàng, nhất là đối với những tập dữ liệu lớn.

## Luồng dữ liệu
Luồng dữ liệu (stream) là thành phần trung gian nối giữa ứng dụng và nguồn dữ liệu (file, network, v.v.). Stream giúp thống nhất, ổn định, tăng hiệu quả và đơn giản hơn trong việc đọc/ghi dữ liệu với các loại nguồn.

![image](https://user-images.githubusercontent.com/83684068/125764541-95da91e5-efec-4933-9b10-dd0be41f7be6.png)

Các luồng tiêu chuẩn là các kênh giao tiếp vào ra được kết nối trước giữa chương trình máy tính và môi trường của nó khi chương trình bắt đầu thực thi. Ba kết nối vào/ra (I/O) được gọi là đầu vào tiêu chuẩn (stdin), đầu ra tiêu chuẩn (stdout) và lỗi tiêu chuẩn (stderr).

Các hàm xử lý file trong thư viện C:

| Hàm | Mô tả |
| ------------- |:-------------|
| fopen()      | Mở hoặc tạo file nếu không có sẵn   |
| fprintf()      |  Ghi tập dữ liệu vào file    |
| fscanf()      |  Đọc tập dữ liệu vào file  |
|  fputc()     |  Ghi một ký tự vào file   |
|  fgetc()     |  Đọc một ký tự từ file   |
|    fclose()   |  Đóng file đã được mở |
|   fseek()    |  Chỉ định vị trí con trỏ file |
|   rewind()    |  Đặt con trỏ file vào đầu tiên |

## Các thao tác cơ bản
Khai báo một file con trỏ dùng để trỏ đến kiểu FILE. Đồng thời trỏ đến nhiều thông tin khác nhau về file, bao gồm tên, trạng thái và vị trí hiện tại. Về bản chất, con trỏ file xác định một file cụ thể và đưa ra các chỉ thị hoạt động cho các chức năng I/O. Để đọc hoặc ghi file, chương trình cần sử dụng con trỏ file:

    FILE *fptr;
    
## fopen
Trước khi có thể đọc hoặc ghi một file từ disk, hàm fopen() gọi open() system call để mở file:

    fptr = fopen("path/filename","mode");
    
Hàm fopen() mở ra một luồng tới file để sử dụng nó và trả lại con trỏ file. Con trỏ này có thể bị ngắt liên kết tới file nhờ fclose() hoặc freopen() (tái sử dụng lại luồng để mở file mới hoặc mode mới). `path/filename` là một con trỏ tới chuỗi ký tự filename hoặc đường dẫn hợp lệ. 

**Các mode thao tác với file** dựa trên những tag của open() system call như O_RDONLY, O_WRONLY, O_WRONLY, O_APPEND, O_CREATE,...
| Mode  | Mô tả |
| --- |------|
|   r  |  Mở file để đọc    |
|   w |  Mở file để ghi từ đầu, sẽ tạo nếu file không có sẵn. Con trỏ file sẽ xuất phát từ đầu file |
|  a   |  Mở file để ghi tiếp vào cuối, sẽ tạo nếu file không có sẵn. Con trỏ file sẽ xuất phát ở cuối file   |
|  r+ |  Mở file để đọc và ghi    |
|  w+   |  Tạo hoặc mở file để đọc và ghi  |
|   a+  |  Tạo hoặc mở file để đọc và ghi vào cuối. Nếu đọc thì sẽ bắt đầu từ đầu, còn ghi sẽ được thêm vào cuối   |
|   rb, wb, ab  |  Chức năng tương tự, nhưng dùng cho mở binary file   |

Tuy nhiên, trong quá trình mở file, fopen có thể xảy ra fail như dung lượng không đủ để tạo tệp mới, disk được bảo vệ chống ghi hoặc bị hỏng, v.v. Để đảm bảo file được mở thành công

    FILE *fp;
    fp = fopen("file.C","r");
    if(fp == NULL){
      printf("Error in opening file!");
      exit();
    }


## fclose
Có một giới hạn về số lượng file được mở cùng lúc, và phải đóng trước khi muốn mở một file khác. Điều này được thực hiện bằng hàm fclose(). Hàm fclose() gọi close() syscall để đóng một luồng liên kết tới file mà đã được mở bằng fopen. Sau đó sẽ đẩy (flush) bất kỳ dữ liệu nào vẫn còn trong bộ đệm vào disk, và giải phóng tất cả memory được dùng cho file.

    fclose(fptr);
    
Hàm `fclose()` trả về 0 khi thực thi thành công hoặc EOF nếu có lỗi khi đóng file. EOF là một hằng số được định nghĩa trong header file stdio.h.

## fscanf
Hàm fscanf() được sử dụng để đọc tập các ký tự từ file. Nó đọc input đã được định dạng từ một stream và trả về EOF (End of File) ở vị trí kết thúc file.
Hàm scanf() đọc từ luồng đầu vào chuẩn stdin, còn fscanf() sẽ đọc đầu vào từ con trỏ luồng.

Khi thành công, hàm trả về một số bằng với số lượng các đối tượng đã được đọc thành công. Nếu ít hơn hoặc không khớp là do lỗi trong quá tình đọc hoặc do phạm vi
của *end-of-file*

    fscanf(f, "%s %s", s1, s2) == 2

Nếu lỗi đọc xảy ra hoặc gặp EOF trong quá trình đọc, thì EOF sẽ được trả về.

## fprintf
Hàm fprintf() được sử dụng để ghi tập các ký tự vào file. Nó gửi dữ liệu output được định dạng tới một stream.
Khác với hàm printf() ghi đầu ra vào luồng đầu ra chuẩn stdout.

    
    fprintf(fp, "Hello World!!");

- `fp` là con trỏ tới một đối tượng FILE để nhận dạng luồng (stream) đầu dùng cho việc đọc dữ liệu
- `!Hello World!!"` chuỗi text để ghi vào luồng

## feof
Phát hiện chỉ thị *End-of-File* đã được đưa tới luồng chưa, nếu có thì trả về một giá trị khác 0.
    
    while(!feof(f)){
        fscanf(f,"%s %s",s1,s2);
        printf("%s %s\n",s1,s2);
    }

## fgetc, fputc
Hàm fgetc() đọc ký tự từ stream đã cho và tăng vị trí chỉ định cho Stream đó.
Hàm này trả về ký tự được đọc dưới dạng một unsigned char được ép kiểu thành một int hoặc EOF hoặc lỗi.

Hàm fputc() ghi một ký tự đã được xác định bởi tham số char tới Stream đã cho, và tăng vị trí chỉ định cho Stream.
Nếu lỗi xuất hiện, EOF được trả về và chỉ thị Error được thiết lập.

## fseek
Hàm fseek() thiết lập vị trí con trỏ file của Stream tới một whence (vị trí) đã cho cộng thêm offset (nếu có). Tham số offset tính số byte bắt đầu từ vị trí whence đã cho.

    int fseek(FILE *stream, long int offset, int whence);
    
Các flag whence cho biết nơi bắt đầu tính offset:
|  Flag | M |
| --- |:------|
|  SEEK_SET	   |   Phần đầu file   |
|  SEEK_CUR   |   Vị trí hiện tại của con trỏ file  |
|   SEEK_END  |  Phần cuối file    |

## rewind
Hàm rewind() trong thiết lập vị trí file tại phần đầu của file trong stream đã cho. Hàm này có chức năng tương tự với flag SEEK_SET của fseek().

## fread/fwrite
Đọc một mảng các `count` phần tử từ `stream`, mỗi phần tử có kích thước là `size` byte, và lưu trữ chúng trong khối bộ nhớ được chỉ định bởi `ptr`. Như vậy, tổng lượng byte nếu được đọc thành công là (size*count).

    size_t fread (void * ptr, size_t size, size_t count, FILE * stream);

Tương tự đối với fwrite(), chỉ khác là ghi từ `ptr` xuống vị trí hiện tải của `stream`.

