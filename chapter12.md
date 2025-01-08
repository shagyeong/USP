# 12장 소켓 프로그래밍 기초
## 12.1 개요
### 12.1.1 개요
#### 개요
- 인터넷의 확산으로 TCP/IP 프로토콜이 표준으로 자리잡음
- 리눅스에서도 제공됨
### 12.1.2 TCP/IP 프로토콜
#### TCP/IP 프로토콜 계층구조
|OSI 7계층|TCP/IP 계층|
|---|---|
|응용 계층|응용 계층|
|표현 계층||
|세션 계층||
|전송 계층|전송 계층|
|네트워크 계층|네트워크 계층|
|데이터 계층 링크|네트워크 접속 계층|
|물리 계층|하드웨어 계층|
#### 응용 계층
- 응용 계층: 서비스 제공을 위한 계층
- 주요 프로토콜: Telnet, FTP, HTTP, SMTP, DNS
#### 전송 계층
- 전송 계층: 패킷 전송을 담당하는 계층
- 주요 프로토콜: TCP, UDP
#### 네트워크 계층
- 네트워크 계층: 패킷이 전달되는 경로를 담당하는 계층
- 주요 프로토콜: IP, ICMP, ARP
#### 네트워크 접속/하드웨어 계층
- 물리적인 네트워크 연결을 담당하는 계층
#### TCP vs UDP
|TCP|UDP|
|---|---|
|연결지향형|비연결형|
|신뢰성 보장|신뢰성을 보장하지 않음|
|흐름 제어 기능 제공|흐름 제어 기능 없음|
|순서 보장|순서를 보장하지 않음|
- UDP: 신뢰성보다 속도가 중요한 서비스에 주로 사용됨
#### IP
- IP: TCP/IP 프로토콜에 대한 주소 프로토콜
- IP 주소: TCP/IP 프로토콜 기반 네트워크 주소
- 목적지 호스트를 알려주는 역할을 함
#### 포트 번호
- 포트 번호: 목적지 호스트의 어느 프로세스가 수신해 서비스할 것인지 지정
- 2바이트 정수(0 ~ 65535)
- 웰노운 포트(0 ~ 1023): 23-Telnet, 21-FTP, 80-HTTP, ...
### 12.1.3 소켓 인터페이스
#### 소켓 인터페이스
- 소켓 인터페이스: 응용 계층 - 전송 계층간 API
#### 소켓 인터페이스를 이용한 통신구조
- 응용 프로그램
- 소켓 인터페이스
- TCP/UDP
- IP
- 이더넷
- 라우터
- 인터넷

## 12.2 IP 주소와 포트 번호
### 12.2.1 IP 주소와 호스트명
#### IP 주소
- IP 주소: 인터넷 이용에 사용하는 주소
- 점으로 구분된 32비트 형태
- '네트워크/인터넷 주소'라고도 함
#### DNS
- DNS(domain name system): 호스트명/도메인명을 관리하는 시스템
- 호스트명: IP 주소와 매핑되는 호스트명 - 도메인명 형태의 주소
### 12.2.2 호스트명과 IP 주소 변환
#### 호스트명과 IP 주소 읽어오기: gethostent(3), sethostent(3), endhostent(3)
```C
#include<netdb.h>
struct hostent* gethostent(void);
void sethostent(int stayopen);
void endhostend(void);
```
- gethostent(3): 호스트명, IP주소를 구조체 hostent의 인스턴스에 저장하고 리턴
    - DB의 끝을 만나면 NULL 리턴
- sethostent(3): DB 읽기 위치를 시작 부분으로 재설정
    - gethostent(3) 사용 전 호출해야 함
    - 인자 stayopen이 0이 아닌 경우 DB가 열린 상태로 둠
