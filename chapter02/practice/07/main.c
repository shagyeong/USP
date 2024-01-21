#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    if(rmdir("test") == -1){
        perror("test");
        exit(1);
    }

    exit(0);
}