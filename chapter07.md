# 7장 프로세스 생성과 실행
## 7.1 개요
### 7.1.1 프로세스 생성 함수
- 프로그램 내부에서 다른 프로그램을 실행하여 프로세스를 생성하는 경우
```C
int system(const char* command); //프로그램 실행
pid_t fork(void);   //프로세스 생성
pid_t vfork(void);  //프로세스 생성
```
### 7.1.2 프로세스 종료 함수
- 종료 상태: 프로세스가 어떻게 종료되었는지 나타냄
- 자식 프로세스는 부모 프로세스에 종료 상태값을 리턴할 수 있다
- 0: 일반적으로 정상 종료를 의미
- 0이 아닌 값: 오류 발생을 의미
```C
void exit(int status);  //프로세스 종료
void _exit(int status); //프로세스 종료
int atexit(void (*function)(void)); //종료시 수행할 작업 지정
int on_exit(void (*fucntion)(int, void*), void* arg);   //종료시 수행할 작업 지정
```
### 7.1.3 exec 함수군
- 인자로 받은 다른 프로그램을 자신을 호출한 프로세스의 메모리에 덮어씀
- 기존 프로그램은 중지되어 업어짐
- 새로 덮어쓴 프로그램 실행
- fork(2)와 연결해 자식 프로세스가 새로운 프로그램을 실행하도록 함
```C
/* 프로세스 실행 */
int execl(const char* pathname, const char* arg, ... /* (char*) NULL */);
int execlp(const char* file, const char* arg, ... /* (char*) NULL */);
int execle(const char* pathname, const char* arg, ... /* (char*) NULL, char* const envp[] */);
int execv(const char* pahtname, char* const argv[]);
int execvp(const char* file, char* const argv[]);
int execvpe(const char* file, char* const argv[], char* const envp[]);
```
### 7.1.4 프로세스 동기화 함수
- 좀비 프로세스를 방지하기 위해 부모 프로세스와 자식 프로세스 동기화 필요
```C
pid_t wait(int* wstatus);//프로세스 동기화
pid_t watitpid(pid_t pid, int* wstatus, int options);//특정 자식 프로세스와 동기화
int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options);//특정 자식 프로세스와 동기화
```

## 7.2 프로세스 생성
### 7.2.1 프로그램 실행: system(3)
#### 프로그램 실행: system(3)
```C
#include<stdlib.h>
int system(const char* command);
```
- 기존 명령/실행 파일명을 인자로 받아 셸에 전달
- 셸이 내부적으로 프로세스를 생성해 인자로 받은 명령을 실행
- 해당 명령이 끝날 때까지 기다렸다가 종료 상태 리턴
- 비효율적(명령을 실행하기 위해 셸까지 동작시킴)
#### 예제: 프로그램 실행: system(3)
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int ret;
    ret = system("ls > test.txt");
    printf("ret value: %d\n", ret);
    ret = system("./hello");
    printf("ret value: %d\n", ret);
}
``````
$ sh test.sh
ret value: 0
hello
ret value: 0
$ cat test.txt
hello
hello.c
test
(...)
```
- 기존 명령어 ls(1)에 대한 리디렉션을 실행한 것을 확인
- 로컬에 존재하는 실행파일(hello.out)이 실행된 것을 확인
### 7.2.2 프로세스 생성
#### 프로세스 생성
- fork(2): 부모 프로세스를 (거의) 그대로 복제해 새로운 프로세스 생성(그림 7.2.2)
- 자식 프로세스의 메모리 공간: 부모 프로세스의 메모리 공간을 그대로 복제
- 부모 프로세스: fork(2)를 호출한 프로세스
- 자식 프로세스: fork(2)가 생성한 새로운 프로세스
- 처리 순서: 시스템 스케줄링 정책을 따름(어느 것이 먼저 실행 될 지는 알 수 없음)
#### 리턴
- 자식 프로세스에 대한 리턴: 0
- 부모 프로세스에 대한 리턴: 자식 프로세스의 PID
#### 상속 속성
- 실제 사용자 ID(RUID)/유효 사용자 ID(EUID)
- 실제 그룹 ID(RGID)/유효 그룹 ID(EGID)
- 환경 변수
- 열린 fd
- 시그널 처리 설정
- setuid, setgid 설정
- 현재 작업 디렉터리
- umask 설정값
- 사용 가능한 자원 제한
#### 부모 프로세스와 다른 특성
- PID(자식 프로세스는 새로 할당된 PID를 가짐)
- PPID(부모 프로세스의 PID)
- 부모 프로세스가 open한 fd에 대한 복사본을 갖고있음 - 읽기/쓰기시 유의
- 부모 프로세스가 설정한 프로세스 잠금, 파일 잠금, 기타 메모리 잠금 등은 상속하지 않음
- 처리되지 않은 시그널은 상속되지 않음
- 자식 프로세스의 tms 구조체 값은 0으로 초기화
#### 프로세스 생성: fork(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t fork();
```
- 성공시: 부모 프로세스에 자식 PID 리턴, 자식 프로세스에 0 리턴
- 실패시: 0 리턴
#### 예제: 프로세스 생성: fork(2)
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    pid_t pid;
    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            printf("child process\n");
            printf("pid: %d, ppid: %d\n", (int)getpid(), (int)getppid());
            break;
        default:
            printf("parent process\n");
            printf(
                "pid: %d, ppid: %d, child's pid: %d\n",
                (int)getpid(), (int)getppid(), (int)pid
            );
    }
}
```
```
$ sh test.sh
parent process
pid: 52105, ppid: 52099, child's pid: 52106
child process
pid: 52106, ppid: 52105
```
#### 프로세스 생성: vfork(2)
```C
#include<unistd.h>
pid_t vfork(void);
```
- 부모 프로세스의 메모리 공간을 모두 복사하지는 않는다
- exec 함수군과 연계시 효율적
- 버그 우려로 사용이 권장되지 않음

## 7.3 프로세스 종료

## 7.4 exec 함수군 활용

## 7.5 프로세스 동기화