- endhostent(3): DB를 닫음
#### 구조체 hostent
- <netdb.h>에 정의되어 있음
    ```C
    struct hostent{
        char* h_name;       //호스트명 저장
        char** h_aliases;   //호스트를 가리키는 다른 이름(alias) 저장
        int h_addrtype;     //호스트 주소 형식 지정
        int h_length;       //주소 길이 지정
        char** h_addr_list; //호스트 주소 목록 저장
    }
    ```
#### 예제: 호스트명 읽어오기(gethostent(3), endhostent(3))
- test.c
    ```C
    #include<netdb.h>
    #include<stdio.h>

    int main(void){
        struct hostent* hent;
        sethostent(0);
        while((hent = gethostent()) != NULL){
            printf("name=%s\n", hent->h_name);
        }
        endhostent();
    }
    ```
- demo
    ```
    $ ./test
    name=localhost
    name=shagyeong
    name=ip6-localhost
    ```
#### 호스트명으로 정보 검색: gethostbyname(3)
```C
#include<netdb.h>
struct hostent* gethostboyname(const char* name);
```
- 호스트명을 인자로 받아 검색
#### IP 주소로 정보 검색: gethostbyaddr(3)
```C
#include<netdb.h>
#include<sys/socket.h>
struct hostent* gethostbyaddr(const void* addr, socklen_t len, int type);
```
- IP 주소, 주소 길이, 주소 형식을 인자로 받아 검색
#### IP 주소 형식
- 주요 형식: AF_UNIX, AF_INET
    |형식|기능|형식|기능|
    |---|---|---|---|
    |AF_UNIX|호스트 내부 통신|AF_PPPOX||
    |AF_LOCAL||AF_LLC||
    |AF_INET|ipV4 인터넷 프로토콜|AF_IB||
    |AF_AX25||AF_MPLS||
    |AF_IPX||AF_CAN||
    |AF_APPLETALK||AF_TIPC||
    |AF_X25||AF_BLUETOOTH||
    |AF_INET6||AF_ALG||
    |AF_KEY||AF_VSOCK||
    |AF_NETLINK||AF_KCM||
    |AF_PACKET||AF_XDP||
    |AF_RDS||||
### 12.2.3 포트 번호
#### 개요
- 포트 번호: dest 호스트 서비스 프로세스 구분자
- 2바이트 정수 형식(0 ~ 65535)
- 웰노운 포트: 자주 사용되는 서비스(0 ~ 1023)
#### 포트 정보 읽어오기: getservent(3), setservent(3), endservent(3)
```C
#include<netdb.h>
struct servent* getservent(void);
void setservent(int stayopen);
void endservent(void);
```
- 호스트명과 IP 주소 읽어오기 함수군(gethostent(3), sethostent(3), endhostent(3))과 동작 방식이 같음
- getservent(3): 포트 정보를 구조체 servent의 인스턴스에 저장하고 리턴
    - DB의 끝을 만나면 NULL 리턴
- setservent(3): DB 읽기 위치를 시작 부분으로 재설정
    - getservent(3) 사용 전 호출해야 함
    - 인자 stayopen이 0이 아닌 경우 DB가 열린 상태로 둠
- endservent(3): DB를 닫음
#### 구조체 servent
- <netdb.h>에 정의되어 있음
    ```C
    struct servent{
        char* s_name;       \\포트명 저장
        char** s_aliases;   \\서비스를 가리키는 다른 이름(alias) 저장
        int s_port;         \\포트 번호 저장
        char* s_proto;      \\서비스에 사용하는 프로토콜 저장
    }
    ```
#### 예제: 포트 정보 읽어오기(getservent(3))
- test.c
    ```C
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
    ```
- demo
    ```
    $ ./test
    name=tcpmux, port=256
    name=echo, port=1792
    name=echo, port=1792
    name=discard, port=2304
    name=discard, port=2304
    ```
