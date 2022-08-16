#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]){
    while(--argc > 0){
        if(**(++argv) == '-'){
            switch(argv[0][1]){
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
        else{
            break;
        }
    }

    printf("옵션이 아닌 파라미터 처리\n");

    exit(0); /*정상종료*/
}