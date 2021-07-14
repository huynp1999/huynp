Tệp header trong C có đuôi `.h` dùng để giữ tất cả các hằng số, các macro, các biến toàn cục để có thể include sử dụng ở bất kỳ đâu.
Có hai loại file header:
- File có sẵn trong compiler, khai báo `#include <.h>`
  - `stdio.h` thư viện nhập xuất chuẩn
  - `math.h` thư viện định nghĩa các hàm toán học
  - `string.h` thư viện làm việc với chuỗi
  - ...
- File tự viết, khai báo `#include ".h"`


Ví dụ có `header.h` sau:

    void write(char *str){
        printf("%s",str);
    }
    
Các chương trình khác chỉ cần gọi và sử dụng `write()` thông qua

    #include "header.h"
    #include <stdio.h>

    int main(){
        write("hello");
    }

