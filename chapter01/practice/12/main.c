/* Makefile과 make */
#include<stdio.h>

extern int addnum(int a);
extern int subnum(int a);

int main(void){
    int sum1 = addnum(1);
    int sum2 = addnum(2);
    int sum3 = subnum(3);
    int sum4 = subnum(4);

    printf("sum1 = %d\n", sum1);     
    printf("sum2 = %d\n", sum2); 
    printf("sum3 = %d\n", sum3); 
    printf("sum4 = %d\n", sum4);

    return 0;     
}