#include <stdio.h>
#include <stdlib.h>

struct sinhvien{
    char ten[50];
    int id;
    float dtb;
};

int main(){
    struct sinhvien sv;
    FILE *fp1, *fp2;
    fp1= fopen("in.txt","r");
    fp2= fopen("out.txt","w");
    if (fp1 == NULL){
        printf("Error in opening the file!");
        exit(1);
    }

    while ((fscanf(fp1,"Ten: %s\t\tID: %d\tDiemTB: %f\n",sv.ten,&sv.id,&sv.dtb)) != EOF ){
        if ((sv.id > 30) && (sv.dtb >= 8 )){
            fprintf(fp2,"%s\t%d\t%.1f\n",sv.ten,sv.id,sv.dtb);
        }
    }
    fclose(fp1);
    return 0;
}


/*
in.txt
Ten: Binh     ID: 28  DiemTB: 8.23
Ten: Cuong    ID: 67  DiemTB: 7.55
Ten: Linh     ID: 13  DiemTB: 6.63
Ten: Khanh    ID: 57  DiemTB: 8.35
Ten: Hoang    ID: 69  DiemTB: 9.13

out.txt
Khanh	57	8.4
Hoang	69	9.1
*/


