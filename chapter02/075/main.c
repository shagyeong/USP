/* 디렉터리 이동 2(fchdir(2)) */
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    char* cwd;
    int fd;

    cwd = getcwd(NULL, BUFSIZ);
    printf("current working directory : %s\n", cwd);

    fd = open("test", O_RDONLY); /* open()은 디렉터리를 열고 파일 디스크립터를 리턴한다 */
    fchdir(fd);

    cwd = getcwd(NULL, BUFSIZ);
    printf("current working directory : %s\n", cwd);

    close(fd);
    free(cwd);

    exit(0);
}