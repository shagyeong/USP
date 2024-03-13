#include<stdio.h>

int main(int argc, char* argv[]){
    int n = 0;
    printf("argc = %d\n", argc);

    while(n < argc){
        printf("argv[%d] = %s\n", n, argv[n]);
        n += 1;
    }

    return 0;
}