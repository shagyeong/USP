#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp; int n;
    int id, lin, eng, cp;
    if((rfp = fopen("test.dat", "r")) == NULL){
        perror("fopen");
        exit(1);
    }

    while((n = fscanf(rfp, "%d %d %d %d", &id, &lin, &eng, &cp)) != EOF){
        printf("id : %d, avg = %d\n", id, (lin + eng + cp) / 3);
    }

    exit(0);
}