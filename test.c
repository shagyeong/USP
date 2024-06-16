#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
void printstat(char* path);
void mode(struct stat statbuf, char* charmode);

int main(int argc, char* argv[]){
    printstat(argv[1]);
}
void printstat(char* path){
    struct stat statbuf; stat(path, &statbuf);
    char charmode[9];mode(statbuf, charmode);
    printf("%s %d %s\n", path, (int)statbuf.st_uid, charmode);
}
void mode(struct stat statbuf, char* charmode){
    unsigned int intmode = statbuf.st_mode;
    //oth
    if(intmode & 1 == 1){charmode[8] = 'x';}else{charmode[8] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[7] = 'w';}else{charmode[7] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[6] = 'r';}else{charmode[6] = '-';} intmode >>= 1;
    //grp
    if(intmode & 1 == 1){charmode[5] = 'x';}else{charmode[5] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[4] = 'w';}else{charmode[4] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[3] = 'r';}else{charmode[3] = '-';} intmode >>= 1;
    //usr
    if(intmode & 1 == 1){charmode[2] = 'x';}else{charmode[2] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[1] = 'w';}else{charmode[1] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[0] = 'r';}else{charmode[0] = '-';}
}