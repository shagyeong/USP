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

## 12.4 소켓 인터페이스 함수

## 12.5 소켓 프로그래밍 예제
