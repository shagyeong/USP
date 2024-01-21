/* * 현재 디렉터리를 기억하고 있다가 다른 디렉터리로 이동해 작업한 후 원래 디렉터리로 돌아오는 프로그램을 만들어라 */
/* test 디렉터리에 새 파일을 만들고 다시 돌아오기 */
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(void){
    DIR* dp = opendir(".");
    struct dirent* dent;

    chdir("test");
    
}