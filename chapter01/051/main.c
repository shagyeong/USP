/* 옵션 처리(getopt(3)) */
#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int n;
    extern char* optarg; /* 옵션 타겟*/
    extern int optind; /* 옵션 인덱스 */

    printf("current optind : %d\n", optind);
    while((n = getopt(argc, argv, "x:yz")) != -1){ /* 옵션 x에는 인자가 있음 */
        switch(n){
            case 'x':
                printf("option x\n");
                break;
            case 'y':
                printf("option y\n");
                break;
            case 'z':
                printf("option z\n");
                break;
        }

        printf("next optind : %d\n", optind);
    }

    return 0;
}