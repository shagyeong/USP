#include<unistd.h>
#include "myclock.h"

int main(int argc, char* argv[]){
    char hbuf[2]; gethour(hbuf);
    char mbuf[2]; getminute(mbuf);
    char sbuf[2]; getsec(sbuf);

    write(STDOUT_FILENO, hbuf, 2); write(STDOUT_FILENO, ":", 1);
    write(STDOUT_FILENO, mbuf, 2); write(STDOUT_FILENO, ":", 1);
    write(STDOUT_FILENO, sbuf, 2); write(STDOUT_FILENO, "\n", 1);
}