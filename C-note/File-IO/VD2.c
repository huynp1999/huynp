#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char a, fname[50];
    printf("File name: ");
    fgets(fname, 50, stdin);
    fp = fopen(fname,"w");

    printf("Create file succesfully, enter some text:\n");
    while (a != '$') {
        a= getchar();
        fputc(a,fp);
    }
    fclose(fp);

}

/*
huynp@huyComputer:~/C/fileio2$ gcc main.c -o main.o
huynp@huyComputer:~/C/fileio2$ ./main.o 
File name: test.txt
Create file succesfully, enter some text:
Hello World!!!
Test
$

test.txt
Hello World!!!
Test
$
*/
