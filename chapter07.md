# 7장 프로세스 생성과 실행
### 학습 목표
* 프로세스를 생성할 수 있다.
* 프로세스를 종료할 수 있다.
* exec 함수군으로 새로운 프로그램을 실행할 수 있다.
* 프로세스를 동기화할 수 있다.
### 중요 개념
* 7.1 개요 : 
* 7.2 프로세스 생성 : 
* 7.3 프로세스 종료 : 
* 7.4 exec 함수군 활용 : 
* 7.5 프로세스 동기화 : 

## 예제 명세
### 7.2 프로세스 생성
* 281 : 프로그램 실행(system(3))
* 284 : 프로세스 생성(fork(2))
### 7.3 프로세스 종료
* 288 : 프로그램 종료(exit(3), atexit(3), on_exit(3))
### 7.4 exec 함수군 활용
* 292 : 명령을 바꿔 실행(execlp(3))
* 293 : 명령을 바꿔 실행(execv(3))
* 294 : 함수 호출(execve(3))
* 296 : 자식 프로세스에서 다른 프로그램 실행(fork(2), execlp(3))
### 7.5 프로세스 동기화
* 299 : 프로세스 동기화(wait(2))
* 302 : 특정 자식 프로세스 동기화(waitpid(2))
* 303 : 특정 자식 프로세스 동기화(waitid(2))

## 7.1 개요
### 프로세스 생성 함수
* 프로세스 생성
    * 명령행에서 직접 프로그램 실행
    * 프로그램 내부에서 다른 프로그램을 실행
```C
int system(const char* command); //프로그램 실행
pid_t fork(void);   //프로세스 생성
pid_t vfork(void);  //프로세스 생성
```
### 프로세스 종료 함수
* 종료 상태(exit status) : 리눅스에서 프로세스가 종료되었을 시 종료 상태 저장
* 자식 프로세스는 부모프로세스에 종료 상태값 리턴 가능
* 0 : (일반적으로) 정상적으로 종료됨
* 0이 아님 : 오류 발생
```C
void exit(int status);  //프로세스 종료
void _exit(int status); //프로세스 종료
int atexit(void (*function)(void)); //종료시 수행할 작업 지정
int on_exit(void (*fucntion)(int, void*), void* arg);   //종료시 수행할 작업 지정
```
### exec 함수군
* exec 함수군 : 자신을 호출한 프로세스의 메모리에 인자로 받은 프로그램을 덮어씀
* 프로세스 수행 중이던 기존 프로그램은 중지
* 새로 덮어쓴 프로그램이 실행됨
* fork(2)와 연결해 자식 프로세스가 새로운 프로그램을 실행하도록 할 때도 사용함
```C
/* 프로세스 실행 */
int execl(const char* pathname, const char* arg, ... /* (char*) NULL */);
int execlp(const char* file, const char* arg, ... /* (char*) NULL */);
int execle(const char* pathname, const char* arg, ... /* (char*) NULL, char* const envp[] */);
int execv(const char* pahtname, char* const argv[]);
int execvp(const char* file, char* const argv[]);
int execvpe(const char* file, char* const argv[], char* const envp[]);
```
### 프로세스 동기화 함수
* fork(2)로 자식 프로세스 생성시 부모/자식 프로세스는 순서에 관계없이 실행되고 실행을 마친 프로세스는 먼저 종료됨
* 좀비 프로세스(zombie process) 같은 불안정 상태의 프로세스 발생
* 이를 방지하기 위해 부모 프로세스와 자식 프로세스를 동기화해야 함
```C
pid_t wait(int* wstatus);//프로세스 동기화
pid_t watitpid(pid_t pid, int* wstatus, int options);//특정 자식 프로세스와 동기화
int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options);//특정 자식 프로세스와 동기화
```

## 7.2 프로세스 생성
### 7.2.1 system(3)로 프로그램 실행하기
#### 개요
* sysmtem(3)
    * 프로그램 내부에서 새로운 프로그램을 실행하는 가장 간단한 방법
    * 명령 실행을 위해 셸까지 동작시킴 - 비효율적
