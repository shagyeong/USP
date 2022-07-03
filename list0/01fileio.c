#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFERSIZE 4

int main(int argc, char* argv[]){
    FILE* fp1 = fopen(argv[1], "r");
    FILE* fp2 = fopen(argv[2], "r");

    //fd : file discriptor
    //fileno : 파일 포인터를 인자로 파일 디스크립터를 리턴
    //int fileno(FILE* fp){...}
    int fd1 = fileno(fp1);
    int fd2 = fileno(fp2);

    char buffer[BUFFERSIZE];

    int count = read(fd1, buffer, BUFFERSIZE);
    
    printf("!!%d", count);

    fclose(fp1);
    fclose(fp2);

    exit(0);
}