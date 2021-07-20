#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/timeb.h>

#define BUFFERSIZE (60000)
#define MEGABYTE (1024*1024)

int main(int argc, char * argv[]){
    long megabytes,i;
    int fo;
    char buffer[BUFFERSIZE];
    struct timeb start,end;
    
    for (i=0; i < BUFFERSIZE ; i++)
        buffer[i]='A'; //tao du lieu tren buffer de sau day vao file

    fo = open(argv[1], O_CREAT | O_WRONLY | O_SYNC);
    megabytes=atol(argv[2]); //lay dung luong file
    ftime(&start);

    for (i=0; i < ((MEGABYTE/BUFFERSIZE)*megabytes); i++) //ghi buffer vao fo theo megabytes lan
        write(fo,buffer,BUFFERSIZE); //ghi tu buffer vao disk

    ftime(&end);
    long write_time=end.time-start.time; //tinh thoi gian ghi theo giay

    if (write_time > 0)
        printf("Write rate: %ld MB/s\nExecute time: %ld s\n", megabytes/write_time, write_time );

    close(fo);
    return 0;
}


/*
Đầu vào là filename và dung lượng file (200MB)

./a.out /home/huynp/C/systemcall/benchmark/test 200
Write rate: 2MB/s
Execute time: 106s

Tốc độ thấp hơn nhiều khi test bằng tiện ích fio (?)

WRITE: bw=21.9MiB/s (22.9MB/s), 21.9MiB/s-21.9MiB/s (22.9MB/s-22.9MB/s), io=200MiB (210MB), run=9146-9146msec

*/