#### 프로그램 실행 : system(3)
```C
#include<stdlib.h>
int system(const char* command);
```
* 명령(1)이나 실행 파일명을 인자로 받아 셸에 전달
* 셸에서 내부적으로 프로세스를 생성해 인자로 받은 명령 실행
* 명령이 끝날 때 까지 기다렸다가 종료 상태를 리턴함
#### 예제 281 : 프로그램 실행(system(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    printf("exit status : %d\n", system("ps -ef | grep sshd > sshd.txt"));
}
```
```
$ sh test.sh
exit status : 0
$ cat sshd.txt
********    5328    5327  0 10:41 pts/0    00:00:00 sh -c ps -ef | grep sshd > sshd.txt
********    5330    5328  0 10:41 pts/0    00:00:00 grep sshd
```
### 7.2.2 프로세스 생성
#### 개요
* fork(2) : 부모 프로세스를 거의 그대로 복제해 새로운 프로세스 생성
* 부모 프로세스 : fork(2)를 호출한 프로세스
* 자식 프로세스 : fork(2)가 호출한 프로세스
* fork(2)가 리턴시 부모/자식 프로세스는 동시에 동작 - 실행 순서는 스케줄링에 따름
* 생성 과정
    * 부모 프로세스 : fork(2) 호출
    * fork(2) 모듈 : 새로운 프로세스 생성
    * fork(2) 모듈 : 메모리 공간 복사
    * fork(2) 모듈 : 리턴(부모 : 자식의 PID, 자식 : 0)
#### fork(2)의 특징
* fork(2)로 생성한 자식 프로세스의 메모리 공간 : 부모 프로세스의 메모리 공간을 복사해 만듦
* 상속받는 속성
    * RUID, EUID, RGID, EGID
    * 환경 변수
    * 열린 파일 기술자(같은 파일의 오프셋을 공유하는 상태이므로 읽기/쓰기시 주의 필요)
    * 시그널 처리 설정
    * setuid, setgid 설정
    * 현재 작업 디렉터리
    * umask 설정값
    * 사용 가능한 자원 제한
* 상속받지 않는 속성
    * PID, PPID
    * 부모 프로세스가 설정한 프로세스 잠금, 파일 잠금, 기타 메모리 잠금
    * 처리되지 않은 시그널은 상속되지 않음
    * 자식 프로세스의 tms 구조체 값은 0으로 초기화(프로세스 시간 측정 기준값이 새로 설정됨)
#### 프로세스 생성 : fork(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t fork(void);
```
* 성공시
    * 부모 프로세스 : 자식 프로세스의 PID
    * 자식 프로세스 : 0
