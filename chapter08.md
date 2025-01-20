# 8장 시그널
## 8.1 개요
### 8.1.1 시그널
#### 시그널
- 시그널: 프로세스에 발생한 이벤트를 알리는 비동기적 소프트웨어 인터럽트
- 예외적 상황이 발생한 경우
- 다른 프로세스에 시그널을 보내는 경우
- 미리 정의된 상수를 이용
#### 시그널 처리
- 기본 동작 수행
- 시그널 무시
- *시그널 핸들러* 수행
### 8.1.2 주요 함수
#### 시그널 보내기 함수
```C
int kill(pid_t pid, int sig);
int raise(int sig);
void abort(void);
```
#### 시그널 핸들러 지정 함수
```C
sighandler_t signal(int signum, sighandler_t handler);
sighandler_t sigset(int sig, sighandler_t disp);
```
- 시그널 핸들러: 시그널 처리시 수행할 작업(함수)
#### 시그널 집합 함수
```C
int sigemptyset(sigset_t* set);
int sigfillset(sigset_t* set);
int sigaddset(sigset_t* set, int signum);
int sigdelset(sigset_t*set, int signum);
int sigismember(const sigset_t* set, int signum);
```
- 시그널 집합: (POSIX)복수의 시그널을 처리하기 위해 도입한 개념
#### 시그널 제어 함수
```C
int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);   //시그널 제어
vod psiginfo(const siginfo_t* pinfo, const char* s);    //시그널 발생 원인 출력
```
- *플래그*를 지정해 시그널 처리 작업 제어
#### 알람 시그널 함수
```C
unsigned int alarm(unsigned int seconds);   //알람 시그널
int getitimer(int which, struct itimerval* curr_value); //인터벌 타이머
int setitimer(int which, const struct itimerval* vlaue, struct itimerval* ovalue);  //인터벌 타이머
```
#### 기타 시그널 함수
```C
//시그널 정보 출력
void psignal(int sig, const char* s);
char* strsignal(int sig);
//시그널 블로킹과 해제
int sighold(int sig);
int sigrelse(int sig);
int sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
//시그널 기다리기
int pause(void);
int sigpause(int sig);
int sigsuspend(const sigset_t* mask);
//시그널 보내기
int sigsend(idtype_t idtype, id_t id, int sig);
//시그널 무시 처리
int sigignore(int sig);
```

