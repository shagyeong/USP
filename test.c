#include<sys/errno.h>
#include<unistd.h>
#include<stdio.h>

extern int errno;

int main(void){
    if(access("linuxxxx.txt", F_OK) == -1 && errno == ENOENT)
        printf("file not exitst\n");

    if(access("linux.txt", R_OK) == 0)
        printf("read permission is permitted\n");
    else if(access("linux.txt", R_OK) == -1 && errno == EACCES)
        printf("read permission is not permitted\n");
}