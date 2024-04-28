#include<sys/time.h>
#include<stdio.h>

int main(void){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("tv_sec : %d\n", (int)tv.tv_sec);
    printf("tv_usec : %d\n", (int)tv.tv_usec);
}