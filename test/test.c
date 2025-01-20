#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    off_t start;
    char buf[10]; int n;
    int rfd; int rflags = O_RDONLY;
    int wfd; int wflags = O_CREAT | O_WRONLY;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    rfd = open("./test.txt", rflags);
    wfd = open("./test.bak", wflags, mode);
    //파일을 처음부터 끝까지 읽기
    printf("current offset: %d\n", (int)lseek(rfd, 0, SEEK_CUR));
    while((n = read(rfd, buf, 5)) > 0){
        printf("%s", buf);
    }
    printf("current offset: %d\n", (int)lseek(rfd, 0, SEEK_CUR));
    //특정 위치로 이동후 파일 읽기
    start = lseek(rfd, 6, SEEK_SET); //6번째로 이동해 'System'의 'S'부터 읽음
    while((n = read(rfd, buf, 5)) > 0){
        write(wfd, buf, n);
    }
    close(rfd);
    close(wfd);
}