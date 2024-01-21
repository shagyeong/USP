/* 디렉터리 이동 1(chdir(2)) */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(void){
    /* current working directory */
    char* cwd = getcwd(NULL, BUFSIZ);

    printf("current working directory : %s\n", cwd);
    if(access("test.txt", R_OK) == -1){
        perror("test.txt");
    }

    chdir("test");
    cwd = getcwd(NULL, BUFSIZ);

    printf("current working directory : %s\n", cwd);
    if(access("test.txt", R_OK) == -1){
        printf("perrortest\n");
        perror("test.txt");    
    }

    free(cwd);

    exit(0);
}
