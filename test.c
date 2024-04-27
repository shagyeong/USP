#include<sys/types.h>
#include<time.h>
#include<stdio.h>

int main(void){
    time_t tloc;
    time(&tloc);
    printf("time : %d\n", (int)tloc);
}