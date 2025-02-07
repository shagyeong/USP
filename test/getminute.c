#include "myclock.h"

void getminute(char* mbuf){
    struct tm* tmbuf;
    time_t timep;
    time(&timep);
    tmbuf = gmtime(&timep);

    int minute = tmbuf -> tm_min;

    mbuf[0] = __itoa(minute / 10); minute -= (minute/10) * 10;
    mbuf[1] = __itoa(minute);
}
