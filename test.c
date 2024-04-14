#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* fp;
    int fd;
    char template[32];
    int ret;

    fp = tmpfile();
    fpust("tmep file", fp);
    fclose(fp);

    strcpy(template, "/tmp/testXXXXXX");
    fd = mkstemp(template);
    write(fd, "temp file", 10);
    close(fd);
}