#include<time.h>
#include<stdio.h>

char* op[] = {"%x %X", "%G년 %m월 %d일 %U주 %H:%M", "%r"};

int main(void){
    struct tm* tm;
    int n;
    time_t timep;
    char buf[257];

    time(&timep);
    tm = localtime(&timep);

    strftime(buf, sizeof(buf), op[0], tm);
    printf("%s\n", buf);
    strftime(buf, sizeof(buf), op[1], tm);
    printf("%s\n", buf);
    strftime(buf, sizeof(buf), op[2], tm);
    printf("%s\n", buf);
}