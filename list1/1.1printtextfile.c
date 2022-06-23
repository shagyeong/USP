#include<stdio.h>
#include<stdlib.h>

void main(int argc, char *argv[]){
    FILE* infilepointer = fopen(argv[1], "r");
    char in;

    if(infilepointer == NULL){
        fprintf(stderr, "*ERROR : Can't open input file %s.\n", argv[1]);
        exit(1);
    }

    while((in = getc(infilepointer)) != EOF){
        putchar(in);
    }

    fclose(infilepointer);

    exit(0);    
}