#### 서비스명으로 정보 검색: getservbyname(3)
```C
#include<netdb.h>
struct srevent* getservbyname(const char* name, const char* proto);
```
- proto: 프로토콜 - 'tcp' 또는 'udp'
#### 포트 번호로 정보 검색: getservbyport(3)
```C
#include<netdb.h>
struct servent* getservbyport(int port, const char* proto);
```
- proto: 프로토콜 - 'tcp' 또는 'udp'

## 12.3 소켓 프로그래밍
### 12.3.0 개요
#### 소켓
- 소켓: 응용 계층-전송 계층간 프로그래밍 인터페이스
### 12.3.1 소켓의 종류
#### 유닉스 도메인 소켓
- 유닉스 도메인 소켓: 같은 호스트에서 프로세스간 통신에 사용
- 주소 패밀리명: AF_UNIX
#### 인터넷 소켓
- 인터넷 소켓: 인터넷을 통해 다른 호스트와 통신에 사용
- 주소 패밀리명: AF_INET
### 12.3.2 소켓의 통신 방식
#### 전송 계층 프로토콜
- TCP: SOCK_STREAM
- UDP: SOCK_DGRAM
#### 통신 유형
- AF_UNIX - SOCK_STREAM
- AF_UNIX - SOCK_DGRAM
- AF_INET - SOCK_STREAM
- AF_INET - SOCK_DGRAM
### 12.3.3 소켓 주소 구조체
#### 유닉스 도메인 소켓 구조체
```C
struct sockaddr_un{
    _kernel_sa_family_t sun_family; //주소 패밀리명(AF_UNIX)
    char sun_path[UNIX_PATH_MAX];   //경로명
}
```
#### 인터넷 소켓 구조체
```C
struct sockaddr_in{
    _kernal_sa_family_t sin_family; //주소 패밀리명(AF_INET)
    _be16 sin_port;                 //포트 번호
    struct in_addr sin_addr;        //인터넷 주소
}
struct in_addr{
    _be32 s_addr;   //BE 32비트 주소
}
```
### 12.3.4 바이트 순서 함수
#### 바이트 오더링
- BE(big endian): 상위 주소(주소값이 작음)에 상위 바이트를 저장
- LE(little endian): 상위 주소에 하위 바이트를 저장
#### NBO(network byte ordering)
- NBO: TCP/IP 프로토콜의 바이트 오더링
- 반드시 BE 사용
#### HBO(host byte ordering)
- HBO: 호스트의 바이트 오더링
#### 바이트 오더링 함수
```C
unit32_t htonl(unit32_t hostlong);
unit16_t htons(unit16_t hostshort);
unit32_t ntohl(unit32_t netlong);
unit16_t ntohs(unit16_t netshort);
```
- h: 호스트
- n: 네트워크
- l: long(32비트)
- s: short(16비트)
#### 예제: NBO-HBO 변환(ntohs(3))
- servent 구조체는 NBO 형태로 저장
- test.c
    ```C
    #include<netdb.h>
    #include<stdio.h>

    int main(void){
        struct servent* port;
        setservent(0);
        for(int n = 0; n < 5; n++){
            port = getservent();
            printf("name=%s, port=%d\n", port->s_name, ntohs(port->s_port));
        }
    }
    ```
- demo
    ```
    $ ./test
    name=tcpmux, port=1
    name=echo, port=7
    name=echo, port=7
    name=discard, port=9
    name=discard, port=9
    ```
#### 예제: HBO-NBO 변환(htons(3))
- test.c
    ```C
    #include<netdb.h>
    #include<stdio.h>

    int main(void){
        struct servent* port;
        port = getservbyport(htons(21), "tcp");
        printf("name=%s, port=%d\n", port->s_name, ntohs(port->s_port));
    }
    ```
- demo
    ```
    t$ ./test
    name=ftp, port=21
    ```
