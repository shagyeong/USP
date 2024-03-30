#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    int kind;
    stat("linux.txt", &statbuf);

    printf("mode = %d\n", (unsigned int)statbuf.st_mode);
    
    if(S_ISLNK(statbuf.st_mode))
        printf("LNK\n");
    if(S_ISDIR(statbuf.st_mode))
        printf("DIR\n");
    if(S_ISREG(statbuf.st_mode))
        printf("REG\n");
}