#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char buf[256] = "hello world\n";
    int fd; int flags = O_WRONLY;
    fd = open("./test.txt", flags);
    write(fd, buf, 256);
    
    flags = fcntl(fd, F_GETFL);
    flags |= O_APPEND;
    fcntl(fd, F_SETFL, flags);
    
    write(fd, buf, 256);
    close(fd);
}