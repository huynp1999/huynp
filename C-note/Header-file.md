Header file trong C có đuôi `.h` dùng để giữ tất cả các hằng số, các macro, các biến toàn cục để có thể include sử dụng ở bất kỳ đâu. Header file giúp source code dễ bảo trì, update, và tối ưu hóa chương trình.
Có hai loại file header:
- File có sẵn trong compiler, khai báo `#include <.h>`
  - `stdio.h` thư viện nhập xuất chuẩn
  - `math.h` thư viện định nghĩa các hàm toán học
  - `string.h` thư viện làm việc với chuỗi
  - `stdlib.h` thư viện liên quan tới cấp phát bộ nhớ động 
  - ...
- File tự viết, khai báo `#include ".h"`


Ví dụ có `header.h`, trong đó cho declaration sau:

    void write(char *str);
   
Tại file định nghĩa:

    #include "header.h"
    #include <stdio.h>
    
    void write(char *str);{
        printf("%s",str);
    }
    
Các chương trình khác chỉ cần khai báo header file `header.h` và sử dụng `write()` khi được đặt trong cùng folder

    #include "header.h"

    int main(){
        write("Hello!");
    }

Lý do là khi include header, compiler sẽ mang nội dung của header file thế chỗ vào `#include` và trở thành như một function thông thường.
