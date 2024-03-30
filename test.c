#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    
    stat("linux.txt", &statbuf);
    printf("mode = %o\n", (unsigned int)statbuf.st_mode);

    if((statbuf.st_mode & __S_IREAD) != 0)
        printf("rusr\n");
    if((statbuf.st_mode & __S_IREAD >> 3) != 0)
        printf("rgrp\n");
    if((statbuf.st_mode & __S_IREAD >> 6) != 0)
        printf("roth\n");
}