#include<sys/sysinfo.h>
#include<stdio.h>

int main(void){
    struct sysinfo info;
    sysinfo(&info);

    printf("totalram : %ld\n", info.totalram);
    printf("freeram : %ld\n", info.freeram);
    printf("procs : %d\n", info.procs);
}