#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    stat("linux.txt", &statbuf);

    printf("inode = %d\n", (int)statbuf.st_ino);
    printf("mode = %d\n", (unsigned int)statbuf.st_mode);
    printf("nlink = %d\n", (unsigned int)statbuf.st_nlink);
    printf("uid = %d\n", (int)statbuf.st_uid);
    printf("gid = %d\n", (int)statbuf.st_gid);
    printf("size = %d\n", (int)statbuf.st_size);
    printf("blksize = %d\n", (int)statbuf.st_blksize);
    printf("blocks = %d\n", (int)statbuf.st_blocks);
}