#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    int i = 0;
    
    for(int iter = atoi(argv[1]); iter <= atoi(argv[2]); iter++){
        i += iter;
    }

    printf("%d", i);

    return 0;
}