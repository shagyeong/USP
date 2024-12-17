#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(void){
    printf("pid: %d\n", (int)getpid());
    printf("pgrp: %d\n", (int)getpgrp());
    printf("sid: %d\n", (int)getsid(0));
}