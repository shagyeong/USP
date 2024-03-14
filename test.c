#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    char* cwd;
    int fd;

    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd = %s\n", cwd);

    fd = open("dir01", O_RDONLY);
    fchdir(fd);

    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd = %s\n", cwd);

    close(fd);
    free(cwd);
}