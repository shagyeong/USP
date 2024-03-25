#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(void){
    DIR* dp;
    struct dirent* dent;
    long loc;

    dp = opendir(".");
    printf("start position : %ld\n", telldir(dp));

    while(dent = readdir(dp)){
        printf("read : %s -> ", (*dent).d_name);
        printf("current position : %ld\n", telldir(dp));
    }

    rewinddir(dp);
    printf("rewinded position : %ld\n", telldir(dp));

    /*항목 한 개를 읽은 후 오프셋의 위치*/
    readdir(dp);
    loc = telldir(dp);
    seekdir(dp, loc);
    printf("current position : %ld\n", telldir(dp));

    dent = readdir(dp);
    printf("read : %s\n", (*dent).d_name);

    closedir(dp);
}