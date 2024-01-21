#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

void perrortest(void){
    if(access("test.txt", R_OK) == -1){
        printf("perrortest\n");
        perror("test.txt");    
    }
}