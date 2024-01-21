/* 디렉터리의 내용을 읽는 위치 변경하기(telldir(3), seekdir(3), rewind(3)) */
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(void){
    DIR* dp;
    struct dirent* dent;
    long loc;

    dp = opendir(".");

    printf("initial position : %ld\n", telldir(dp));
    while(dent = readdir(dp)){
        printf("read : %s -> ", (*dent).d_name);
        printf("current position : %ld\n", telldir(dp));
    }

    printf("** directory position rewind **\n");
    rewinddir(dp);
    printf("current position : %ld\n", telldir(dp));

    printf("** move directory pointer **\n");
    readdir(dp);
    loc = telldir(dp);
    seekdir(dp, loc);
    printf("current position : %ld\n", telldir(dp));

    dent = readdir(dp);
    printf("read : %s \n", (*dent).d_name);

    closedir(dp);

    exit(0);
}

/*
DIR* dp = opendir(".");
long loc = telldir(dp);
*/