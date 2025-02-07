#include "myclock.h"

char __itoa(int i){
    char c;
    switch(i){
        case 0: c = '0'; break;
        case 1: c = '1'; break;
        case 2: c = '2'; break;
        case 3: c = '3'; break;
        case 4: c = '4'; break;
        case 5: c = '5'; break;
        case 6: c = '6'; break;
        case 7: c = '7'; break;
        case 8: c = '8'; break;
        case 9: c = '9'; break;
    }
    return c;
}

void gethour(char* hbuf){
    struct tm* tmbuf;
    time_t timep;
    time(&timep);
    tmbuf = gmtime(&timep);

    int hour = tmbuf -> tm_hour + 9;

    hbuf[0] = __itoa(hour / 10); hour -= (hour/10) * 10;
    hbuf[1] = __itoa(hour);
}
