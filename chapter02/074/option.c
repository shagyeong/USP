#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]){
    char* cp; /*'-' 이후 연속적으로 제시된 옵션 순회 포인터*/

    while(--argc > 0){
        if(**(++argv) == '-'){
            cp = *argv;

            while(*(++cp)){
                switch(*cp){
                    case 'a':
                        printf("option a\n");
                        break;
                    case 'b':
                        printf("option b\n");
                        break;
                    case 'c':
                        printf("option c\n");
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

    exit(0); /*정상종료*/
}