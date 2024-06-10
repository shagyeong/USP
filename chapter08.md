# 8장 시그널
### 학습 목표
* 시그널의 기본 개념을 이해한다.
* 시그널을 보내고 받아서 처리할 수 있다.
* 시그널 집합의 개념과 사용 방법을 이해한다.
* sigaction() 함수를 사용해 시그널을 처리할 수 있다.
* 알람 시그널을 처리할 수 있다.
* 그 외 시그널 처리 함수를 사용할 수 있다.
### 중요 개념
* 8.1 개요 : 
* 8.2 시그널의 개념 : 
* 8.3 시그널 보내기 : 
* 8.4 시그널 기본 처리 : 
* 8.5 시그널 집합 : 
* 8.6 sigaction()함수의 활용 : 
* 8.7 알람 시그널 : 
* 8.8 기타 시그널 처리 함수 : 

## 예제 명세
### 8.3 시그널 보내기
* 323 : 시그널 보내기(kill(2))
### 8.4 시그널 기본 처리
* 327 : 시그널 핸들러 지정(signal(3))
* 330 : 시그널 핸들러 지정(sigset(3))
### 8.5 시그널 집합
### 8.6 sigaction()함수의 활용
### 8.7 알람 시그널
### 8.8 기타 시그널 처리 함수

## 8.1 개요
### 시그널(signal)
* **시그널** : 프로세스에 뭔가 발생했음을 알리는 간단한 메시지를 비동기적으로 보내는 것
* 시그널은 **소프트웨어 인터럽트**임
* 시그널 발생
    * 예외적 상황(0으로 나누기 등)이 발생하는 경우
    * 프로세스가 함수를 통해 다른 프로세스에 시그널을 보내는 경우
* 전달 메시지는 미리 정의된 상수를 사용함
### 시그널 보내기 함수
```C
int kill(pid_t pid, int sig);
int raise(int sig);
void abort(void);
```
### 시그널 핸들러 지정 함수
```C
sighandler_t signal(int signum, sighandler_t handler);
sighandler_t sigset(int sig, sighandler_t disp);
```
* 프로세스의 기본 시그널 처리 : 프로세스 종료
* 프로세스 종료 전 작업이 남아 있거나 특정 시그널을 종료하지 않고자 하는 경우 시그널을 처리하는 함수를 지정할 수 있음
* **시그널 핸들러(signal hander)** : (위 함수에 의해 지정되는)시그널을 처리하는 함수
### 시그널 집합 함수
```C
int sigemptyset(sigset_t* set);
int sigfillset(sigset_t* set);
int sigaddset(sigset_t* set, int signum);
int sigdelset(sigset_t* set, int signum);
int sigismember(const sigset_t* set, int signum);
```
* POSIX 표준에서 복수의 시그널 처리 가능
* **시그널 집합(signal set)** : 복수의 시그널을 처리하기 위해 도입한 개념
### 시그널 제어 함수
```C
int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact); //시그널 제어
void psiginfo(const siginfo_t* pinfo, const char* s); //시그널 발생 원인 출력
```
* 플래그를 설정해 시그널 처리 과정 제어 가능
### 알람 시그널 함수
```C
//알람 시그널
unsigned int alarm(unsigned int seconds);
//인터벌 타이머
int getitimer(int which, struct itimerval* curr_value);
int setitimer(int which, const struct itimerval* value, struct itimerval* ovalue);
```
* **알람 시그널(alarm signal)** : 일정 시간 경과 후 자동으로 시그널이 발생하도록 함
### 기타 시그널 함수
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
### 8.2.1 시그널의 발생
* 시그널의 발생
    * 0으로 나누기 등 프로그램에서 예외적인 상황이 발생하는 경우
    * 프로세스가 함수를 사용해 다른 프로세스에 시그널을 보내는 경우
    * 사용자가 인터럽트 키(Ctrl + c 등)를 입력한 경우
