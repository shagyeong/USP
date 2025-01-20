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
- 시그널을 보낼수 있는 함수(kill(1) 등)를 이용해 프로세스에서 다른 프로세스로 시그널을 보내는 경우
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

## 8.4 시그널 기본 처리

## 8.5 시그널 집합

## 8.6 sigaction( ) 함수의 활용

## 8.7 알람 시그널

## 8.8 기타 시그널 처리 함수