## 8.2 시그널의 개념
### 8.2.1 시그널 발생
#### 시그널 발생
- 프로그램에서 예외적 상황 발생(0으로 나누기 등)
- 시그널을 보낼수 있는 함수(kill(2) 등)를 이용해 프로세스에서 다른 프로세스로 시그널을 보내는 경우
- 사용자가 인터럽트 키(ctrl + c 등)를 입력한 경우
### 8.2.2 시그널 처리 방법
#### 시그널 처리 방법
- 기본 동작 수행
- 시그널 무시
- 지정된 함수 호출
- 시그널 블록
#### 기본 동작 수행
- 시그널에 지정된 기본 동작 수행
- 프로세스 종료
- 일시 중지(suspend)
- 재시작(resume)
#### 시그널 무시
- 시스템이 프로세스에 시그널을 전달하지 않음
#### 지정된 함수 호출
- 시그널 핸들러: 시그널 처리를 위해 지정하는 함수
- 시그널을 받은 경우 기존 처리 작업을 중지하고 시그널 핸들러 호출
- 시그널 핸들러 동작 완료시 기존 처리 작업 수행
#### 시그널 블록
- (수신 측)프로세스에서 특정 부분이 실행되는 동안 시그널이 발생되지 않도록 블로킹 가능
- 시그널 블록이 해제되면 큐에 있던 시그널이 전달됨
### 8.2.3 시그널 종류
#### 시그널 종류
- <signal.h>에 정의되어 있다
- 코어 덤프: 코어 파일을 만들고 종료
- |시그널|번호|기본 처리|발생 요건|
  |---|---|---|---|
  |SIGHUP|1|종료|행업으로 터미널과 연결이 끊어짐|
  |SIGINT|2|종료|사용자 인터럽트 Ctrl + C|
  |SIGQUIT|3|코어 덤프|사용자 종료신호 Ctrl + \\|
  |SIGILL|4|코어 덤프|잘못된 명령 사용|
  |SIGTRAP|5|코어 덤프|trace 또는 break point에서 트랩 발생|
  |SIGABRT|6|코어 덤프|abort(3)에 의해 발생|
  |SIGIOT|6|코어 덤프|SIGABRT와 동일|
  |SIGBUS|7|코어 덤프|버스 오류|
  |SIGFPE|8|코어 덤프|산술 연산 오류|
  |SIGKILL|9|종료|강제 종료|
  |SIGUSR1|10|종료|사용자가 정의해 사용하는 시그널 1|
  |SIGSEGV|11|코어 덤프|세그멘테이션 오류|
  |SIGUSR2|12|종료|사용자가 정의해 사용하는 시그널 2|
  |SIGPIPE|13|종료|잘못된 파이프 처리|
  |SIGALRM|14|종료|alarm(2)에 의해 발생|
  |SIGTERM|15|종료|소프트웨어 종료|
  |SIGSTKFLT|16|종료|보조 프로세스 스택 오류(리눅스에서는 지원 안 함)|
  |SIGCHLD|17|무시|자식 프로세스의 상태가 바뀜|
  |SIGCONT|18|무시|중지된 프로세스 재시작|
  |SIGSTOP|19|중지|중지 시그널 - SIGCONT 수신까지 프로세스 수행 중단|
  |SIGTSTP|20|중지|사용자 중지 신호 Ctrl + Z|
  |SIGTTIN|21|중지|터미널 입력 대기를 위한 중지|
  |SIGTTOU|22|중지|터미널 출력을 위한 중지|
  |SIGURG|23|무시|소켓에 긴급한 상황 발생|
  |SIGXCPU|24|코어 덤프|CPU 시간 제한 초과|
  |SIGXFSZ|25|코어 덤프|파일 크기 제한 초과|
  |SIGVTALRM|26|종료|가상 타이머 종료|
  |SIGPROF|27|종료|프로파일 타이머 종료|
  |SIGWINCH|28|무시|윈도우 크기 변화|
  |SIGIO|29|종료|비동기식 이벤트로 발생|
  |SIGPOLL|SIGIO|종료|SIGIO와 동일|
  |SIGPWR|30|무시|전원 중단/재시작|
  |SIGSYS|31|코어 덤프|잘못된 시스템 호출|
  |SIGUNUSED|31|무시|향후 사용을 위해 예약된 번호|

## 8.3 시그널 보내기
### 8.3.1 시그널 보내기
#### 시그널 보내기: kill(2)
```C
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid, int sig);
```
- pid: 시그널을 받을 프로세스의 PID
- sig: 지정한 프로세스에 보내는 시그널 - 0 지정시 시그널을 보내지 않고 오류 확인
#### kill(2) 인자 pid
- 0보다 큰 수: pid로 지정한 프로세스에 시그널을 보냄
- -1이 아닌 음수: PGID에 속하고 시그널을 보낼 권한이 있는 모든 프로세스에 시그널을 보냄
- 0: 송신측 프로세스 PGID에 속하는 모든 프로세스에 시그널을 보냄(특수한 프로세스(스케줄러 등)는 제외)
- -1: 송신측 프로세스의 유효 사용자 ID가 root가 아닌 경우 특수한 프로세스를 제외하고 송신측 프로세스의 실제 사용자 ID가 유효 사용자 ID와 같은 모든 프로세스에 시그널을 보냄
#### 예제: 시그널 보내기(kill(2))
- test.c
    ```C
    #include<sys/types.h>
    #include<unistd.h>
    #include<signal.h>
    #include<stdio.h>

    int main(void){
        printf("before SIGCONT signal to parent\n");
        kill(getppid(), SIGCONT);
        printf("before SIGQUIT signal to me\n");
        kill(getpid(), SIGQUIT);
        printf("after SIGQUIT signal\n");
    }
    ```
- demo
    ```
    $ ./test
    before SIGCONT signal to parent
    before SIGQUIT signal to me
    끝내기 (코어 덤프됨)
    ```
#### 시그널 보내기: raise(3)
```C
#include<signal.h>
int raise(int sig);
```
- 호출한 프로세스에 인자로 지정된 시그널을 보냄
- 시그널 핸들러 호출시 핸들러 수행 종료까지 리턴하지 않음
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 시그널 보내기: abort(3)
```C
#include<stdlib.h>
void abort(void);
```
- 호출한 프로세스에 SIGABRT 시그널을 보냄
- 프로세스를 비정상 종료시키고 코어 덤프 파일 생성
- 최소 해당 프로세스가 연 파일을 모두 닫음

