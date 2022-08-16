#include<stdio.h>
#include<stdlib.h>

#define BUFF 17
#define ERR 01

void usage(void);
void hexdump(void);

char* commandname;
FILE* fp;

void main(int argc, char* argv[]){
    while(*++argv){
        fp = fopen(*argv, "r");

        printf("%s\n", *argv);
        hexdump();
        fclose(fp);
    }

    exit(0);
}


void hexdump(void){
    int fd;
    unsigned int address;
    int count;
    unsigned char buffer[BUFF];
    int iter;

    fd = fp->_fileno;

    for(address = 0; (count = read(fd, buffer, 16)) > 0; address += count){
        printf("%08x ", address);

        for(iter = 0; iter < count; iter++){
            printf("%02x ", buffer[iter]&0xff);
        }

        printf("\n");
    }

    printf("\n");
}