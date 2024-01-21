#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(mkdir("dir1", 0755) == -1){
        exit(1);
    }
    if(mkdir("dir2", 0755) == -1){
        exit(1);
    }

    if(rename("dir2", "hanbit")){
        exit(1);
    }

    exit(0);
}