* 실패시 : -1 리턴
#### 예제 284 : 프로세스 생성(fork(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    pid_t pid;

    switch(pid = fork()){
        case -1:
            printf("fork failed\n");
            exit(1);
            break;
        case 0://자식 프로세스
            printf("child process\n");
            printf("pid : %d, ppid : %d\n", (int)getpid(), (int)getppid());
            break;
        default://부모 프로세스
            printf("parent process\n");
            printf("pid : %d, ppid : %d\n", (int)getpid(), (int)getppid());
            break;
    }
    printf("end of fork\n");
}
```
```
$ sh test.sh
parent process
pid : 5744, ppid : 5738
end of fork
child process
pid : 5745, ppid : 5744
end of fork
```
* 부모의 PID, 자식의 PPID가 같은 것을 확인
#### 프로세스 생성 : vfork(2)
```C
#include<unistd.h>
pid_t vfork(void);
```
* fork(2)와 마찬가지로 새로운 프로세스를 생성함
* 부모 프로세스의 메모리 공간을 모두 복사하지는 않음
* exec 함수군을 사용해 새로운 작업 수행시 효율적
* 버그 발생 우려로 인해 사용을 추천하지 않음

## 7.3 프로세스 종료
### 개요
#### 종료 상태
* 종료 상태(exit status) : 리눅스는 프로세스가 종료되면 종료 상태를 저장
* 부모 프로세스는 저장된 종료 상태 정보를 통해 자식 프로세스가 어떻게 종료되었는지 알 수 있음
* 0 : (일반적으로) 정상적으로 종료되었음을 의미
* 1 : 오류 발생
* 다양한 상태값 : 프로그래머에 따라 어떻게 종료되었는지 나타내기도 함
#### 프로그램 종료 : exit(3)
```C
#include<stdlib.h>
void exit(int status);
```
* 프로세스를 종료시키고 부모 프로세스에 종료 상태값을 전달
* 이때 atexit(3)로 예약한 함수를 지정된 순서와 역순으로 모두 실행
    * 예약된 함수가 문제가 발생해 리턴하지 못할시 exit(3)의 나머지 과정도 수행되지 않음
* 프로세스가 사용 중이던 모든 표준 입출력 스트림의 데이터를 기록하고 닫음
* tmpfile(3)로 생성한 임시 파일을 삭제하고 _exit(2) 호출
* _exit(2) : 프로세스가 사용하던 모든 자원을 반납
    * C 표준 함수이므로 시스템에 독립적인 기능을 수행하고 시스템 관련 기능은 시스템 호출에서 처리하도록 해야 함
#### 프로그램 종료 : _exit(2)
```C
#include<unistd.h>
void _exit(int status);
```
* 일반적으로 직접 사용하지 않고 exit(3) 내부에서 호출함
* exit(3) : 시스템 독립적인 기능만 수행
* _exit(2) : exit(3) 내부에서 호출되어 시스템 관련된 기능 수행
    * 모든 파일 기술자를 닫음
    * 부모 프로세스에 종료 상태를 알림
    * 자식 프로세스에 SIGHUP 시그널을 보냄
    * 부모 프로세스에 SIGCHLD 시그널을 보냄
    * 프로세스간 통신에 사용된 자원을 반납
#### 프로그램 종료 시 수행할 작업 예약 : atexit(3), on_exit(3)
```C
#include<stdlib.h>
int atexit(void (*function)(void));
init on_exit(void (*function)(int, void*), void* arg);
```
* 프로세스가 종료할 때 수행할 기능 예약(로그 작성, 데이터 저장, ...)
* atexit(3) : 인자로 함수의 포인터를 받음
* on_exit(3) : 인자로 함수의 포인터와 함수의 인자의 포인터를 받음
* 예약할 수 있는 함수 개수
    * 여유 메모리에 따라 달라짐
    * sysconf(3)의 _SC_ATEXIT_MAX 항목으로 검색 가능
* 참고 : 솔라리스는 5.0부터 사용 불가, 리눅스는 가능
#### 예제 288 : 프로그램 종료(exit(3), atexit(3), on_exit(3))
```C
#include<stdlib.h>
#include<stdio.h>

