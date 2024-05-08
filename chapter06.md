# 6장 프로세스 정보
### 학습 목표
* 리눅스 시스템에서 프로세스가 무엇인지 이해한다.
* 함수를 사용해 프로세스의 속성을 검색할 수 있다.
* 프로세스의 실행 시간을 측정할 수 있다.
* 환경 변수를 설정하고 사용할 수 있다.
### 중요 개념
* 6.1 개요 : 
* 6.2 프로세스의 개념 : 
* 6.3 프로세스 식별 : 
* 6.4 프로세스 실행 시간 측정 : 
* 6.5 환경 변수의 활용 : 

## 예제 명세
### 6.2 프로세스의 개념
* 250 : 메모리 크기 검색(sysinfo(2))
### 6.3 프로세스 식별
* 252 : PID, PPID 검색(getpide(2), getppid(2))
* 254 : PGID 검색(getpgrp(2), getpgid(2))
* 257 : 세션 ID 검색(getsid(2))
### 6.4 프로세스 실행 시간 측정
* 260 : 실행 시간 측정(times(2))
### 6.5 환경 변수의 활용
* 265 : 전역 변수로 환경 변수 검색(environ(7))
* 266 : main() 인자로 환경 변수 검색
* 268 : 환경 변수 검색(getenv(3))
* 269 : 환경 변수 설정(putenv(3))
* 270 : 환경 변수 설정(setenv(3))

## 6.1 개요
### 6.1.1 프로세스
#### 프로세스
* 프로세스 : 현재 실행 중인 프로그램
* 리눅스에서는 동시에 여러 프로세스가 실행 됨
* 계속 실행 상태에 있는 것은 아니며 규칙에 따라 여러 상태로 변함
* ps(1), top(1) : 현재 시스템에서 실행중인 프로세스 확인
#### 프로세스의 상태
* 실행
* 수면(sleep)
* 실행 대기
#### PID, 프로세스 그룹, 세션
* PID(프로세스 ID) : 시스템에서 프로세스를 식별하기 위해 사용하는 ID
* 프로세스 그룹(process group) : 관련 프로세스들이 모여 프로세스 그룹 형성
* 세션(session) : POSIX에서 제안한 개념으로, 사용자가 로그인해 작업하는 터미널 단위로 프로세스를 묶은 것
### 6.1.2 프로세스 관련 함수
#### 프로세스 식별 함수
```C
int sysinfo(struct sysinfo* info);  //메모리와 스왑 상태 검색
pid_t getpid(void);                 //PID 검색
pid_t getppid(void);                //부모 PID 검색
pid_t getpgrp(void);                //프로세스 그룹 ID 검색
pid_t getpgid(pid_t pid);           //프로세스 그룹 ID 검색
int setpgid(pid_t pid, pid_t pgid); //프로세스 그룹 ID 변경
pid_t getsid(pid_t pid);            //세션 리더 ID rjator
pid_t setsid(void);                 //세션 생성
```
#### 프로세스 실행 시간 측정 함수
```C
clock_t times(struct tms* buf); //프로세스 실행 시간 측정
```
* 시스템 사용 요금 결정, 시간소요가 많은 부분 찾기 등에 쓰임
* 프로세스 실행 시간의 구분
    * 시스템 실행 시간 : 프로세스에서 커널의 코드를 수행한 시간
    * 사용자 실행 시간 : 사용자 모드에서 프로세스를 실행한 시간
#### 프로세스 환경 설정 함수
```C
extenr char** environ;          //환경 설정 전역 변수사용
char* getenv(const char* name); //환경 변수 검색
int putenv(char* string);       //환경 변수 설정
int setenv(const char* name, const char* value, int overwrite);//환경 변수 설정
int unsetenv(const char* name); //환경 변수 삭제
```
* 기본 환경 : 모든 프로세스는 부모 프로세스(parent process)로부터 기본 환경을 물려받음
* 환경 변수(environment variable)를 사용해 프로세스 환경을 설정하거나 설정된 환경을 검색할 수 있음

