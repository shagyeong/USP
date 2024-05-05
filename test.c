#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int n;
	extern char* optarg;

    while((n = getopt(argc, argv, "pn:h")) != -1){
        switch(n){
            case 'p':
                printf("Welcome Linux System Programming!\n");
                break;
            case 'n':
                printf("Nice to meet %s\n", optarg);
                break;
            case 'h':
                printf("-p, -n\n");
                break;
        }
    }
}