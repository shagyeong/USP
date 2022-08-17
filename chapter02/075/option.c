#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]){
    char* p1;
    char* p2;

    while(--argc > 0){
        if(**(++argv) == '-'){
            p1 = *argv;

            while(*++p1){
                switch(*p1){
                    case 'a':
                        printf("option a\n");
                        break;
                    case 'b':
                        printf("option b\n");
                        break;
                    case 'c':
                        printf("option c\n");
                        p2 = *++argv;
                        argc--;
                        break;
                    default:
                        printf("일치하는 옵션 없음\n");
                        exit(1);
                }
            }
        }
        else{
            break;
        }
    }

    exit(0);
}