#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd1, fd2, n;
    char buf[50];
    fd1= open("in.txt", O_RDONLY | O_CREAT); //nếu không có sẵn file thì tự tạo

    if (fd1 < 0){ // nếu mở (đóng) không thành công, file descriptor (fd) return -1
        perror("Error: ");
        exit(1);
    }
    n= read (fd1, buf, 20); //lấy 20 byte từ mảng buf và return lại n

    fd2= open("out.txt",O_WRONLY | O_CREAT);
    write(fd2, buf, n); //ghi 20 byte data từ mảng buf vào file descriptor
    close(fd1);
    close(fd2);
}


