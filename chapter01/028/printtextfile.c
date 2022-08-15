//지정한 텍스트파일 표시
#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]){
    FILE* fp;
    char in;

    if((fp = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "*ERROR : Can't open input file %s.\n", argv[1]);
        exit(1);
    }

    while((in = getc(fp)) != EOF){
        putchar(in);
    }

    fclose(fp);

    exit(0);
}