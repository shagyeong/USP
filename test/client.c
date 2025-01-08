#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9003

int main(void){
    char buf[256];
    struct sockaddr_in client;
    int csd;
    int clen;
    //클라이언트 소켓 세팅
    csd = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*)&client, '\0', sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORTNUM);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    //연결 요청
    connect(csd, (struct sockaddr*)&client, sizeof(client));
    //메시지 수신
    clen = recv(csd, buf, sizeof(buf), 0);
    buf[clen] = '\0';
    printf("from server: %s\n", buf);
    //소켓 반납
    close(csd);
}