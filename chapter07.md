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
$ ./test
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
$ ./test
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
### 7.3.0 개요
#### 종료 상태
- 종료 상태: 프로세스 종료시 어떻게 종료되었는지 나타낸다
- 자식 프로세스는 부모 프로세스에 종료 상태값을 리턴할 수 있다
- 0: (일반적으로) 프로세스 정상 종료를 의미 - eixt(0) 또는 main()에서 0 리턴
- 1: 0이 아닌 종료 상태값은 오류 발생을 의미
#### 주요 함수
- exit(3)
- atexit(3)
- _exit(2)
### 7.3.1 프로세스 종료
#### 프로세스 종료: exit(3)
```C
#include<stdlib.h>
void exit(int status);
```
- 프로세스를 종료시키고 부모 프로세스에 종료 상태값 전달
- atexit(3)으로 예약한 함수를 지정된 순서와 역순으로 모두 실행
    - atexit(3)으로 예약된 함수에서 문자 발생시 exit(3)의 나머지 과정도 수행되지 않음
- 프로세스가 사용중이던 입출력 스트림 반납
- tmpfile(3)으로 생성한 임시 파일 삭제
- _exit(2) 호출 - 프로세스가 사용하던 모든 자원 반납
#### exit(3)과 _exit(2)의 구분
- exit(3): C 라이브러리 함수(3) - *시스템에 독립적*인 기능만 수행 
- _exit(2): 시스템 호출(2) - 시스템과 관련된 기능은 시스템에서 처리하도록 함
#### 프로그램 종료시 수행할 작업 예약: atexit(3)
```C
#include<stdlib.h>
int atexit(void (*function)(void));
int on_exit(void (*function)(int, void*), void* arg);
```
- 프로세스 종료시 수행할 기능 예약
- atexit(3): 인자와 리턴값이 없는 함수
- on_exit(3): 예약할 함수의 인자와 포인터를 인자로 받음
#### 예제: 프로세스 종료(exit(3), atexit(3))
```C
#include<stdlib.h>
#include<stdio.h>

void cleanse1(void){
    printf("cleanse1 called\n");
}
void cleanse2(int status, void* arg){
    printf("cleanse2 called: %ld\n", (long)arg);
}
int main(void){
    atexit(cleanse1);
    on_exit(cleanse2, (void*)20);
    exit(0);
}
```
```
$ ./test
cleanse2 called: 20
cleanse1 called
```
- atexit(3): 인자와 리턴이 없는 함수를 예약한 것을 확인
- on_exit(3): 인자가 지정된 함수를 예약한 것을 확인
- 실제로는 프로세스 종료시 *반드시 수행해야할 작업*을 지정해야 함 - 로그 남기기, 관리자에게 메시지 전송, 데이터 전송 등
#### 프로그램 종료: _exit(2)
```C
#include<unistd.h>
void _exit(int status);
```
- 시스템 자원 정리
    - 모든 fd close
    - 부모 프로세스에 종료 상태를 알림
    - 자식 프로세스에 SIGHUP 시그널을 보냄
    - 부모 프로세스에 SIGCHLD 시그널을 보냄
    - 프로세스간 통신에 사용한 자원 반납
- 일반적으로 프로그램에서 직접 호출하지 않고 exit(3) 내부에서 호출

