#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char a, fname[50], path[50] = "/home/huynp/C/fileio2/test.txt";
    printf("File name: ");
    fgets(fname, 50, stdin);
    fp = fopen(fname,"w");
    
    if (!fp){
        printf("error");
        exit(1);
    }
    
    printf("Create file succesfully, enter some text:\n");
    while (a != '$') {
        a= getchar();
        fputc(a,fp);
    }
    fclose(fp);

}

/*
Tham số truyền vào là tên file hoặc đường dẫn file

huynp@huyComputer:~/C/fileio2$ ./main.o
File name: /home/huynp/C/fileio2/test.txt
Create file succesfully, enter some text:
Hello World!!!
123 456
$

Text được ghi tại đầu ra

test.txt
Hello World!!!
Test
$
*/