## 8.4 시그널 기본 처리
### 8.4.1 시그널 핸들러 지정
#### 시그널 핸들러 지정: signal(3)
```C
#include<signal.h>
typedef void(*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```
- signum: 시그널 핸들러로 처리할 시그널
- handler: 시그널 핸들러 이름
- SIGKILL, SIGSTOP을 제외하고 지정 가능
#### signal(3) 인자 handler
- 아래 세 가지 중 하나 설정
- 시그널 핸들러 주소
- SIG_IGN: 시그널을 무시하도록 지정
- SIG_DFL: 시그널의 기본 처리 방법을 수행하도록 지정
#### 예제: 시그널 핸들러 지정(signal(3))
- test.c
    ```C
    #include<unistd.h>
    #include<signal.h>
    #include<stdlib.h>
    #include<stdio.h>

    void test(int signo){
        printf("signal handler signum: %d\n", signo);
        psignal(signo, "received signal");
    }

    int main(void){
        void (*hand)(int);
        hand = signal(SIGINT, test);
        if(hand == SIG_ERR){
            perror("signal");
            exit(1);
        }
        printf("wait 1st Ctrl + C: SIGINT\n");
        pause();
        printf("after 1st signal handler\n");
        printf("wait 2nd Ctrl + C: SIGINT\n");
        pause();
        printf("after 2nd signal handler\n");
    }
    ```
- demo
    ```
    $ ./test
    wait 1st Ctrl + C: SIGINT
    ^C
    signal handler signum: 2
    received signal: Interrupt
    after 1st signal handler
    wait 2nd Ctrl + C: SIGINT
    ^C
    signal handler signum: 2
    received signal: Interrupt
    after 2nd signal handler
    ```
- pause(2): 시그널이 입력될 때까지 대기
#### 시그널 핸들러 지정: sigset(2)
```C
#include<signal.h>
sighandler_t sigset(int sig, sighandler_t disp);
```
- sig: 시그널 핸들러로 처리할 시그널
- disp: 시그널 핸들러 이름
- 리눅스: 사용을 권장하지 않음
- 솔라리스: signal(2)과 달리 한번 호출된 후 기본 동작으로 재설정하지 않음

## 8.5 시그널 집합
### 8.5.1 시그널 집합
#### 시그널 집합
- 시그널 집합: 시그널 설정에 대한 비트 마스크
- 0: 시그널 설정되지 않음
- 1: 시그널 설정됨
#### 구조체 sigset_t
```C
typedef struct{
    unsigned long __val[_NSIG_WORDS];
}sigset_t;
```
### 8.5.2 시그널 집합 처리 함수
#### 시그널 집합 비우기: sigemptyset(3)
```C
#include<signal.h>
int sigemptyset(sigset_t* set);
```
- 시그널 집합의 모든 비트를 0으로 설정
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 시그널 집합에 모든 시그널 설정: sigfillset(3)
```C
#include<signal.h>
int sigfillset(sigset_t* set)
```
- 시그널 집합의 모든 비트를 1로 설정
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 시그널 집합에 시그널 설정 추가: sigaddset(3)
```C
#include<signal.h>
int sigaddset(sigset_t* set, int signum);
```
- 인자로 지정한 시그널에 대한 비트를 1로 설정
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 시그널 집합에서 시그널 설정 삭제: sigdelset(3)
```C
#include<signal.h>
int sigdel(sigset_t* set, int signum);
```
- 인자로 지정한 시그널에 대한 비트를 0으로 설정
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 시그널 집합에 설정된 시그널 확인: sigismember(3)
```C
#include<signal.h>
int sigismember(const sigset_t* set, int signum);
```
- 인자로 지정한 시그널에 대한 설정(비트) 리턴
#### 예제: 시그널 집합 처리(sigemptyset(3), sigaddset(3), sigismember(3))
- test.c
    ```C
    #include<signal.h>
    #include<stdio.h>

    int main(void){
        sigset_t st;
        sigemptyset(&st);
        sigaddset(&st, SIGINT);
        //sigaddset(&st, SIGQUIT);
        printf("SIGINT: %d\n", sigismember(&st, SIGINT));
        printf("SIGQUIT: %d\n", sigismember(&st, SIGQUIT));
    }
    ```
- demo
    ```
    $ ./test
    SIGINT: 1
    SIGQUIT: 0
    ```

## 8.6 sigaction( ) 함수의 활용

## 8.7 알람 시그널

## 8.8 기타 시그널 처리 함수
