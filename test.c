#include<sys/ucontext.h>
#include<unistd.h>
#include<sys/signal.h>
#include<stdlib.h>
#include<stdio.h>

void sighandler(int signo, siginfo_t* sf, ucontext_t* uc){
    psiginfo(sf, "received signal:");
    printf("si_code : %d\n", sf->si_code);
}
int main(void){
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = (void (*)(int, siginfo_t *, void *))sighandler;
    sigemptyset(&act.sa_mask);
    if(sigaction(SIGUSR1, &act, (struct sigaction*) NULL) < 0){
        perror("sigaction");
        perror("sigactioin");
        exit(1);
    }
    pause();
}