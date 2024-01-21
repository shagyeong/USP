/* 디렉터리 열기, 닫기, 내용 읽기(opendir(3), closedir(3), readdir(3)) */
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(void){
    DIR* dp = opendir(".");
    struct dirent* dent;

    while((dent = readdir(dp))){
        printf("name : %s ", (*dent).d_name);
        printf("inode : %d\n", (int)(*dent).d_ino);
    }

    closedir(dp);
    exit(0);
}

/*
opendir() : 인자로 지정된 디렉터리를 열고 디렉터리 스트림을 생성, 그 포인터를 리턴
closedir() : 닫으려는 디렉터리의 디렉터리 스트림 포인터를 인자로 받음
*/