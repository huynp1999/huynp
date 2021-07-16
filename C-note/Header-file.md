# Header file
Header file trong C có đuôi `.h` dùng để giữ tất cả các hằng số, các macro, các biến toàn cục để có thể include sử dụng ở bất kỳ đâu. Header file giúp source code dễ bảo trì, update, và tối ưu hóa chương trình.

Có hai loại file header:
- File có sẵn trong compiler, khai báo `#include <.h>`
  - `stdio.h` thư viện nhập xuất chuẩn
  - `math.h` thư viện định nghĩa các hàm toán học
  - `string.h` thư viện làm việc với chuỗi
  - `stdlib.h` thư viện liên quan tới cấp phát bộ nhớ động 
  - ...
- File tự viết, khai báo `#include ".h"`

## Lợi ích
Khi code source yêu cầu gọi một function, compiler bắt buộc phải biết trước function đó là gì. Như vậy prototype được khai báo trong header file giống như một bảng hướng dẫn sử dụng trước khi dùng function cho máy tính.

Như vậy, compiler sẽ hiểu được cách sử dụng tất cả các function ngay từ khi bắt đầu chạy chương trình. Điều này giúp lập trình viên ít bận tâm hơn về việc đặt **thứ tự** các function trong các files `.c`. Khi có càng nhiều function thì sự tiện lợi từ prototype càng tăng.

Ví dụ có `header.h`, trong đó là macro và declaration sau:
    
    void write(char *str);
   
Tại file định nghĩa:

    #include "header.h"
    #include <stdio.h>
    
    void write(char *str);{
        printf("%s",str);
    }
    
Các chương trình khác muốn sử dụng hàm write() chỉ cần khai báo `header.h`, miễn là header file có sẵn trong project folder hoặc trong libary folder của compiler. (`/usr/include` với gcc trên Linux, hoặc `\MinGW\include` với MinGW trên Windows)

    #include "header.h"

    int main(){
        write("Hello!");
    }

Lý do là khi include header, compiler sẽ mang nội dung của header file thế chỗ vào `#include` và trở thành như một function thông thường.
