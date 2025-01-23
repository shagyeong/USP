#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    char buf[10]; int n;
    int rfd; int rflags = O_RDONLY;
    int wfd; int wflags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t wmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    mode_t dmode = S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    rfd = (argv[2], rflags);
    mkdir(argv[1], dmode); chdir(argv[1]);
    wfd = (argv[2], wflags, wmode);

    while((n = read(rfd, buf, 5)) > 0){
        write(STDOUT_FILENO, buf, 5);
    }

    close(rfd);
    close(wfd);
}