void cleanse1(void){
    printf("cleanse1 is called\n");
}
void cleanse2(int status, void* arg){
    printf("cleanse2 is called : %ld\n", (long)arg);
}
int main(void){
    atexit(cleanse1);
    on_exit(cleanse2, (void*) 20);
    exit(0);
}
```
```
$ sh test.sh
cleanse2 is called : 20
cleanse1 is called
```

## 7.4 exec 함수군 활용
### 개요
* exec 함수군
    * 함수명이 exec로 시작하는 함수군
    * 인자로 받은 다른 프로그램을 자신을 호출한 프로세스의 메모리에 덮어씀
    * 호출한 프로세스 자체가 바뀌므로 성공시 리턴값이 없음
    * fork(2)와 연결해 자식 프로세스가 새로운 프로그램을 실행하도록 할 때 유용함
### 7.4.1 exec 함수군의 형태
```C
#include<unistd.h>
int execl(const char* pathname, const char* arg, ... /* (char*) NULL */);
int execlp(const char* file, const char* arg, ... /* (char*) NULL */);
int execle(const char* pathname, const char* arg, ... /* (char*) NULL, char* const envp[] */);
int execv(const char* pahtname, char* const argv[]);
int execvp(const char* file, char* const argv[]);
int execvpe(const char* file, char* const argv[], char* const envp[]);
```
* pahtname 또는 file에 지정한 명령이나 실행 파일을 실행
* arg, envp로 시작하는 인자를 pathname이나 file에 지정한 파일의 main()에 전달
* 각 함수는 경로명 지정/파일명 지정, 인자 전달 형태 등에 있어 차이가 있음
* letters
    * exec : execute
    * l : Command-line arguments are passed individually (a list) to the function.
    * p : Uses the PATH environment variable to find the file named in the file argument to be executed.
    * v : Command-line arguments are passed to the function as an array (vector) of pointers. - 명령행 인자를 포인터로 지정?
    * e : An array of pointers to environment variables is explicitly passed to the new process image.
* execl(3)
    * pathname에 지정한 경로명의 파일 실행
    * arg0 ~ argn을 인자로 전달
    * arg0 : 실행 파일명을 지정
    * 마지막 인자 : NULL 포인터 지정(인자의 끝을 의미)
* execlp(3)
    * file에 지정한 파일 실행
    * arg0 ~ argn을 인자로 전달
    * 이 함수를 호출한 프로세스의 검색 경로(환경 변수 PATH에 정의된 경로)에서 파일을 찾음
    * arg0 ~ argn은 포인터로 지정
    * 마지막 인자 : NULL 포인터 지정
* execle(3)
    * pathname에 지정한 경로명의 파일 실행
    * arg0 ~ argn, envp를 인자로 전달
    * envp : 새로운 환경 변수를 설정할 수 있음
        * envp는 포인터 배열임
    * 마지막 인자 : NULL 포인터 지정
* execv(3)
    * pathname에 지정한 경로명의 파일 실행
    * argv를 인자로 전달
        * argv는 포인터 배열임
    * 마지막 인자 : NULL 포인터 지정
* execvp(3)
    * file에 지정한 파일 실행
    * argv를 인자로 전달
    * 마지막 인자 : NULL 포인터 지정
* execvpe(3)
    * pathname에 지정한 경로명의 파일 실행
    * argv, envp를 인자로 전달
    * 마지막 인자 : NULL 포인터 지정
### 7.4.2 exec 함수군의 사용
#### 예제 292 : 명령을 바꿔 실행(execlp(3))
```C
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    printf("before exec function\n");
    if(execlp("ls", "ls", "-a", (char *) NULL) == -1){
        perror("execlp");
        exit(1);
    }
    printf("after exec function\n");
}
```
```
$ sh test.sh
before exec function
.  ..  .***  .******  *********.** (...)
```
* 프로세스 이미지가 바뀌어 execlp(3) 호출 이후 printf문이 실행되지 않음을 확인
#### 예제 293 : 명령을 바꿔 실행(execv(3))
```C
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* argv[3];
    printf("before exec function\n");
    argv[0] =  "ls";
    argv[1] =  "-a";
    argv[2] =  NULL;
    if(execv("/usr/bin/ls", argv) == -1){
        perror("execv");
        exit(1);
    }
    printf("after exec function\n");
}
```
```
$ sh test.sh
before exec function
.  ..  .***  .******  *********.** (...)
```
#### 예제 294 : 함수 호출(execve(3))
```C
//test.c
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* argv[3];
    char* envp[2];
    printf("before exec function\n");

    argv[0] = "testarg";
    argv[1] = "100";
    argv[2] = NULL;

    envp[0] = "TESTENV=test";
    envp[1] = NULL;

    if(execve("./testarg", argv, envp) == -1){
        perror("execve");
        exit(1);
    }

    printf("after exec function\n");
}
```
```C
//testarg.c
#include<stdio.h>

int main(int argc, char **argv, char **envp){
    int n;
    char **env = envp;
    printf("in testarg.c\n");

    printf("argc = %d\n", argc);
    for(n = 0; n < argc; n++)
        printf("argv[%d] : %s\n", n, argv[n]);
    while(*env){
        printf("%s\n", *env);
        env++;
    }
}
```
```
#test.sh
gcc -o testarg testarg.c
gcc -o test test.c
./test
```
```
$ sh test.sh
before exec function
in testarg.c
argc = 2
argv[0] : testarg
argv[1] : 100
TESTENV=test
```
### 7.4.3 exec 함수군과 fork(2)
#### 개요
* fork(2) : 새로운 프로세스 생성
* 예제 284 : 부모/자식 프로세스가 같은 프로그램 실행
* 자식 프로세스에서 exec 함수군 호출시 자식은 부모로부터 복사한 프로그램과는 다른 명령이나 프로그램 실행 가능
#### 예제 296 : 자식 프로세스에서 다른 프로그램 실행(fork(2), execlp(3))
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
            printf("pid : %d, ppid : %d\n", (int)getpid(), (int)getppid());
            exit(0);
            break;
    }
}
```
```
$ sh test.sh
parent process
pid : 11872, ppid : 11866
child process
.  ..  .***  .******  *********.** (...)
```

