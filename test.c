#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

int main(void){
    printf("before SIGCONT signal to parent\n"); //무시
    kill(getppid(), SIGCONT);
    printf("before SIGQUIT signal to me\n"); //코어 덤프
    kill(getpid(), SIGQUIT);
    printf("affter SIGQUIT signal\n");
}