## 6.2 프로세스의 개념
### 6.2.1 프로세스의 정의 
#### 프로세스
* 프로세스 : 실행 중인 프로그램 - 파일의 종류와 관계없이 실행파일을 메모리에 적재(load)하면 프로세스가 됨
* 프로세서 : CPU를 의미(프로세스를 처리함)
* 프로그램 : 명령어의 집합
#### 프로그램, 프로세스, 프로세서의 관계
* 프로그램
    * 소스파일
    * 실행 파일(소스 파일을 컴파일)
* 프로세스
    * 프로그램을 메모리에 적재
* 프로세서(CPU)
    * 프로세서를 실행
### 6.2.2 프로세스의 구조
* 스택(stack) 영역
    * 프로그램에서 정의한 지역 변수를 저장하는 메모리 영역
    * 지역 변수를 정의한 부분에서 할당해 사용함
* 빈 공간
    * 가변 영역(스택 영역, 힙 영역)의 가변적 메모리 할당을 위해 유지하고 있는 빈 메모리 영역
    * 이 영역이 모두 소진되면 메모리 부족으로 프로그램이 중단될 수 있음
* 힙(heap) 영역
    * 프로그램 실행 중에 동적으로 메모리를 요청하는 경우 할당되는 영역
    * 빈 영역 - 할당 - 할당 해제 과정으로 상태가 변함(가변 영역)
* 데이터 영역
    * 프로그램에서 정의한 전역 변수를 저장
    * 전역 변수는 프로그램 작성시 크기가 고정(고정 영역)
* 텍스트 영역
    * 실행 코드 저장
    * 프로세스 실행 중 크기가 변하지 않음(고정 영역)
* 가변 영역 : 스택, 빈 공간, 힙 영역
* 고정 영역 : 데이터, 텍스트 영역
### 6.2.3 프로세스 상태 변화
#### 프로세스의 상태 및 전이
* 1 : 사용자 모드 수행
* 2 : 커널 모드 수행
* 3 : 실행 대기(wait)
* 4 : 수면(sleep)
* 1 - 2 : 시스템 호출
* 2 - 2 : 인터럽트, 인터럽트 복귀
* 2 - 4 :
* 4 - 3 : 깨어남(wake up)
* 3 - 2 :
* 2 - 1 : 복귀
#### 프로세스 상태 전이 과정
* 프로세스는 사용자 모드에서 먼저 실행됨
* 사용자 모드에서 시스템 호출시 커널 모드로 전환되어 실행
* 수면 중이던 프로세스가 깨어나 실행 대기 상태가 되면 바로 실행할 수 있도록 준비함
* 커널 모드에서 실행 중 입출력 완료를 기다릴 때와 같이 실행을 더 이상 할 수 없을 때 수면 상태로 전환
#### 스케줄링
* 스케줄링 : 커널의 프로세스 관리 기능(프로세스의 상태를 적절히 변환)
* CPU : 한 번에 프로세스 하나만 실행 가능
* 한 개의 프로세스만 1 또는 2 상태에 있음
* 나머지는 3, 4 상태에 있음
* 수면 상태 : 사건(event)가 발생하기를 기다리는 상태
    * 입출력을 완료했을 때
    * 다른 프로세스가 종료되기를 기다릴 때
* 해당 사건이 발생하면 실행 대기 상태로 전환(스케줄링에 따라 수행됨)
### 6.2.4 프로세스 목록 보기
#### 프로세스 목록 보기 : ps(1)
```
$ ps #현재 터미널에서 실행한 프로세스만 출력
$ ps -ef | more #시스템에서 동작중인 전체 프로세스 보기
```
#### 시스템 메모리 정보 보기 : top(1)
```
$ top
```
* 프로세스 목록만 보여주는 것이 아님
* 시스템 부하 평균 정보(load average)를 아래의 정보를 통해 표시
    * 메모리
    * 스왑
    * 실행 중인 프로세스 수
    * ...