## 7.5 프로세스 동기화
### 개요
* fork(2)로 생성한 부모/자식 프로세스 중 먼저 실행을 마친 프로세스는 종료함
* 부모/자식 프로세스간 종료 절차가 제대로 진행되지 않을 수 있음
* 이때 좀비 프로세스(zombie process)같은 불안정 상태의 프로세스 발생
* 이를 방지하기 위해 부모/자식 프로세스를 동기화해야 함
### 7.5.1 좀비 프로세스
* 정상적 프로세스 종료 과정
    * 자식 프로세스가 종료를 위해 부모 프로세스에 종료 상태 리턴
    * 부모 프로세스는 프로세스 테이블에서 자식 프로세스 삭제
* 비정상적 프로세스 종료
    * 부모 프로세스가 자식 프로세스의 종료 상태를 받지 않음
    * 부모 프로세스가 자식 프로세스보다 먼저 종료
* 좀비 프로세스는 프로세스 테이블에만 존재함
* 좀비 프로세스는 일반적인 방법으로 제거할 수 없으며 부모 프로세스가 wait(2)를 호출해야 사라짐
* 고아 프로세스
    * 부모 프로세스가 먼저 종료된 자식 프로세스
    * init 프로세스의 자식 프로세스로 등록됨
### 7.5.2 프로세스 동기화
#### 프로세스 동기화 : wait(2)
```C
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait(int* wstatus);
```
* 자식 프로세스가 종료될 때까지 부모 프로세스를 기다리게 함
* 자식 프로세스의 종료 상태는 wstatus가 지정한 주소에 저장됨
* wait(2)를 호출 전에 자식 프로세스가 종료되면 즉시 리턴
* 리턴값 : 자식 프로세스의 PID
* -1 리턴 : 살아있는 자식 프로세스가 없음
#### 예제 299 : 프로세스 동기화(wait(2))
```C
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int status;
    pid_t pid;

    switch(pid = fork()){
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            printf("child process\n");
            exit(2);
            break;
        default:
            printf("parent process\n");
            while(wait(&status) != pid)
                continue;
            printf("status : %d, %x\n", status, status);
            printf("child process exit status : %d\n", status >> 8); //부모 프로세스에 왼쪽으로 1byte 이동해 전달됨
            break;
    }
}
```
```
$ sh test.sh
parent process
child process
status : 512, 200
child process exit status : 2
```
#### 특정 자식 프로세스 동기화 : waitpid(2)
```C
#include<sys/types.h>
#include<sys/wait.h>
pid_t waitpid(pid_t pid, int* wstatus, int options);
```
* 인자 설명
    * pid : 종료를 기다리는 PID
    * status : 종료 상태값을 저장할 주소
    * options : waitpid(2)의 리턴 조건
* wait(2) : 자식 프로세스가 여러 개일 경우 아무 자식 프로세스가 종료하면 리턴
* waitpid(2) : pid로 지정한 자식 프롯스가 종료하기를 기다림
* pid에 지정할 수 있는 값
    * -1보다 작을 경우 : 절대값과 같은 GID를 가신 프로세스 그룹에 속한 자식 프로세스 중 임의의 프로세스 상태값 요청
    * -1 : wait(2)와 동일하게 임의의 자식 프로세스의 상태값 요구
    * 0 : 함수를 호출한 프로세스와 같은 프로세스 그룹에 속한 임의의 프로세스의 상태값을 요구
    * 0보다 클 경우 : 지정한 pid에 해당하는 프로세스의 상태값을 요구
* options : <sys/wait.h>에 정의되어 있음, OR 연산 가능
    * WCONTINUE : 수행 중인 자식 프로세스의 상태값 리턴
    * WNOHANG : pid로 지정한 자식 프로세스의 상태값을 즉시 리턴받을 수 없어도 이를 호출한 프로세스의 실행을 블로킹하지 않고 다른 작업을 수행하게 함
    * WNOWAIT : 상태값을 리턴한 프로세스가 대기 상태로 머물 수 있도록 함
    * WUNTRACED : 실행을 중단한 자식 프로세스의 상태값을 리턴 - 실행이 중단되었으므로 더이상 상태값을 리턴하지 않음
