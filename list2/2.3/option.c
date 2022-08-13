#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    while(--argc > 0){
        if(**(++argv) == '-'){
            switch(argv[0][1]){
                case 'a':
                    puts("a\n");
                    break;
                case 'b':
                    puts("b\n");
                    break;
                case 'c':
                    puts("c\n");
                    break;
                default:
                    puts("default");
            }
        }
        else{
            break;
        }
    }

    exit(0);
}