* 시그널은 비동기적으로 발생하며 리눅스 OS가 프로세스에 전달함
* 시그널은 소프트웨어 인터럽트임
### 8.2.2 시그널 처리 방법
#### 기본 동작(default action) 수행
* 각 시그널에는 기본동작이 지정되어 있음
* 프로세스 종료
* 프로세스 수행 일시 중지(suspend)
* 프로세스 재시작(resume)
* ...
#### 시그널 무시
* 프로세스가 시그널을 무시하기로 지정하면 시스템은 프로세스에 시그널을 전달하지 않음
#### 지정된 함수 호출
* **시그널 핸들러(signal handler)** : 시그널 처리를 위해 함수를 미리 지정하는 함수
* 시그널을 받으면 기존 처리 작업을 중지하고 시그널 핸들러를 호출
* 시그널 핸들러 동작 완료 후 기존 처리 작업을 계속 수행
#### 시그널 블록
* **블로킹** : 특정 부분이 실행되는 동안 시그널이 발생되지 않도록 하는 것
* 블로킹된 시그널은 **큐에 쌓여 있다가** 시그널 블록이 해제되면 전달됨
### 8.2.3 시그널의 종류
* <signal.h>에 정의되어 있음
* 코어 덤프(core dump) : 코어 파일을 만들고 종료
* |시그널|번호|기본 처리|발생 요건|
  |---|---|---|---|
  |SIGHUB|1|종료|행업으로 터미널과 연결이 끊어졌을 때 발생
  |SIGINT|2|종료|사용자가 인터럽트로 Ctrl + C 입력시 발생
  |SIGQUIT|3|코어 덤프|사용자가 종료신호로 Ctrl + \ 입력시 발생
  |SIGILL|4|코어 덤프|잘못된 명령 사용
  |SIGTRAP|5|코어 덤프|추적(trace)이나 브레이크 지점(break point)에서 트랩 발생
  |SIGABRT|6|코어 덤프|abort()에 의해 발생
  |SIGIOT|6|코어 덤프|SIGARBT와 동일
  |SIGBUS|7|코어 덤프|버스 오류로 발생
  |SIGFPE|8|코어 덤프|산술 연산 오류로 발생
  |SIGKILL|9|종료|강제 종료로 발생
  |SIGUSR1|10|종료|사용자가 정의해 사용하는 시그널 1
  |SIGSEGV|11|코어 덤프|세그먼테이션 오류로 발생
  |SIGUSR2|12|종료|사용자가 정의해 사용하는 시그널 2
  |SIGPIPE|13|종료|잘못된 파이프 처리로 발생
  |SIGALRM|14|종료|alarm()에 의해 발생
  |SIGTERM|15|종료|소프트웨어 종료로 발생
  |SIGSTKFLT|16|종료|보조 프로세서의 스택 오류로 발생(리눅스에서는 지원 안 함)
  |SIGCHLD|17|무시|자식 프로세스의 상태가 바뀌었을 때 발생
  |SIGCONT|18|무시|중지된 프로세스를 재시작할 때 발생
  |SIGSTOP|19|중지|중지(stop) 시그널 - SIGCONT을 받을 때 까지 프로세스 수행 중단
  |SIGTSTP|20|중지|사용자가 Ctrl + z로 중지시킬 때 발생
  |SIGTTIN|21|중지|터미널 입력을 기다리기 위해 중지시킬 때 발생
  |SIGTTOU|22|중지|터미널 출력을 위해 중지시킬 때 발생
  |SIGURG|23|무시|소켓에 긴급한 상황이 생기면 발생
  |SIGXCPU|24|코어 덤프|CPU 시간 제한을 초과할 때 발생
  |SIGXFSZ|25|코어 덤프|파일 크기 제한을 초과할 때 발생
  |SIGVTALRM|26|종료|가상 타이머가 종료할 때 발생
  |SIGPROF|27|종료|프로파일 타이머가 종료할 때 발생
  |SIGWINCH|28|무시|윈도우 크기가 바뀌었을 때 발생
  |SIGIO|29|종료|비동기식 입출력 이벤트로 발생
  |SIGPOLL|SIGIO|종료|SIGIO와 동일
  |SIGPWR|30|무시|전원이 중단되거나 재시작할 때 발생
  |SIGSYS|31|코어 덤프|잘못된 시스템 호출로 발생
  |SIGUNUSED|31|무시|향후 사용을 위해 예약된 번호