#### 메모리와 스왑 상태 검색 : sysinfo(2)
```C
#include<sys/sysinfo.h>
int sysinfo(struct sysinfo* info);
```
* sysinfo 구조체에 검색 결과를 저장해 리턴
* 성공시 : 0 리턴
* 실패시 : -1 리턴
#### sysinfo 구조체
```C
struct sysinfo{
    long uptime;            //시스템 부팅 후 경과된 시간을 초 단위로 저장
    unsigned long loads[3]; //시스템 부하 평균을 저장하는 배열(1, 5, 15분 기준)
    unsigned long totalram; //사용 가능한 총 메모리 크기 저장
    unsigned long freeram;  //사용 가능한 메모리 크기 저장
    unsigned long sharedram;//공유 메모리 크기 저장
    unsigned long bufferram;//버퍼가 사용하는 메모리 크기 저장
    unsigned long totalswap;//스왑 영역의 크기 저장
    unsigned long freeswap; //사용 가능한 스왑 영역의 크기 저장
    unsigned short procs;   //현재 실행 중인 프로세스 수 저장
    unsigned long totalhigh;//사용자에 할당된 메모리(high memory)의 총 크기 저장
    unsigned long freehigh; //사용 가능한 사용자 메모리 크기 저장
    unsigned int mem_unit;  //메모리 크기를 바이트 단위로 저장
    char _f[20-2*sizeof(long)-sizeof(int)]; //64바이트 크기를 맞추기 위한 패딩
}
```
#### 예제 250 : 메모리 크기 검색(sysinfo(2))
```C
#include<sys/sysinfo.h>
#include<stdio.h>

int main(void){
    struct sysinfo info;
    sysinfo(&info);

    printf("totalram : %ld\n", info.totalram);
    printf("freeram : %ld\n", info.freeram);
    printf("procs : %d\n", info.procs);
}
```
```
$ sh test.sh
totalram : 16592216064
freeram : 11948105728
procs : 797
```
#### 참고 : 스왑 영역, 패딩
* 스왑 영역 : RAM이 가득 찼을 때 임시로 사용하는 공간
* 패딩 : 읽는 대상에 메모리를 추가하여 성능 저하를 막는 것

## 6.3 프로세스 식별
### 개요
* PID(process ID) : 프로세스 식별을 위한 ID
* 프로세스 그룹 : 관련 프로세스가 모여 형성
### 6.3.1 PID 검색
#### 개요
* PID 시작 : 0
    * 0번 프로세스 : 스케줄러
    * 1번 프로세스 : init
* 프로세스가 생성될 때마다 기존 PID와 중복되지 않은 번호가 할당됨
* PID 검색 : getpid(2) 사용
#### PID 검색 : getpid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getpid(void);
```
* 이 함수를 호출한 프로세스의 PID를 리턴
#### PPID 검색 : getppid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getppid(void);
```
* 부모 프로세스(parent process)
    * 프로세스를 생성한 프로세스
    * 0번 프로세스(스케줄러)를 제외한 모든 프로세스에게 부모 프로세스가 있음
* PPID(parent process ID) : 부모 프로세스의 PID
#### 예제 252 : PID, PPID 검색(getpide(2), getppid(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("pid : %d\n", (int)getpid());
    printf("ppid : %d\n", (int)getppid());
}
```
```
$ sh test.sh
pid : 5025
ppid : 5019
```
### 6.3.2 프로세스 그룹
#### 프로세스 그룹
* 프로세스 그룹 : 관련 있는 프로세스를 묶은 것
* 프로세스 그룹 리더
    * 멤버 중 하나가 그룹 리더가 됨
    * 프로세스 그룹 리더의 PID가 PGID가 됨
    * 변경 가능하며 변경시 PGID도 변경됨
* PGID(processs group ID) : 프로세스 그룹이 부여받는 ID
* 멤버 : 프로세스 그룹을 구성하는 각 프로세스
* 도입 배경
    * BSD 계열 유닉스에서 작업(job) 제어를 구현하며 도입
    * 작업 제어 기능을 제공하는 셸(C 셸, 배시 셸 등)은 명령을 파이프로 연결함으로써 프로세스 그룹으로 묶어 한 작업으로 처리 가능
#### PGID 검색 : getpgrp(2), getpgid(2)
```C
#include<sys/types.h>
#include<unistd>
pid_t getgrp(void);
pid_t getpgid(pid_t pid);
```
* getgrp(2) : 함수를 호출하는 프로세스가 속한 그룹의 PGID 리턴
* getpgid(2) : 인자로 지정한 프로세스가 속한 그룹의 PGID 리턴
#### 예제 254 : PGID 검색(getpgrp(2), getpgid(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("pid : %d\n", (int)getpid());
    printf("pgrp : %d\n", (int)getpgrp());
    printf("pgid(0) : %d\n", (int)getpgid(0));
    //printf("pgid(xxxx) : %d\n", (int)getpgid(xxxx));
```
```
$ sh test.sh
pid : 5328
pgrp : 5322
pgid(0) : 5322
```
#### PGID 변경 : setpgid(2)
```C
#include<sys/types.h>
#include<unistd.h>
int setpgid(pit_t pid, pid_t pgid);
```
* 인자 설명
    * pid : 그룹에 속하는 프로세스의 pid(그룹을 지정)
    * pgid : 새로 지정할 pgid(그룹 리더가 될 멤버 지정)
