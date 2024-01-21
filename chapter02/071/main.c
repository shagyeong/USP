/* 현재 작업 디렉터리의 위치 검색 2(get_current_dir_name(3)) */
#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* cwd;

    cwd = get_current_dir_name();
    printf("cwd = %s\n", cwd);
    free(cwd);

    return 0;
}