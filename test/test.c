#include<netdb.h>
#include<stdio.h>

int main(void){
    struct servent* port;
    setservent(0);
    for(int n = 0; n < 5; n++){
        port = getservent();
        printf("name=%s, port=%d\n", port->s_name, port->s_port);
    }
}