* pid에 해당하는 프로세스 그룹의 PGID를 pgid에 해당하는 멤버의 PID로 변경
* pid가 0일 때 : 이 함수를 호출하는 현재 프로세스의 PID 사용
* pgid가 0일 때 : pid로 지정한 프로세스가 PGID가 됨
### 6.3.3 세션
#### 세션
* 세션(session)
    * 사용자가 로그인해 작업하고 있는 터미널 단위로 프로세스 그룹을 묶은 것
    * 관련 있는 프로세스 그룹을 모은 것
    * POSIX 표준에서 제안한 개념
* 세션에도 ID가 할당됨
    * 세션 리더 : 프로세스가 새로운 세션 생성시 해당 프로세스는 세션 리더가 됨
    * 세션 ID : 세션 리더의 PID
#### 세션 검색 : getsid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getsid(pid_t pid);
```
* pid로 지정한 프로세스가 속한 세션의 ID 리턴
* 0으로 지정시 현재 프로세스의 세션 ID 리턴
#### 예제 257 : 세션 ID 검색(getsid(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("pid : %d\n", (int)getpid());
    printf("pgid : %d\n", (int)getpgrp());
    printf("sid : %d\n", (int)getsid(0)); //세션 리더 : 배시 셸
}
```
```
$ sh test.sh
pid : 5742
pgid : 5736
sid : 4989
```
#### 세션 생성 : setsid(2)
```C
#include<sys/types.h>
#include<unistd>
pid_t setsid(void);
```
* setsid(2)를 호출하는 프로세스에 대해
    * 프로세스 그룹 리더가 아닐 경우
    * 세션 리더가 됨
    * 새로운 세션에서 프로세스 그룹 리더가 됨
    * setsid(2)를 호출한 프로세스가 새로운 세션과 프로세스 그룹의 유일한 프로세스가 됨
* 성공시 : 세션 ID 리턴
* 실패시 : -1 리턴

## 6.4 프로세스 실행 시간 측정
### 개요
* 프로세스 실행시 시스템 자원(system resouce)(CPU, 메모리 등)을 사용
* 시간 정보를 이용해 프로세스 실행 시간 측정 가능
* 시스템 사용 요금 결정시 활용
* 프로그램 성능 향상에 활용
### 6.4.1 프로세스 실행 시간의 구성
* 프로세스 실행 시간의 구분
    * 시스템 실행 시간
        * 커널의 코드를 수행한 시간
        * 시스템 호출로 소비한 시간을 의미함
    * 사용자 실행 시간
        * 사용자 모드에서 프로세스를 실행한 시간
        * 프로그램 내부 사용자가 작성한 코드를 실행하는 데 걸린 시간을 의미
