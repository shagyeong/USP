/* 디렉터리명 변경(rename(2)) */
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(rename("test", "renamed") == -1){
        perror("rename");
        exit(1);
    }

    exit(0);
}