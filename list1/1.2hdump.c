#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFFERSIZE 16
#define ERR -1

void hexdump(FILE* fp);

void main(int argc, char* argv[]){
    FILE* fp1 = fopen(argv[1], "r");

    hexdump(fp1);

    exit(0);
}

void hexdump(FILE* fp){
    int fd; //파일 디스크립터
    unsigned int address; //바이트 수(주소)
    int count; //읽어들일 바이트 수
    unsigned char buffer[BUFFERSIZE]; //버퍼

    fd = fileno(fp);
    address = 0;
    count = read(fd, buffer, BUFFERSIZE);

    while(count > 0){
        printf("%08x", address);

        for(int i = 0; i < count; i++){
            printf(" %02x", buffer[i]);
        }

        printf(" ");

        for(int i = 0; i < count; i++){
            printf("%c", buffer[i]);
        }

        printf("\n");


        //반복문 증감식
        count = read(fd, buffer, BUFFERSIZE);
        address += count;
    }


    
}

/*1
2
3
4







*/
/*
#include<stdio.h>
#include<stdlib.h>

#define BUFF 18
#define ERR -1
void usage(void);
char* command_name;
FILE* fpin;

void main(int argc, char* argv[]){
    
    char* rindex(const char* s, int c);
    void hexdump(void);

    if((command_name = rindex(*argv, '/')) != NULL)
        command_name++;
    else
        command_name = *argv;

    if(argc < 2)
        usage();

    while(*++argv){
        if((fpin = fopen(*argv, "r")) == NULL){
            fprintf(stderr, "*ERROR : Can't open input file %s.\n", *argv);
            continue;
        }
        printf("%s ; \n", *argv);
        hexdump();
        fclose(fpin);
    }

    exit(0);
}




void hexdump(void){

    int fdin;
    unsigned int address;
    int count;
    unsigned char buf[BUFF];
    int i;

    fdin = fpin->_fileno;
    for(address = 0;(count = read(fdin, buf, 16)) > 0; address += count){
        printf("%08x ", address);
        for(i = 0; i < count; i++){
            printf("%02x ", buf[i] & 0xff);
            if(buf[i] < 0x20 || 0x7e < buf[i])
                buf[i] = '.';
        }
        buf[count] = '\0';
        if(count < 16){
            while(count++ < 16)
            printf("    ");
        }
        printf(" %s\n", buf);
    }
    if(count == ERR){
        perror("read");
        exit(1);
    }
}




void usage(void){
    fprintf(stderr, "Usage : %s file...\n", command_name);
    exit(1);
}
*/