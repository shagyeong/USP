#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    //파일을 읽어 다른 파일에 쓰기
    int rfd, wfd, n;
    char buf[10];

    rfd = open("test.txt", O_RDONLY);
    if(rfd == -1){
        perror("test.txt");
        exit(1);
    }

    wfd = open("test.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(wfd == -1){
        perror("test.bak");
        exit(1);
    }

    while((n = read(rfd, buf, 5)) != 0){
        if(write(wfd, buf, n) != n){
            perror("write");
        }
    }

    if(n == -1){
        perror("read");
    }

    close(rfd);
    close(wfd);

    exit(0);
}