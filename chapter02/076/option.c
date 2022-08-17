#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
                    case '-':
                        if(strcmp(p1, "-help") == 0){
                            printf("option help\n");
                        }
                        else if(strcmp(p1, "-long") == 0){
                            printf("option long\n");
                        }
                        else if(strcmp(p1, "-term") == 0){
                            printf("option term\n");
                        }
                        /*...*/
                        else{
                            printf("일치하는 단어 옵션 없음\n");
                        }
                        *(p1 + 1) = '\0';
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