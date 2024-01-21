/* 명령행 인자의 전달 */
#include<stdio.h>

int main(int argc, char*argv[]){
    int iter = 0;

    printf("argc : %d\n", argc);

    for(; iter < argc; iter++){
        printf("argv[%d] : %s\n", iter, argv[iter]);
    }

    return 0;
}