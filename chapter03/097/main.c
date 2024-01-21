/* 파일 기술자로 파일 정보 검색(fstat(2)) */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd;
    struct stat statbuf;

    if((fd = open("test.txt", O_RDONLY)) == -1){
        perror("open: test.txt");
        exit(1);
    }

    fstat(fd, &statbuf);

    printf("inode = %d\n", (int)statbuf.st_ino);
    close(fd);

    exit(0);
}