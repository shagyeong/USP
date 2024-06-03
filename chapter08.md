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
### 8.1 개요
### 8.2 시그널의 개념
### 8.3 시그널 보내기
### 8.4 시그널 기본 처리
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
## 8.3 시그널 보내기
## 8.4 시그널 기본 처리
## 8.5 시그널 집합
## 8.6 sigaction()함수의 활용
## 8.7 알람 시그널
## 8.8 기타 시그널 처리 함수


### 8.3 시그널 보내기
* 322 : 시그널 보내기 : kill(2)
* 324 : 시그널 보내기 : raise(3)
* 324 : 시그널 보내기 : abort(3)
### 8.4 시그널 기본 처리
* : 325 시그널 핸들러 지정 : signal(3)
* : 330 시그널 핸들러 지정 : sigset(3)
### 8.5 시그널 집합
* 333 : 시그널 집합 비우기 : sigemptyset(3)
* 333 : 시그널 집합에 모든 시그널 설정 : sigfillset(3)
* 334 : 시그널 집합에 시그널 설정 추가 : sigaddset(3)
* 334 : 시그널 집합에서 시그널 설정 삭제 : sigdelset(3)
* 334 : 시그널 집합에 설정된 시그널 확인 : sigismember(3)
### 8.6 sigaction()함수의 활용
* 339 : sigaction(2)
* 345 : 시그널 발생 원인 출력 : psiginfo(3)
### 8.7 알람 시그널
* 347 : 알람 시그널 생성 : alarm(2)
* 349 : 타이머 정보 검색 : getitimer(2)
* 350 : 타이머 설정 : setitimer(2)
### 8.8 기타 시그널 처리 함수
* 353 : 시그널 정보 출력 : psignal(3)
* 353 : 시그널 정보 출력 : strsignal(3)
* 354 : 시그널 블로킹과 해제 : sighold(3), sigrelse(3)
* 355 : 시그널 집합 블로킹과 해제 : sigprocmask(2)
* 357 : 시그널 대기 : pause(2)
* 358 : 시그널 대기 : sigpause(3)
* 358 : 시그널 기다리기 : sigsuspend(2)
* 360 : 시그널 보내기 : sigsend(2)
* 361 : 시그널 무시 처리 : sigignore(3)