/* 현재 작업 디렉터리의 위치 검색(getcwd(3)) */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    /* current working directory */
    char* cwd;

    /* char* getcwd(char* buf, size_t size) */

    /* buf에 경로를 저장할 만큼 충분한 메모리를 할당하고 그 크기를 size에 지정한다 */
    char wd1[BUFSIZ];
    getcwd(wd1, BUFSIZ);
    printf("wd1 = %s\n", wd1);

    /* buf에 NULL을 지정하고 할당이 필요한 메모리 크기를 size에 지정한다 */
    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd1 = %s\n", cwd);
    free(cwd);

    /* buf에 NULL을 지정하고 size는 0으로 지정한다  */
    cwd = getcwd(NULL, 0);
    printf("cwd2 = %s\n", cwd);
    free(cwd);

    /* 경로보다 크기가 작은 buf를 지정한 경우 */
    char wd2[10];
    if(getcwd(wd2, 10) == NULL){
        perror("getcwd");
        exit(1);
    }

    exit(0);
}