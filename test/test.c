#include<signal.h>
#include<stdio.h>

int main(void){
    sigset_t st;
    sigemptyset(&st);
    sigaddset(&st, SIGINT);
    //sigaddset(&st, SIGQUIT);
    printf("SIGINT: %d\n", sigismember(&st, SIGINT));
    printf("SIGQUIT: %d\n", sigismember(&st, SIGQUIT));
}