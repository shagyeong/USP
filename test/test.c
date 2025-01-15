#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc, char* argv[]){
    pid_t pid;
    if(argc == 1){pid = getpid();printf("PPID: %d\n", getppid());}
    else{pid = atoi(argv[1]);}
    printf("PGID: %d\n", getpgid(pid));
    printf("SID: %d\n", getsid(pid));
}
