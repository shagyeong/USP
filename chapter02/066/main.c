/* 066 : 디렉터리 생성하기 */
#include<stdio.h>
#include<stdlib.h> /* mkdir*/
#include<sys/stat.h> /* mkdir*/
#include<unistd.h> /* rmdir */

int main(void){
    /* 0755 : 111 101 101 rwx r-x r-x  소유자 그룹 공개 */
    
    /*
    if(mkdir("testdir", 0755) == -1){
        perror("testdir");
        exit(1);
    }
    */

    if(rmdir("testdir") == -1){
        perror("testdir");
        exit(1);
    }

    exit(0);
}
