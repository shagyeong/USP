#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd, n;
    off_t init, curr;
    char buf[256];

    fd = open("test.txt", O_RDONLY);
    
    init = lseek(fd, 0, SEEK_CUR);
    n = read(fd, buf, 255);
    buf[n] = '\0';

    
}