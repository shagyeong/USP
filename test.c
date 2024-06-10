#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

void sighandler(int signo){
    printf("signal handler signum : %d\n", signo);
    psignal(signo, "recieved signal"); //8.8절에서 다루는 함수
}

int main(void){
    void (*hand)(int);
    hand = signal(SIGINT, sighandler); //SIGINT : Ctrl + C 인터럽트시 종료
    if(hand == SIG_ERR){
        perror("signal");
        exit(1);
    }
    printf("wait 1st Ctrl + C... : SIGINT\n");
    pause(); //pause(2) : 시그널이 입력될 때 까지 기다리는 함수
    printf("after 1st signal handler\n");
    printf("wait 2nd Ctrl + C... : SIGINT\n");
    pause();
    printf("after 2nd signal handler\n");
}