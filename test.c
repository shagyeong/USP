#include<unistd.h>
#include<sys/signal.h>
#include<stdlib.h>
#include<stdio.h>

void sighandler(int signo){
    psignal(signo, "received signal:");
    sleep(5);
    printf("in signal handler, after sleep\n");
}
int main(void){
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT); //SIGQUIT 블로킹
    act.sa_flags = 0;
    act.sa_handler = sighandler;
    if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0){
        perror("sigaction");
        exit(1);
    }
    fprintf(stderr, "input SIGINT: ");
    pause();
    fprintf(stderr, "after signal handler\n");
}