### 12.3.5 IP 주소 변환 함수
#### 개요
- 시스템 외부로 출력시: 점으로 구분된 형태 사용
- 시스템 내부: 이진 값으로 바꾸어 저장
#### IP 주소 변환: inet_addr(3), inet_ntoa(3)
- inet_addr(3)
    ```C
    #include<sys/socket.h>
    #include<netinet/in.h>
    #include<arpa/inet.h>
    in_addr_t inet_addr(const char* cp);
    ```
    - 문자열 → 이진값
- inet_ntoa(3)
    ```C
    #include<arpa/inet.h>
    char* inet_ntoa(const struct in_addr in);
    ```
    - 이진값 → 문자열
#### 예제: IP 주소 변환(inet_addr(3), inet_ntoa(3))
- test.c
    ```C
    #include<sys/socket.h>
    #include<arpa/inet.h>
    #include<netdb.h>
    #include<stdlib.h>
    #include<stdio.h>
    #include<string.h>

    int main(void){
        in_addr_t addr;
        struct hostent* hp;
        struct in_addr in;
        if((addr = inet_addr("8.8.8.8")) == (in_addr_t)-1){
            printf("error: inet_addr(8.8.8.8)\n");
            exit(1);
        }
        hp = gethostbyaddr((char*)&addr, 4, AF_INET);
        if(hp == NULL){
            printf("host information not found\n");
            exit(2);
        }
        printf("name=%s\n", hp->h_name);
        memcpy(&in.s_addr, *hp->h_addr_list, sizeof(in.s_addr));
        printf("IP=%s\n", inet_ntoa(in));
    }
    ```
- demo
    ```
    $ ./test
    name=dns.google
    IP=8.8.8.8
    ```

## 12.4 소켓 인터페이스 함수
### 12.4.1 소켓 인터페이스 함수
#### 개요
- 주요 함수
    |함수|사용측|기능|
    |---|---|---|
    |socket(2)||소켓 fd 생성|
    |bind(2)|서버|소켓 fd를 IP주소/포트 번호와 결합|
    |listen(2)|서버|클라이언트 연결 요청 대기|
    |connect(2)|클라이언트|서버 접속 요청|
    |accept(2)|서버|연결 요청 수락|
    |send(2)||데이터 송신(SOCK_STREAM)|
    |recv(2)||데이터 수신(SOCK_STREAM)|
    |sendto(2)||데이터 송신(SOCK_DGRAM)|
    |recvfrom(2)||데이터 수신(SOCK_DGRAM)|
    |close(2)||소켓 fd 종료|
#### 소켓 fd 생성: socket(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
int socket(int domain, int type, int protocol);
```
- domain: 도메인 주소 패밀리(소켓 종류)
- type: 통신 방식(TCP/UDP)
- protocol: 소켓에 이용할 프로토콜 - 0 지정시 시스템이 결정
#### 소켓 fd를 IP주소/포트 번호와 결합: bind(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
```
- 소켓 fd - sockaddr 인스턴스간 연결 수행
- sockaddr: 소켓 종류, IP 주소, 포트 번호 지정
- sockfd: socket(2)로 생성한 소켓 fd
- addr: 소켓 이름 표현 구조체
- addrlen: addr의 크기
#### 클라이언트 연결 요청 대기: listen(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
int listen(int sockfd, int backlog);
```
- sockfd: 소켓 fd
- backlog: 최대 허용 클라이언트 수
#### 서버 접속 요청: connect(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
```
- sockfd: 소켓 fd
- addr: 접속하려는 서버의 IP 정보
- addrlen: addr의 크기
#### 연결 요청 수락: accept(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
```
- sockfd: 소켓 fd
- addr: 접속을 수락한 클라이언트 IP 정보
- addrlen: addr 크기
#### 데이터 송신: send(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
ssize_t send(int sockfd, const void* buf, size_t len, int flags);
```
- sockfd: 소켓 fd
- buf: 전송할 메시지 저장 주소
- len: 메시지의 크기
- flags: 데이터 송신 방법을 지정한 플래그
    - MSG_OOB: out of band 데이터로 처리 - 수신 확인을 받지 않아도 다른 메시지를 계속 전송
    -MSG_DONTROUTE: 데이터 라우팅 설정 해제
