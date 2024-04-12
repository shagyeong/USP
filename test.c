#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp;FILE* wfp;
    char buf[BUFSIZ];
    if((rfp = fopen("test.txt", "r")) == NULL){
        perror("read");
        exit(1);
    }
    if((wfp = fopen("test.out", "w")) == NULL){
        perror("write");
        exit(1);
    }

    while(fgets(buf, BUFSIZ, rfp) != NULL){
        fputs(buf, wfp);
    }

    fclose(rfp);
    fclose(wfp);
}