#include<stdio.h>

int main(int argc, char** argv, char** envp){
    int n;
    char** env = envp;

    printf("arg.c main\n");
    printf("argc = %d\n", argc);
    for(n = 0; n < argc; n++){printf("argv[%d] = %s\n", n , argv[n]);}
    while(*env){printf("%s\n", *env);env++;}
}