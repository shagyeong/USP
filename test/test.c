#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

int main(void){
    printf("before SIGCONT signal to parent\n");
    kill(getppid(), SIGCONT);
    printf("before SIGQUIT signal to me\n");
    kill(getpid(), SIGQUIT);
    printf("after SIGQUIT signal\n");
}