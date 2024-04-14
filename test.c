#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* fp;
    int n;
    long cur;
    char buf[BUFSIZ];
    if((fp = fopen("test.txt", "r")) == NULL){
        perror("fopen");
        exit(1);
    }

    cur = ftell(fp);
    printf("current offset : %d\n", (int)cur);
    n = fread(buf, sizeof(char), 5, fp);
    buf[n] = '\0';
    printf("str : %s\n", buf);

    fseek(fp, 1, SEEK_CUR);
    cur = ftell(fp);
    printf("current offset : %d\n", (int)cur);
    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = '\0';
    printf("str : %s\n", buf);

    fseek(fp, 1, SEEK_CUR);
    cur = ftell(fp);
    printf("current offset : %d\n", (int)cur);
    n = fread(buf, sizeof(char), 11, fp);
    buf[n] = '\0';
    printf("str : %s\n", buf);

    rewind(fp);
    cur = ftell(fp);
    printf("rewind offset : %d\n", (int)cur);

    fclose(fp);
}