#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int status;
    pid_t pid;
    siginfo_t infop;

    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        printf("child process\n");
        sleep(2);
        exit(2);
    }
    printf("parent process\n");
    while(waitid(P_PID, pid, &infop, WEXITED) != 0){
        printf("parent still wating...\n");
    }
    printf("child's PID: %d\n", infop.si_pid);
    printf("child's UID: %d\n", infop.si_uid);
    printf("child's Code: %d\n", infop.si_code);
    printf("child's status: %d\n", infop.si_status);
}