## 7.4 exec 함수군 활용
### 7.4.1 exec 함수군
#### exec 함수군
- exec 함수군: 함수명이 exec로 시작하는 함수들
- 명령, 실행 파일을 실행할 수 있다
- *fork(2)와 연계해 자식 프로세스가 새로운 프로그램을 실행하도록 함*
- 인자로 받은 다른 프로그램을 자신을 호출한 메모리에 덮어씀
- 프로세스가 수행 중이던 기존 프로그램은 중지되어 없어지고 새로운 프로그램이 실행됨
- 성공시 리턴값 없음(프로세스 자체가 바뀜)
#### exec letters
- exec: execute
- e(environment variables): 환경 변수에 대한 포인터가 새로운 프로세스 이미지로 명시적으로 전달
- l(list): 명령행 인자가 리스트로 전달
- p(PATH environment variable): 실행 파일 탐색을 위해 경로 환경 변수 PATH사용
- v(vector): 명령행 인자가 포인터의 벡터로 전달
#### exec 함수군
```C
#include<unistd.h>
int execl(const char* pathname, const char* arg, ... /* (char*) NULL */);
int execlp(const char* file, const char* arg, ... /* (char*) NULL */);
int execle(const char* pathname, const char* arg, ... /* (char*) NULL, char* const envp[] */);
int execv(const char* pahtname, char* const argv[]);
int execvp(const char* file, char* const argv[]);
int execvpe(const char* file, char* const argv[], char* const envp[]);
```
#### execl
```C
int execl(const char* pathname, const char* arg, ... /* (char*) NULL */);
```
- pathname: 실행할 파일의 상대/절대 경로
- arg0: 실행파일명 지정
- 널 포인터: 인자의 끝을 의미
#### execlp
```C
int execlp(const char* file, const char* arg, ... /* (char*) NULL */);
```
- file: 실행 파일 지정
- 널 포인터: 인자의 끝을 의미
- 접미사 *p*: 호출한 프로세스의 (환경변수 PATH에 정의된)검색 경로에서 실행 파일을 찾음을 의미
#### execle
```C
int execle(const char* pathname, const char* arg, ... /* (char*) NULL, char* const envp[] */);
```
- pathname: 실행할 파일의 상대/절대 경로
- envp: 환경변수 포인터 배열(마지막에 NULL을 지정해야 함)
- 널 포인터: 인자의 끝을 의미
#### execv
```C
int execv(const char* pahtname, char* const argv[]);
```
- pathname: 실행할 파일의 상대/절대 경로
- argv: 인자 포인터 배열(마지막에 NULL을 지정해야 함)
#### execvp
```C
int execvp(const char* file, char* const argv[]);
```
- file: 실행 파일 지정
- 접미사 *p*: 호출한 프로세스의 (환경변수 PATH에 정의된)검색 경로에서 실행 파일을 찾음을 의미
- argv: 인자 포인터 배열(마지막에 NULL을 지정해야 함)
#### execvpe
```C
int execvpe(const char* file, char* const argv[], char* const envp[]);
```
- pathname: 실행할 파일의 상대/절대 경로
- argv: 인자 포인터 배열(마지막에 NULL을 지정해야 함)
- envp: 환경변수 포인터 배열(마지막에 NULL을 지정해야 함)
### 7.4.2 exec 함수군 활용
#### 예제: 명령 바꿔 실행(execlp(3))
```C
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    printf("before execlp\n");
    //int execlp(const char* file, const char* arg, ... /* (char*) NULL */);
    if(execlp("ls", "ls", "-a", (char*) NULL) == -1){
        perror("execlp");
        exit(1);
    }
    printf("after execlp\n"); //실행되지 않음
}
```
```
$ ./test
before execlp
.  ..  test  test.c  test.sh
```
#### 예제: 명령 바꿔 실행(execv(3))
```C
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* argv[3];
    printf("before execv\n");
    argv[0] = "ls";
    argv[1] = "-a";
    argv[2] = NULL;
    if(execv("/usr/bin/ls", argv) == -1){
        perror("execv");
        exit(1);
    }
    printf("after execv\n");
}
```
```
$ ./test
before execv
.  ..  test  test.c  test.sh
```
#### 예제: 명령 바꿔 실행(execve(3))
- test.c
    ```C
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        char* argv[3];
        argv[0] = "arg.out";
        argv[1] = "100";
        argv[2] = NULL;

        char* envp[2];
        envp[0] = "MYENV=test";
        envp[1]=NULL;

        printf("before execve\n");
        if(execve("./arg.out", argv, envp) == -1){
            perror("execve");
            exit(1);
        }
        printf("after execve\n");
    }
    ```
- arg.c
    ```C
    #include<stdio.h>

    int main(int argc, char** argv, char** envp){
        int n;
        char** env = envp;

        printf("arg.c main\n");
        printf("argc = %d\n", argc);
        for(n = 0; n < argc; n++){printf("argv[%d] = %s\n", n , argv[n]);}
        while(*env){printf("%s\n", *env);env++;}
    }
    ```
- demo
    ```
    ./test
    before execve
    arg.c main
    argc = 2
    argv[0] = arg.out
    argv[1] = 100
    MYENV=test
    ```
### 7.4.3 exec 함수군과 fork(2)
#### 개요
- 자식 프로세스에서 exec 함수군을 호출해 부모 프로세스로부터 복사한 다른 명령이나 프로그램 실행 가능
#### 예제: 부모 프로세스와 자식 프로세스 분리(fork(2), execlp(3))
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
            if(execlp("ls", "ls", "-a", (char*) NULL) == -1){
                perror("execlp");
                exit(1);
            }
            exit(0);
            break;
        default:
            printf("parent process\n");
            printf("pid: %d\n", (int)getpid());
            break;
    }
}
```
```
$ ./test
parent process
pid: 30391
child process
.  ..  arg.c  arg.out  test  test.c  test.sh
```

## 7.5 프로세스 동기화
