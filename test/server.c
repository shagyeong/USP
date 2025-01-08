#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9000

int main(void){
    char buf[256];
    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(cli);
    //소켓 생성
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    //포트 매핑
    bind(sd, (struct sockaddr*)&sin, sizeof(sin));
    //요청 대기
    listen(sd, 5);
    //요청 수락
    ns = accept(sd, (struct sockaddr*)&cli, &clientlen);
    //메시지 송신
    sprintf(buf, "your IP: %s\n", inet_ntoa(cli.sin_addr));
    send(ns, buf, strlen(buf) + 1, 0);
    //소켓 반납
    close(ns);
    close(sd);
}
