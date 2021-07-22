#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/timeb.h>

#define MEGABYTE (1024*1024)

int main(int argc, char * argv[]){
    long megabytes,i, buf_size;
    int fo, ret;
    struct timeb start,end;
    unsigned char *buf;

    fo = open(argv[1], O_WRONLY | O_DIRECT | O_CREAT, 0755);
    buf_size = atol(argv[2]); //lay buffer size file

    // cap phat vung nho cho buffer + 512 la can chinh vi tri bat dau
    ret = posix_memalign((void **)&buf, 512, buf_size); 
    memset(buf, 'A', buf_size); //tao du lieu tren buffer de sau day vao file
    
    ftime(&start);

    ret= write(fo,buf,buf_size); //ghi du lieu tu buffer vao file

    ftime(&end);

    float write_time=end.time-start.time; //tinh thoi gian ghi theo giay
    if (write_time < 1)
        printf("Write rate: %.2f KB/s\n\nExecute time: < 0 \n", buf_size/1000.0);
    else
        printf ("Write rate: %.2f MB/s\nExecute time: %.2f s\n", (ret/MEGABYTE)/write_time, write_time);

    free(buf);
    close(fo);
    return 0;
}
