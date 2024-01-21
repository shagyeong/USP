/* 캐릭터 포인터 복습 */
#include<stdio.h>

int main(void){
    char* cp = "abcde";
    
    printf("%s\n", cp);         /* abcde */
    printf("%c\n", *cp);        /* a */
    printf("%c\n", *(++cp));    /* b */

    return 0;
}