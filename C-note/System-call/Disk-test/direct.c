#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/timeb.h>

#define MEGABYTE 1024*1024

int main(int argc, char * argv[]){
    long megabytes,i, buf_size;
    int fo, ret;
    struct timeb start,end;
    unsigned char *buf;

    fo = open(argv[1], O_WRONLY | O_DIRECT | O_CREAT, 0755);
    megabytes = atol(argv[2]); //lay dung luong file
    buf_size = atol(argv[3]); //lay buffer size file

    // cap phat vung nho cho buffer + 512 la can chinh vi tri bat dau
    ret = posix_memalign((void **)&buf, 512, buf_size); 
    memset(buf, 'A', buf_size); //tao du lieu tren buffer de sau day vao file
    
    ftime(&start);

    for (i=0; i < ((MEGABYTE*megabytes)/buf_size); i++) //ghi buffer vao fo theo megabytes lan
        write(fo, buf, buf_size); //ghi tu buffer vao disk

    ftime(&end);
    long write_time=end.time-start.time; //tinh thoi gian ghi theo giay

    if (write_time > 0)
        printf("Write rate: %ld MB/s\nExecute time: %ld s\n", megabytes/write_time, write_time );

    free(buf);
    close(fo);
    return 0;
}