## 8.3 시그널 보내기
### 시그널 보내기 : kill(2)
```C
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid, int sig);
```
* 인자 설명
    * pid : 시그널을 받을 프로세스의 PID
    * sig : 보낼 시그널
* pid
    * 0보다 큰 수 : pid로 지정한 프로세스에 시그널을 보냄
    * -1이 아닌 음수 : 절대값을 취해 PGID에 해당하며 시그널을 보낼 권한이 있는 모든 프로세스에 시그널을 보냄
    * 0 : 특별한 프로세스(스케줄러 등)를 제외하고 시그널을 보내는 프로세스의 PGID와 같은 PGID를 갖는 모든 프로세스에 시그널을 보냄
    * -1 : 시그널을 보내는 프로세스의 EUID가 root(수퍼 유저)가 아니면 특별한 프로세스를 제외하고 프로세스의 RUID가 시그널을 보내는 프로세스의 EUID와 같은 모든 프로세스에게 시그널을 보냄
### 예제 323 : 시그널 보내기(kill(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

int main(void){
    printf("before SIGCONT signal to parent\n"); //무시
    kill(getppid(), SIGCONT);
    printf("before SIGQUIT signal to me\n"); //코어 덤프
    kill(getpid(), SIGQUIT);
    printf("affter SIGQUIT signal\n");
}
```
```
$ sh test.sh
before SIGCONT signal to parent
before SIGQUIT signal to me
Quit (core dumped)
```
### 시그널 보내기 : raise(3)
```C
#include<signal.h>
int raise(int sig);
```
* 호출한 프로세스에 인자로 지정한 시그널을 보냄
* 시그널 핸들러가 호출되면 시그널 핸들러의 수행이 끝날 때 까지 리턴하지 않음
* 성공시 : 0 리턴
* 실패시 : -1 리턴
### 시그널 보내기 : abort(3)
```C
#include<stdlib.h>
void abort(void);
```
* 호출한 프로세스에 SIGABRT 시그널을 보냄
    * 프로세스를 비정상적으로 종료시키고 코어 덤프 파일을 생성
    * 최소한 해당 프로세스가 연 파일은 모두 닫음
* raise(SIGABRT)와 동작이 같지만 프로세스를 종료시키므로 리턴하지 않음

## 8.4 시그널 기본 처리
### 개요
#### 시그널에 대한 기본 처리
* 프로세스 종료
* 프로세스 종료 전 처리할 작업이 남아있거나 종료하지 않으려면 시그널 핸들러를 지정할 수 있음
#### 시그널 핸들러(signal handler)
* **시그널 핸들러** : 시그널을 받을 때 수행할 함수
* 시그널 붙잡기(catching a signal) : 시그널을 확인해 처리하는 일
### 시그널 핸들러 지정 : signal(3)
#### 함수 원형
```C
#include<signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```
* 성공시 : 시그널 핸들러의 주소 리턴
* 실패시 : SIG_ERR 리턴
#### signum
* signum : 시그널 핸들러로 처리하려는 시그널
* SIGKILL, SIGSTOP 시그널을 제외한 모든 시그널을 지정할 수 있음
#### handler
* handler : 시그널 핸들러의 이름
* 다음 세 가지 중 하나를 설정해야 함
    * 시그널 핸들러 주소
    * SIG_IGN : 시그널을 무시하도록 설정
    * SIG_DFL : 시그널의 기본 처리 방법을 수행하도록 지정
* 시그널 핸들러 리턴 : void(리턴값을 받아서 처리할 수가 없음)
#### 시스템별 동작 방식
* handler가 함수 주소이고 signum이 SIGKILL이나 SIGSTOP이 아니라면 signal(3)의 동작은 시스템에 따라 달라짐
* 시스템 V
    * 시그널을 처리한 후 시그널 기본 처리 방법(SIG_DFL)으로 재설정함
    * 시그널 처리를 계속하려면 signal(3)를 호출해 시그널을 처리한 후 다시 signal(3)를 설정해야 함
