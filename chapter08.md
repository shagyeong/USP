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

## 8.3 시그널 보내기

## 8.4 시그널 기본 처리

## 8.5 시그널 집합

## 8.6 sigaction( ) 함수의 활용

## 8.7 알람 시그널

## 8.8 기타 시그널 처리 함수
