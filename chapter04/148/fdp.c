#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]){
    int fd0 = stdin->_fileno; /*표준 입력의 파일 디스크립터*/
    int fd1 = stdout->_fileno; /*표준 출력의 파일 디스크립터*/
    int fd2 = stderr->_fileno; /*표준 에러 출력의 파일 디스크립터*/

    FILE* fp3 = fopen(argv[1], "r");
    int fd3 = fp3->_fileno;

    FILE* fp4 = fopen(argv[2], "r");
    int fd4 = fp4->_fileno;

    printf("fd of stdin : %d\n", fd0);
    printf("fd of stdout : %d\n", fd1);
    printf("fd of stderr : %d\n", fd2);

    printf("fd of new file 1 : %d\n", fd3);
    printf("fd of new file 2 : %d\n", fd4);

    exit(0);
}