* 프로세스 실행 시간 = 시스템 실행 시간 + 사용자 실행 시간
### 6.4.2 프로세스 실행 시간 측정
#### tms 구조체
```C
struct tms{
    clock_t tms_utime;  //times(2)를 호출한 프로세스가 사용한 사용자 모드 실행 시간
    clock_t tms_stime;  //times(2)를 호출한 프로세스가 사용한 시스템 모드 실행 시간
    clock_t tms_cutime; //tms_utime + times(2)를 호출한 프로세스의 모든 자식 프로세스가 사용한 사용자 모드 실행 시간
    clock_t tms_cstime; //tms_stime + times(2)를 호출한 프로세스의 모든 자식 프로세스가 사용한 시스템 모드 실행 시간
};
```
* <sys/tymes.h>에 정의되어 있음
#### 실행 시간 측정 : times(2)
```C
#include<times.h>
clock_t times(struct tms* buf);
```
* 인자 설명
    * buf : 실행 시간을 저장할 tms 구조체의 주소
* 실행 결과를 tms 구조체에 저장하고 클록 틱 리턴
* 임의의 시점으로부터 경과된 클록 틱 수 리턴
    * 일반적으로 부팅 시점
    * 두 번 호출하여 차이를 계산해 시간 측정
* 실패시 : -1 리턴
#### 예제 260 : 실행 시간 측정(times(2))
```C
#include<sys/types.h>
#include<sys/times.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(void){
    time_t t;
    struct tms buf;
    clock_t ct; clock_t t1, t2;

    ct = sysconf(_SC_CLK_TCK); //_SC_CLK_TCK : 초당 클록 틱 수(sysconf(3)의 인자로 지정하는 상수)
    printf("cd : %ld\n", ct);

    if((t1 = times(&buf)) == -1){
        perror("t1");
        exit(1);
    }

    for(int i = 0; i < 99999999; i++);
        time(&t);
    sleep(1);

    if((t2 = times(&buf)) == -1){
        perror("t2");
        exit(1);
    }

    printf("t1 : %ld\n", t1);
    printf("t2 : %ld\n", t2);
    printf("utime : %ld\n", buf.tms_utime);
    printf("stime : %ld\n", buf.tms_stime);
    printf("real time : %.1f sec\n", (double)(t2 - t1) / ct);
    printf("user time : %.1f sec\n", (double)buf.tms_utime / ct);
    printf("system time : %.1f sec\n", (double)buf.tms_stime / ct);
}
```
```
$ sh test.sh
cd : 100
t1 : 1718454722
t2 : 1718454880
utime : 57
stime : 0
real time : 1.6 sec
user time : 0.6 sec
system time : 0.0 sec
```
* sleep(3)로 인해 실행 시간이 차이남

## 6.5 환경 변수의 활용
### 개요
* 프로세스가 실행되는 기본 환경
    * 사용자의 로그인명(login name)
    * 로그인 셸(login shell)
    * 터미널에 설정된 언어
    * 경로명(pathname)
    * ...
