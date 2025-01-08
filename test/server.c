#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9003

int main(void){
    struct sockaddr_in server, client;
    int ssd, csd;
    int clen = sizeof(client);
    //서버 소켓 세팅
    ssd = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*)&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUM);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //바인딩
    bind(ssd, (struct sockaddr*)&server, sizeof(server));
    //연결 대기
    listen(ssd, 5);
    //요청 처리
    while(1){
        csd = accept(ssd, (struct sockaddr*)&client, &clen);
        switch(fork()){
            case 0:
                printf("fork client\n");
                close(ssd);
                //입출력 전환: 표준 입출력 → 클라이언트 sd
                dup2(csd, STDIN_FILENO);
                dup2(csd, STDOUT_FILENO);
                execl("./test", "test", (char*)0);
                close(csd);
        }
        close(ssd);
    }
}