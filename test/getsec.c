#include "myclock.h"

void getsec(char* sbuf){
    struct tm* tmbuf;
    time_t timep;
    time(&timep);
    tmbuf = gmtime(&timep);

    int sec = tmbuf -> tm_sec;

    sbuf[0] = __itoa(sec / 10); sec -= (sec/10) * 10;
    sbuf[1] = __itoa(sec);
}
