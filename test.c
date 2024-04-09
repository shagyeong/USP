#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    
    chmod("linuxt.txt", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
    stat("linux.txt", &statbuf);

    printf("mode = %o\n", (unsigned int)statbuf.st_mode);

    statbuf.st_mode |= S_IWGRP;
    statbuf.st_mode &= ~(S_IROTH);
    chmod("linux.txt", statbuf.st_mode);
    stat("linux.txt", &statbuf);

    printf("mode = %o\n", (unsigned int)statbuf.st_mode);
}