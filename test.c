#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

void printbinary(int integer){
    for(int j = 15; j > -1; j--){
        printf("%d", integer >> j & 1);
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    char* fname = argv[(int)strlen(*argv)];
    struct stat statbuf; stat(fname, &statbuf);
    int mode = statbuf.st_mode;
    
    char ugo[3];
    char rwx[3];

    for(int i = 0; i < (int)strlen(*argv); i++){
        printf("%s ", argv[i]);
    }
}


/*
ugo rwx
./test ug+rw test.txt
./test u+rwx g-x o-x test.txt
*/