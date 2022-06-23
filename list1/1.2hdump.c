/*










*/

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

/*

*/
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

/*

*/
void usage(void){
    fprintf(stderr, "Usage : %s file...\n", command_name);
    exit(1);
}