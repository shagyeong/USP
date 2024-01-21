#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

extern int errno;

void strerrortest(void){
    char* err;
    if(access("test.txt", R_OK) == -1){
        printf("strerrortest\n");
        err = strerror(errno);
        printf("%s\n", err);
    }
}