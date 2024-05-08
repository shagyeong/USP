#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* val;
    if((val = getenv("TERM")) == NULL)
        printf("term not defined\n");
    else
        printf("TERM=%s\n", val);

    setenv("TERM", "vt100", 0);
    val = getenv("TERM");
    printf("TERM=%s\n", val);

    setenv("TERM", "vt100", 1); //overwrite
    val = getenv("TERM");
    printf("TERM=%s\n", val);
}