#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(void){
    char template[32] = "/tmp/testXXXXXX";
    int tfd = mkstemp(template);
    FILE* tfp = tmpfile();

    char buf[10] = "hello"; write(tfd, buf, 10);
    fprintf(tfp, "hello");

    close(tfd);
    fclose(tfp);
}