#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


int main(void){
    int fd;
    fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd == -1){
        perror("create");
        exit(1);
    }

    //1번(표준 출력)으로 tmp.bbb 기술자를 복사하여 출력 방향 전환
    dup2(fd, 1);
    printf("dup2 : standard output redirection\n");

    close(fd);
    exit(1);
}