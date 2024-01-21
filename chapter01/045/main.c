/* 메모리 할당 */
#include<stdio.h>
#include<stdlib.h>

int main(void){
    char* p1;
    p1 = malloc(sizeof(char) * 10);
    
    *p1 = 'a';

    printf("%c\n", *p1);

    free(p1);

    return 0;
}