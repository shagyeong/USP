#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(rmdir("dir01") == -1){
        perror("dir01");
        exit(1);
    }
    exit(0);
}