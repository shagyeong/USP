#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[], char* envp[]){
    
    int i;

    for(i = 0; envp[i]; i++){
        printf("%s\n", envp[i]);
    }

    exit(0);
}