* 기본 환경은 환경 변수로 정의되어 있음
* 모든 프로세스는 부모 프로세스에서 기본 환경을 물려받음
* 셀은 환경 변수를 검색/추가/수정할 수 있도록 함
### 6.5.1 환경 변수의 이해
#### 개요
* 환경 변수의 구성 형태 : '환경 변수명=값'
* 환경 변수명 : (관례적으로) 대문자 사용
* 셸의 종류, 현재 디렉터리 위치, 로그인 ID, 홈 디렉터리, ...
#### 셸의 환경 설정 확인 : env(1)
```
$ env
SHELL=/bin/bash
SESSION_MANAGER=local/*********:@/tmp/.ICE-unix/1709,unix/*********:/tmp/.ICE-unix/1709
QT_ACCESSIBILITY=1
(...)
```
### 6.5.2 환경 변수 사용
#### 환경 변수 사용 방법의 구분
* 전역 변수 사용
* main()의 인자 사용
* getenv(3) 사용
#### 전역 변수 사용 : environ(7)
```C
#include<unistd.h>
extern char** envirion;
```
* 전역 변수 environ : 환경 변수 전체에 대한 포인터
#### 예제 265 : 전역 변수로 환경 변수 검색(environ(7))
```C
#include<unistd.h>
#include<stdio.h>

extern char** __environ;

int main(void){
    char** env;
    env = __environ;
    while(*env){
        printf("%s\n", *env);
        env++;
    }
}
```
```
$ env
SHELL=/bin/bash
SESSION_MANAGER=local/*********:@/tmp/.ICE-unix/1709,unix/*********:/tmp/.ICE-unix/1709
QT_ACCESSIBILITY=1
(...)
```
#### main() 인자 사용
```C
int main(int argc, char** argv, char** envp){}
```
* main()의 세 번째로 환경 변수에 대한 포인터를 받음
#### 예제 266 : main() 인자로 환경 변수 검색
```C
#include<unistd.h>
#include<stdio.h>

int main(int argc, char** argv, char** envp){
    char** env = envp;
    while(*env){
        printf("%s\n", *env);
        env++;
    }
}
```
```
$ env
SHELL=/bin/bash
SESSION_MANAGER=local/*********:@/tmp/.ICE-unix/1709,unix/*********:/tmp/.ICE-unix/1709
QT_ACCESSIBILITY=1
(...)
```
#### 환경 변수 검색 : getenv(3)
```C
#include<stdlib.h>
char* getenv(const char* name);
```
* environ, main() 인자 사용시 특정 환경 변수만 검색하기 불편함
* getenv(3) : 인자로 환경 변수를 지정해 검색
* 실패시 : NULL 포인터 리턴
#### 예제 268 : 환경 변수 검색(getenv(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* val;
    if((val = getenv("SHELL")) == NULL)
        printf("shell not defined\n");
    else
    printf("SHELL=%s\n", val);
}
```
```
$ sh test.sh
SHELL=/bin/bash
```
#### 환경 변수 설정 : putenv(3)
```C
#include<stdlib.h>
int putenv(char* string);
```
* string은 '환경 변수명=값'형태로 지정(예시 : putenv("TERM=vt100");)
* 기존 환경 변수값 : 변경
* 새로운 환경 변수 : malloc(3)으로 메모리를 할당해 추가
* 성공시 : 0 리턴
#### 예제 269 : 환경 변수 설정(putenv(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* val;
    if((val = getenv("TERM")) == NULL)
        printf("TERM not defined\n");
    else
        printf("TERM=%s\n", val);
    
    putenv("TERM=vt100");
    val = getenv("TERM");
    printf("TERM=%s\n", val);
}
```
```
$ sh test.sh
TERM=xterm-256color
TERM=vt100
# 프로그램 안에서 변경한 환경 변수의 값이 부모 프로세스인 셸에서도 유효한 것은 아님
$ env | grep TERM
TERM=xterm-256color
```
#### 환경 변수 설정 : setenv(3)
```C
#include<stdlib.h>
int setenv(const char* name, const char* value, int overwrite);
```
* 인자 설명
    * name : 환경 변수명
    * value : 환경 변수값
    * overwrite : 덮어쓰기
* putenv(3)와 차이점
    * putenv(3) : "환경 변수명=값" 형태로 지정
    * setenv(3) : 환경 변수명과 값을 따로 지정
* 덮어쓰기
    * 환경 변수에 이미 값이 설정되어있을 경우
    * 0 : 덮어쓰기 하지 않음
    * 1 : 덮어쓰기
#### 예제 270 : 환경 변수 설정(setenv(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* val;
    if((val = getenv("TERM")) == NULL)
        printf("term not defined\n");
    else
        printf("TERM=%s\n", val);

    setenv("TERM", "vt100", 0);
    val = getenv("TERM");
    printf("TERM=%s\n", val);

    setenv("TERM", "vt100", 1); //overwrite
    val = getenv("TERM");
    printf("TERM=%s\n", val);
}
```
```
$ sh test.sh
TERM=xterm-256color
TERM=xterm-256color
TERM=vt100
```
#### 환경 변수 설정 삭제 : unsetenv(3)
```C
#include<stdlib.h>
int unsetenv(const char* name);
```
* name으로 지정한 환경 변수 삭제
* name으로 지정한 환경 변수가 없으면 환경 변경을 하지 않음