#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    char row[1];
    row[0] = 48;        //ASCII 48: '0'
    
    char buf[1]; int n;
    int rflags = O_RDONLY;
    int rfd = open(argv[1], rflags);
    int wfd = STDOUT_FILENO;

    write(wfd, "row 0: ", 7);
    while((n = read(rfd, buf, 1)) != 0){
        write(wfd, buf, 1);
        if(buf[0] == 10){  //ASCII 10: new line
            write(wfd, "row ", 4);
            row[0]++; write(wfd, row, 1);
            write(wfd, ": ", 2);
        }
    }
    close(rfd);
}