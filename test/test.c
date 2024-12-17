#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    pid_t pid;
    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            printf("child process\n");
            printf("pid: %d, ppid: %d\n", (int)getpid(), (int)getppid());
            break;
        default:
            printf("parent process\n");
            printf(
                "pid: %d, ppid: %d, child's pid: %d\n",
                (int)getpid(), (int)getppid(), (int)pid
            );
    }
}