* BSD
    * 시그널을 처리한 후 시그널 기본 처리 방법으로 재설정하지 않음
    * 시그널 핸들러가 계속 동작함
* 리눅스
    * signal(2) : 시스템 V 형식으로 동작
    * signal(3) : BSD 형식으로 동작(signal(2)를 호출하지 않고 sigaction(2)를 호출)
#### 예제 327 : 시그널 핸들러 지정(signal(3))
```C
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

void sighandler(int signo){
    printf("signal handler signum : %d\n", signo);
    psignal(signo, "recieved signal"); //8.8절에서 다루는 함수
}

int main(void){
    void (*hand)(int);
    hand = signal(SIGINT, sighandler); //SIGINT : Ctrl + C 인터럽트시 종료
    if(hand == SIG_ERR){
        perror("signal");
        exit(1);
    }
    printf("wait 1st Ctrl + C... : SIGINT\n");
    pause(); //pause(2) : 시그널이 입력될 때 까지 기다리는 함수
    printf("after 1st signal handler\n");
    printf("wait 2nd Ctrl + C... : SIGINT\n");
    pause();
    printf("after 2nd signal handler\n");
}
```
```
$ sh test.sh
wait 1st Ctrl + C... : SIGINT
^Csignal handler signum : 2
recieved signal: Interrupt
after 1st signal handler
wait 2nd Ctrl + C... : SIGINT
^Csignal handler signum : 2
recieved signal: Interrupt
after 2nd signal handler
```
### 330 시그널 핸들러 지정 : sigset(3)
#### 함수 원형
```C
#include<signal.h>
sighandler_t sigset(int sig, sighandler_t disp);
```
* 인자 구조가 signal(2)와 동일
* 리눅스에서 제공하지만 사용을 권장하지 않음
* 솔라리스 : 한 번 호출된 후 기본 동작으로 재설정하지 않음
#### 예제 330 : 시그널 핸들러 지정(sigset(3))
```C
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

void sighandler(int signo){
    printf("signal handler signal number : %d\n", signo);
    psignal(signo, "received signal");
}

int main(void){
    void (*hand)(int);
    hand = sigset(SIGINT, sighandler);
    if(hand == SIG_ERR){
        perror("sigset");
        exit(1);
    }
    printf("wait 1st Ctrl + C... : SIGINT\n");
    pause();
    printf("after 1st signal handler\n");
    printf("wait 2nd Ctrl + C... : SIGINT\n");
    pause();
    printf("after 2nd signal handler\n");
}
```
* 솔라리스에서 실행
## 8.5 시그널 집합
#### 시그널 집합 비우기 : sigemptyset(3)
#### 시그널 집합에 모든 시그널 설정 : sigfillset(3)
#### 시그널 집합에 시그널 설정 추가 : sigaddset(3)
#### 시그널 집합에서 시그널 설정 삭제 : sigdelset(3)
#### 시그널 집합에 설정된 시그널 확인 : sigismember(3)
## 8.6 sigaction()함수의 활용
#### sigaction(2)
#### 시그널 발생 원인 출력 : psiginfo(3)
## 8.7 알람 시그널
#### 알람 시그널 생성 : alarm(2)
#### 타이머 정보 검색 : getitimer(2)
#### 타이머 설정 : setitimer(2)
## 8.8 기타 시그널 처리 함수
#### 시그널 정보 출력 : psignal(3)
#### 시그널 정보 출력 : strsignal(3)
#### 시그널 블로킹과 해제 : sighold(3), sigrelse(3)
#### 시그널 집합 블로킹과 해제 : sigprocmask(2)
#### 시그널 대기 : pause(2)
#### 시그널 대기 : sigpause(3)
#### 시그널 기다리기 : sigsuspend(2)
#### 시그널 보내기 : sigsend(2)
#### 시그널 무시 처리 : sigignore(3)