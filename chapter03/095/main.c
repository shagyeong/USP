/* 095 : 파일명으로 inode 정보 검색하기(stat(2)) */
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;

    stat("test.txt", &statbuf);

    printf("Inode = %d\n", (int)statbuf.st_ino);
    printf("Mode = %o\n", (unsigned int)statbuf.st_mode);
    printf("Nlink = %o\n", (unsigned int)statbuf.st_nlink);
    printf("UID = %d\n", (int)statbuf.st_uid);
    printf("GID = %d\n", (int)statbuf.st_gid);
    printf("SIZE = %d\n", (int)statbuf.st_size);
    printf("Blocks = %d\n", (int)statbuf.st_blocks);

    printf("Atime = %d\n", (int)statbuf.st_atim.tv_sec);
    printf("Mtime = %d\n", (int)statbuf.st_mtim.tv_sec);
    printf("Ctime = %d\n", (int)statbuf.st_ctim.tv_sec);

    printf("Atime = %d\n", (int)statbuf.st_atime);
    printf("Mtime = %d\n", (int)statbuf.st_mtime);
    printf("Ctime = %d\n", (int)statbuf.st_ctime);
}