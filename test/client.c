#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9000

int main(void){
    int sd;
    char buf[256];
    struct sockaddr_in sin;
    //소켓 생성
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    //연결 요청
    connect(sd, (struct sockaddr*)&sin, sizeof(sin));
    //메시지 수신
    recv(sd, buf, sizeof(buf), 0);
    printf("from server: %s\n", buf);
    //소켓 반납
    close(sd);
}
