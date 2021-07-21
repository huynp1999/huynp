#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/timeb.h>
#include <string.h>

#define MEGABYTE (1024*1024)

int main(int argc, char * argv[]){
    long megabytes, i, buf_size;
    int fo;
    char buffer[buf_size];
    struct timeb start,end;
    
    memset(buffer, 'A', buf_size);

    fo = open(argv[1], O_CREAT | O_WRONLY | O_SYNC);
    megabytes=atol(argv[2]); //lay dung luong file
    buf_size=atol(argv[3]);
    ftime(&start);

    for (i=0; i < ((MEGABYTE/buf_size)*megabytes); i++) //ghi buffer vao fo theo megabytes lan
        write(fo,buffer,buf_size); //ghi tu buffer vao disk

    ftime(&end);
    long write_time=end.time-start.time; //tinh thoi gian ghi theo giay

    if (write_time > 0)
        printf("Write rate: %ld MB/s\nExecute time: %ld s\n", megabytes/write_time, write_time );

    close(fo);
    return 0;
}