#### 예제 302 : 특정 자식 프로세스 동기화(waitpid(2))
```C
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int status;
    pid_t pid;

    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        printf("child process\n");
        sleep(3);
        exit(3);
    }

    printf("parent process\n");
    while(waitpid(pid, &status, WNOHANG) == 0){
        printf("parent still wating ...\n");
        sleep(1);
    }
    printf("child exit stuats : %d\n", status >> 8);
}
```
```
$ sh test.sh
parent process
parent still wating ...
child process
parent still wating ...
parent still wating ...
parent still wating ...
child exit stuats : 3
```
#### 특정 자식 프로세스와 동기화 : waitid(2)
```C
#include<sys/types.h>
#include<sys/wait.h>
int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options);
```
* 인자 설명
    * idtype : 종료를 기다리는 자식 프로세스 유형 정의
    * id : 식별 번호
    * infop : siginfo_t 구조체 포인터
    * options : waitid(2)의 리턴 조건
* POSIX 표준으로 리눅스에서 제공
    * UNIX 시스템에선 제공하지 않을 수 있음
* waitpid(2)보다 좀 더 세부적으로 정의할 수 있음
* idtype : 기다리는 자식 프로세스를 지정
    * P_PID : PID가 id와 일치하는 자식 프로세스를 기다림
    * P_GID : GID가 id와 일치하는 자식 프로세스를 기다림
    * P_ALL : 모든 자식 프로세스를 기다림 - id는 무시
* id : PID, GID 등 자식 프로세스를 구분할 수 있는 식별 번호를 지정
* infop : waitid(2)가 성공하면 결과값을 채워서 돌려주는 siginfo_t 구조체
    * si_pid : 자식 프로세스의 PID
    * si_uid : 자식 프로세스의 UID
    * si_signo : 시그널로 항상 SiGCHLD로 설정
    * si_status : 자식 프로세스의 종료 상태값
    * si_code : 자식 프로세스가 종료된 이유 코드 저장
        * CLD_EXITED : 자식 프로세스가 _exit(2)를 호출해 종료
        * CLD_KILLED : 자식 프로세스가 시그널을 받고 종료
        * CLD_DUMPED : 자식 프로세스가 시그널을 받고 종료하고 코어 덤프 수행
        * CLD_STOPPED : 자식 프로세스가 시그널을 받고 중단된 상태
        * CLD_CONTINUE : SIGCONT 시그널을 받고 자식 프로세스가 계속 실행
* options : waitid(2) 함수의 리턴 조건 - OR 연산 가능
    * WEXITED : 자식 프로세스가 종료될 때까지 기다림
    * WSTOPPED : 시그널을 받아 중단된 자식 프로세스를 기다림
    * WCONTINUED : 시그널을 받아 다시 수행 중인 자식 프로세스를 기다림
    * WNOHANG : pid로 지정한 자식 프로세스의 상태값을 즉시 리턴받을 수 없어도 이를 호출한 프로세스의 실행을 블로킹하지 않고 다른 작업을 수행하게 함(waitpid(2)에서와 같음)
    * WNOWAIT : 상태값을 리턴한 프로세스가 대기 상태로 머물 수 있도록 함
#### 예제 303 : 특정 자식 프로세스 동기화(waitid(2))
```C
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int status;
    pid_t pid;
    siginfo_t infop;
    
    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        printf("child process\n");
        sleep(2);
        exit(2);
    }

    printf("parent process\n");

    while(waitid(P_PID, pid, &infop, WEXITED) != 0){
        printf("parent still wating ...\n");
    }

    printf("child's pid : %d\n", infop.si_pid);
    printf("child's uid : %d\n", infop.si_uid);
    printf("child's code : %d\n", infop.si_code);
    printf("child's status : %d\n", infop.si_status);
}
```
```
$ sh test.sh
parent process
child process
child's pid : 13953
child's uid : 1000
child's code : 1
child's status : 2
```