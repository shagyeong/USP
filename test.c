#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    link("linux.txt", "linux.ln");
    symlink("linux.txt", "linux.sym");
    struct stat statbuf;

    stat("linux.ln", &statbuf);
    printf("link count : %d\n", (int)statbuf.st_nlink);

    unlink("linux.ln");
    stat("linux.txt", &statbuf);
    printf("link count : %d\n", (int)statbuf.st_nlink);

    unlink("linux.sym");
}