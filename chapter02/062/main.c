#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]){
    for(int i = 0; i < argc; i++){
        printf("argv[%d] : %s %c %c\n", i, argv[i], argv[i][0], argv[i][1]);
    }

    for(int i = 0; i < argc; i++){
        printf("%c\n", **argv);
        argv++;
    }

    exit(0);
}