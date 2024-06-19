//명령행 인자로 받은 파일의 심벌릭 링크를 생성하고
//심벌릭 링크 파일의 내용과 원본 파일의 경로를 출력하는 프로그램을 작성하시오.
//$ usrsym test.c
#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    if(symlink(argv[1], "test.sym") == -1){
        perror("symlink");
    }
    char buf[BUFSIZ];
    readlink("test.sym", buf, BUFSIZ); printf("%s\n", buf);
    realpath("test.sym", buf); printf("%s\n", buf);
}