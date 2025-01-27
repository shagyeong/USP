#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("_PC_LINK_MAX: %ld\n", pathconf(".", _PC_LINK_MAX));
    printf("_PC_NAME_MAX: %ld\n", pathconf(".", _PC_NAME_MAX));
    printf("_PC_PATH_MAX: %ld\n", pathconf(".", _PC_PATH_MAX));
}