#### 데이터 수신: recv(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
ssize_t recv(int sockfd, void* buf, size_t len, int flgas)
```
- sockfd: 소켓 fd
- buf: 전송받은 메시지 저장 주소
- len: 메시지의 크기
- flags: 데이터 송신 방법을 지정한 플래그
#### 데이터 송신: sendto(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
ssize_t sendto(int sockfd, const void* buf, size_t len, int flags, const struct sockaddr* dest_addr, socklen_t addrlen);
```
- sockfd: 소켓 fd
- buf: 전송할 메시지 저장 주소
- len: 메시지의 크기
- flags: 데이터 송신 방법을 지정한 플래그
- dest_addr: 메시지를 받을 호스트의 주소
- addrlen: dest_addr의 크기
#### 데이터 수신: recvfrom(2)
```C
#include<sys/types.h>
#include<sys/socket.h>
ssize_t recvfrom(int sockfd, const void* buf, size_t len, int flags, const struct sockaddr* src_addr, socklen_t addrlen)
```
- sockfd: 소켓 fd
- buf: 전송받은 메시지 저장 주소
- len: 메시지의 크기
- flags: 데이터 송신 방법을 지정한 플래그
- dest_addr: 메시지를 보내는 호스트의 주소
- addrlen: src_addr의 크기
### 12.4.2 소켓 인터페이스 함수 호출 순서
#### 소켓 인터페이스 함수 호출 순서
|서버|기능|클라이언트|
|---|---|---|
|socket()||socket()|
|bind()|||
|listen()|||
|accept()|연결|connect()|
|send()/recv()|데이터 송수신|send()/recv()|
|close()||close()|

## 12.5 소켓 프로그래밍 예제
### 12.5.1 유닉스 도메인 소켓 예제
#### server
```C
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define SOCKET_NAME "shagyeong"

int main(void){
    char buf[256];
    struct sockaddr_un server;
    struct sockaddr_un client;
    int ssd; int csd;    //서버 sd, accept할 클라이언트의 sd
    int slen; int clen;  //서버, 클라이언트 length
    //서버 소켓 생성(호스트 내부 TCP 통신)
    ssd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset((char*)&server, 0, sizeof(struct sockaddr_un));
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SOCKET_NAME);
    slen = sizeof(server.sun_family) + strlen(server.sun_path);
    //포트 연결
    bind(ssd, (struct sockaddr*)&server, slen);
    //요청 대기
    listen(ssd, 5);
    printf("wating...\n");
    //요청 수락
    csd = accept(ssd, (struct sockaddr*)&client, &clen);
    //메시지 수신
    recv(csd, buf, sizeof(buf), 0);
    printf("received message: %s\n", buf);
    //소켓 반납
    close(ssd);
    close(csd);
}
```
#### client
```C
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define SOCKET_NAME "shagyeong"

int main(void){
    char buf[256];
    struct sockaddr_un server;
    int csd;
    int clen;
    //클라이언트 소켓 생성(호스트 내부 TCP 통신)
    csd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset((char*)&server, '\0', sizeof(server));
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SOCKET_NAME);
    clen = sizeof(server.sun_family) + strlen(server.sun_path);
    //연결 요청
    connect(csd, (struct sockaddr*)&server, clen);
    //메시지 송신
    strcpy(buf, "test message");
    send(csd, buf, sizeof(buf), 0);
    //소켓 반납
    close(csd);    
}
```
#### demo
```
$ ./server
wating...
```
```
$ ./client
```
```
$ ./server
wating...
received message: test message
```
### 12.5.2 인터넷 소켓 예제
#### server
```C
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
```
#### client
```C
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
```
#### demo
```
$ ./server
```
```
$ ./client
from server: your IP: 127.0.0.1

```