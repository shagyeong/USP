//여러 개의 원시 코드를 gcc로 처리
#include<stdio.h>

#include "./hello.h"
#include "./bye.h"

int main(void){
    hello();
    bye();

    return 0;   
}