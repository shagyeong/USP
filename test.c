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
int returnmask(char* ugo, char* rwx){
    int mask = 0B0000000000000000;
    if(strcmp(rwx, 'x') == 0){mask +=0B001;}
    else if(strcmp(rwx, 'w') == 0){mask +=0B010;}
    else if(strcmp(rwx, 'wx') == 0){mask +=0B011;}
    else if(strcmp(rwx, 'r') == 0){mask +=0B100;}
    else if(strcmp(rwx, 'rx') == 0){mask +=0B101;}
    else if(strcmp(rwx, 'rw') == 0){mask +=0B110;}
    else if(strcmp(rwx, 'rwx') == 0){mask +=0B111;}
    
    
}

int main(int argc, char* argv[]){
    char* fname = argv[argc - 1];
    struct stat statbuf; stat(fname, &statbuf);
    int mode = statbuf.st_mode;
    
    int index1 = 0;
    int index2 = 0;

    char sign; //+-=
    char ugo[3];
    char rwx[3];

    for(int i = 1; i < argc - 1; i++){
        while(argv[i][index1] != '+' && argv[i][index1] != '-'){
            ugo[index2] = argv[i][index1];
            index1++;
            index2++;
        }
        printf("%s", ugo);
        sign = argv[i][index1];
        index1++;
        index2 = 0;
        while(argv[i][index1] != '\0'){
            rwx[index2] = argv[i][index1];
            index1++;
            index2++;
        }
        
        printf("%c %s %s\n", sign, ugo, rwx);
        ugo[0] = '\0';ugo[1] = '\0';ugo[2] = '\0';
        rwx[0] = '\0';rwx[1] = '\0';rwx[2] = '\0';
        index1 = 0;
        index2 = 0;
    }
}


/*
ugo rwx
./test ug+rw test.txt
./test u+rwx g-x o-x test.txt
*/