#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    
    extern char* optarg; /* 옵션 타겟*/
    // extern int optind; /* 옵션 인덱스 */
    int o;

    if((o = getopt(argc, argv, "pn:h")) == -1){
        printf("option description 2 ...\n");
    }
    else{
        do{
            switch(o){
                case 'p':
                    printf("welcome Linux System Programming\n");
                    break;
                case 'n':
                    printf("nice to meet you, %s\n", optarg);
                    break;
                case 'h':
                    printf("option description 1 ...\n");
                    break;

            }
        }while((o = getopt(argc, argv, "pn:h")) != -1);
    }
    return 0;
}