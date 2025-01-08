# 13장 소켓 프로그래밍 활용
## 13.1 개요
### 13.1.1 개요
#### 데몬(daemon) 프로세스
- 데몬 프로세스: 서버 프로세스를 의미
- 반복 서버: 클라이언트의 요청을 직접 처리하는 데몬 프로세스
- 동시 동작 서버: 서비스와 관련 있는 프로세스를 fork(2)로 생성해 제공

## 13.2 TCP 기반 프로그래밍
### 13.2.1 반복 실행 서버
#### server
```C
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9001

int main(void){
    char buf[256];
    struct sockaddr_in server, client;
    int ssd, csd;
    int clen = sizeof(client);    
    //서버 소켓 세팅
    memset((char*)&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUM);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssd = socket(AF_INET, SOCK_STREAM, 0);
    //소켓-포트 연결
    bind(ssd, (struct sockaddr*)&server, sizeof(server));
    //요청 대기
    listen(ssd, 5);
    //클라이언트 요청 처리
    while(1){
        csd = accept(ssd, (struct sockaddr*)&client, &clen);
        sprintf(buf, "%s", inet_ntoa(client.sin_addr));
        printf("send a message to client(%s)\n", buf);
        strcpy(buf, "welcome to network server!!");
        send(csd, buf, strlen(buf) + 1, 0);
        recv(csd, buf, sizeof(buf), 0);
        printf("from client: %s\n", buf);
        close(csd);
    }
    close(ssd);
}
```
#### client
```C
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9001

int main(void){
    char buf[256];
    int csd;
    struct sockaddr_in client;
    //클라이언트 소켓 세팅
    memset((char*)&client, '\0', sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORTNUM);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    csd = socket(AF_INET, SOCK_STREAM, 0);
    //연결 요청
    connect(csd, (struct sockaddr*)&client, sizeof(client));
    //메시지 수신
    recv(csd, buf, sizeof(buf), 0);
    printf("from serever: %s\n", buf);
    //메시지 송신
    strcpy(buf, "I want a HTTP serevice");
    send(csd, buf, sizeof(buf) + 1, 0);
    //소켓 반납
    close(csd);
}
```
#### demo
```
$ ./server
send a message to client(127.0.0.1)
from client: I want a HTTP serevice
send a message to client(127.0.0.1)
from client: I want a HTTP serevice
send a message to client(127.0.0.1)
from client: I want a HTTP serevice
^C
```
```
$ ./client
from serever: welcome to network server!!
$ ./client
from serever: welcome to network server!!
$ ./client
from serever: welcome to network server!!
```
### 13.2.2 동시 동작 서버
#### server
```C
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sdtlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9002

int main(void){
    char buf[256];
    struct sockaddr_in server, client;
    int ssd, int csd;
    int clen = sizeof(client);
    //서버 소켓 세팅
    ssd = socket(AF_INET, SOCK_STREAM, 0);
    memsset((char*)&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUM);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //소켓-포트 연결
    bind(ssd, (strut sockaddr*)&server, sizeof(server));
    //연결 대기
    listen(sd, 5);
    //클라이언트 요청 처리
    while(1){
        csd = accept(ssd, (struct sockaddr*)&client, &clen);
        switch(fork()){
            case 0:
                strcpy(buf, "welcome to server");
                send(csd, buf, strlen(buf) + 1, 0);
                recv(csd, buf, sizeof(buf), 0);
                printf("from client: %s\n", buf);
                close(csd);
                sleep(5);
                exit(0);
        }
    }
    close(ssd);
}
```
### 13.2.3 동시 동작 서버: 서비스 프로세스 호출(exec())
#### server
```C
```
#### client
```C
```
#### demo
```
```
### 13.2.4 동시 동작 서버: 명령행 인자로 소켓 기술자 전달
#### server
#### client
#### demo

## 13.3 UDP 기반 프로그래밍
