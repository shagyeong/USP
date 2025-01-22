#include<stdio.h>

int main(int argc, char* argv[]){
    long offset;
    char buf[BUFSIZ]; int n;
    FILE* rfp = fopen(argv[1], "r");

    offset = ftell(rfp); printf("current offset: %d\n", (int)offset);
    fread(buf, sizeof(char), 5, rfp);
    printf("buf: %s\n", buf);

    fseek(rfp, 1, SEEK_CUR);  //공백 건너뛰도록 오프셋 이동
    offset = ftell(rfp); printf("current offset: %d\n", (int)offset);
    fread(buf, sizeof(char), 6, rfp);
    printf("buf: %s\n", buf);

    fseek(rfp, 1, SEEK_CUR);
    offset = ftell(rfp); printf("current offset: %d\n", (int)offset);
    fread(buf, sizeof(char), 11, rfp);
    printf("buf: %s\n", buf);

    //rewind
    rewind(rfp); offset = ftell(rfp);
    printf("rewind offset: %d\n", (int)offset);
    
    fclose(rfp);
}