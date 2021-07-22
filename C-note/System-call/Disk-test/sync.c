#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/timeb.h>
#include <string.h>

#define MEGABYTE (1024*1024)

int main(int argc, char * argv[]){
    long i, buf_size;
    int fo, ret;
    // unsigned char *buf;
    char *buf;
    struct timeb start,end;

    ftime(&start);

    fo = open(argv[1], O_CREAT | O_WRONLY | O_SYNC);
    buf_size=atof(argv[2]);
    buf= (char *) malloc (buf_size); //cap phat bo nho buffer dua tren dung luong file
    
    for(i=0; i < buf_size; i++)
        memset(buf, rand(), 1); //ghi du lieu vao buffer de sau day vao file

    ret= write(fo,buf,buf_size); //ghi du lieu tu buffer vao file
    //fs
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
