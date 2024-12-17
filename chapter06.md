# 6장 프로세스 정보
## 6.1 개요
### 6.1.1 프로세스
- 프로세스: 현재 실행 중인 프로그램
- 프로세스 상태: 실행, 수면, 실행 대기, ...
- 시스템에서 실행 중인 프로세스 확인: ps(1), top(1)
- 프로세스 ID(PID): 프로세스 식별
- 프로세스 그룹: 관련된 프로세스들이 모여 형성하는 그룹
- 세션: 사용자가 *로그인*해서 작업하는 터미널 단위로 프로세스 그룹을 묶음
### 6.1.2 주요 함수
#### 프로세스 식별 함수
```C
int sysinfo(struct sysinfo* info);  //메모리와 스왑 상태 검색
pid_t getpid(void);                 //PID 검색
pid_t getppid(void);                //부모 PID 검색
pid_t getpgrp(void);                //프로세스 그룹 ID 검색
pid_t getpgid(pid_t pid);           //프로세스 그룹 ID 검색
int setpgid(pid_t pid, pid_t pgid); //프로세스 그룹 ID 변경
pid_t getsid(pid_t pid);            //세션 리더 ID 검색
pid_t setsid(void);                 //세션 생성
```
#### 프로세스 실행 시간 측정 함수
```C
clock_t times(struct tms* buf); //프로세스 실행 시간 측정
```
- 시스템사용 요금 결정/성능 측정 등에 사용
- 시스템 실행 시간: 프로세스에서 *커널 코드*를 실행한 시간
- 사용자 실행 시간: 사용자 모드에서 프로세스를 실행한 시간
#### 프로세스 환경 설정 함수
```C
extenr char** environ;          //환경 설정 전역 변수사용
char* getenv(const char* name); //환경 변수 검색
int putenv(char* string);       //환경 변수 설정
int setenv(const char* name, const char* value, int overwrite);//환경 변수 설정
int unsetenv(const char* name); //환경 변수 삭제
```
- 자식 프로세스는 부모 프로세스로부터 기본 환경을 물려받는다
- 환경 변수를 사용해 프로세스 환경 검색/설정
- main()의 인자로 받기/프로세스 환경 설정 함수 사용

## 6.2 프로세스의 개념
### 6.2.1 프로세스 정의
#### 프로세스
- 프로세스: 실행 중인 프로그램 - 메모리에 적재되어프로세서가 처리 중인 프로그램(실행 파일)
- 프로세서: CPU
- 프로그램: 명령어 집합
- 프로그램과 프로세스, 프로세서의 관계: 그림 6.2.1 참고
### 6.2.2 프로세스의 구조
#### 프로세스의 기본 구조
- 그림 6.2.2 참고
    |영역|기능|
    |---|---|
    |스택|지역변수|
    |빈 공간||
    |힙|동적 메모리 할당|
    |데이터|전역변수|
    |텍스트|프로그램 실행 코드|
#### 프로세스의 기본 구조
- 텍스트 영역: 실행 코드 저장 - 고정 영역
- 데이터 영역: 전역 변수 저장 - 고정 영역
- 힙 영역: *프로그램 실행 중* 동적으로 메모리를 요청하는 경우 할당되는 영역 - 가변 영역
- 스택 영역: 지역 변수 저장 - 가변 영역
- 빈 공간: 가변적 메모리 할당을 위해 유지하는 빈 메모리 영역 - 소진시 실행 중단 가능성
### 6.2.3 프로세스 상태 변화
#### 주요 상태
- 사용자 모드
- 커널 모드
- 수면: *이벤트* 발생을 기다리는 상태(입출력 완료 또는 다른 프로세스 종료를 기다림)
- 실행 대기: CPU를 사용할 수 있을 때까지 기다리는 상태
#### 전이
- 그림 6.2.3 참고
- 프로세스는 사용자 모드에서 먼저 실행
- 시스템 호출로 커널모드로 전환
- 수면 상태의 프로세스가 깨어나 실행 대기 상태가 됨
- (파이프라이닝 등에 의해) 더 이상 실행할 수 없을 경우 수면 상태로 전환
### 6.2.4 프로세스 목록 확인: ps(1)
#### 현재 터미널에서만 실행 중인 프로세스 출력
- 옵션 없음: 현재 터미널에서만 실행 중인 프로세스 출력
    ```
    $ ps
    PID TTY          TIME CMD
    8128 pts/0    00:00:00 bash
    17111 pts/0    00:00:00 ps
    ```
#### 시스템 전체 프로세스 출력
- -ef: 시스템 전체 프로세스 출력
    ```
    $ ps -ef
    UID          PID    PPID  C STIME TTY          TIME CMD
    root           1       0  0 00:16 ?        00:00:05 /sbin/init splash
    root           2       0  0 00:16 ?        00:00:00 [kthreadd]
    root           3       2  0 00:16 ?        00:00:00 [rcu_gp]
    root           4       2  0 00:16 ?        00:00:00 [rcu_par_gp]
    root           5       2  0 00:16 ?        00:00:00 [slub_flushwq]
    root           6       2  0 00:16 ?        00:00:00 [netns]
    (...)
    ```
### 6.2.5 시스템 메모리 정보
#### 시스템 메모리 정보 확인: top(1)
- 시스템 평균 부하 정보 출력
    ```
    $ top
    top - 01:23:02 up  1:06,  1 user,  load average: 0.73, 0.45, 0.62
    작  업: 319 총계,   1 실행, 317 대기,   0 멈춤,   1 좀비
    %Cpu:  4.7 us,  1.6 sy,  0.0 ni, 93.6 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
    MiB 메모리 :  15823.6 total,   9990.6 free,   2469.2 used,   3363.7 buff/cache
    MiB 스  왑:   1158.4 total,   1158.4 free,      0.0 used.  12435.6 avail 메모리
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
    8025 shagyeo+  20   0 1133.3g 298160 107768 S  25.4   1.8  13:50.69 code
    3662 shagyeo+  20   0 5494776 309696 144380 S   9.6   1.9   3:35.08 gnome-shell
    7980 shagyeo+  20   0   32.7g 146668 103492 S   6.3   0.9   3:21.18 code
    7884 shagyeo+  20   0 1123.4g 174596 129108 S   5.6   1.1   2:12.94 code
    (...)
    ```
#### 메모리와 스왑 상태 검색: sysinfo(2)
```C
#include<sys/sysinfo.h>
int sysinfo(struct sysinfo* info);
```
- sysinfo 구조체에 검색 결과를 저장해 리턴
- 성공시: 0 리턴
- 실패시: -1 리턴
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
#### 예제: 메모리 크기 검색(sysinfo(2))
```C
#include<sys/sysinfo.h>
#include<stdio.h>

int main(void){
    struct sysinfo info;
    sysinfo(&info);

    printf("totalram: %ld\n", info.totalram);
    printf("freeram: %ld\n", info.freeram);
    printf("procs: %d\n", info.procs);
}
```
```
$ ./test
totalram: 16592216064
freeram: 11948105728
procs: 797
```

## 6.3 프로세스 식별
### 6.3.0 개요
- 프로세스 ID(PID): 프로세스 식별
    - PPID: parent PID - 부모 프로세스의 pid
- 프로세스 그룹: 관련된 프로세스가 모여 구성하는 그룹
### 6.3.1 PID 검색
#### 프로세스 계층 구조
- 0번 프로세스: 스케줄러 - 프로세스에 CPU 시간을 할당
- 1번 프로세스: init
- 프로세스가 생성될 때마다 기존 PID와 중복되지 않은 번호가 할당
#### PID 검색: getpid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getpid(void);
```
- 함수를 호출한 프로세스의 PID 리턴(입력이 void)
#### PPID 검색: getppid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getppid(void);
```
- PPID: parent PID - 부모 프로세스의 PID
```
$ ps -ef
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 00:16 ?        00:00:06 /sbin/init splash
root           2       0  0 00:16 ?        00:00:00 [kthreadd]
root           3       2  0 00:16 ?        00:00:00 [rcu_gp]
root           4       2  0 00:16 ?        00:00:00 [rcu_par_gp]
root           5       2  0 00:16 ?        00:00:00 [slub_flushwq]
(...)
```
- init: 1번 프로세스 - PPID가 0인 것을 확인
- kthread: 스레드 관리 프로세스 - PPID가 0인 것을 확인
#### 예제: PID, PPID 검색(getpid(2), getppid(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("pid: %d\n", (int)getpid());
    printf("ppid: %d\n", (int)getppid());
}
```
```
$ ./test
pid: 5025
ppid: 5019
```
- 참고: 프롬프트에서 실행 파일 실행시 셸이 자식 프로세스 생성(7장)
### 6.3.2 프로세스 그룹
#### 프로세스 그룹
- 프로세스 그룹: 관련된 프로세스로 구성한 그룹
- PGID: 프로세스 그룹 ID
- 멤버: 프로세스 그룹을 구성하는 프로세스
- 도입 배경: BSD 계열 유닉스에서 작업 제어를 구현하며 도입
- 작업 제어: 명령을 파이프로 연결해 프로세스 그룹으로 묶어 한 작업으로 처리 가능
#### 프로세스 그룹 리더
- 프로세스 그룹 리더: PGID에 해당하는 프로세스
- 그룹 리더의 PID가 PGID가 됨
- 리더 프로세스가 변경되면 PGID도 변경된다
#### PGID 검색: getpgrp(2), getpgid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getgrp(void);
pid_t getpgid(pid_t pid);
```
- getgrp(2): 호출한 프로세스가 속한 그룹의 PGID 리턴
- getpgid(2): 인자로 지정한 pid에 해당하는 프로세스의 PGID 리턴
#### 예제: PGID 검색(getpgrp(2), getpgid(2))
```C
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(void){
    printf("pid: %d\n", (int)getpid());
    printf("pgrp: %d\n", (int)getpgrp());
    printf("pgid: %d\n", (int)getpgid(getpid()));
    printf("pgid(0): %d\n", (int)getpgid(0));
}
```
```
$ ./test
pid: 28555
pgrp: 28546
pgid: 28546
pgid(0): 28546
```
#### PGID 변경: setpgid(2)
```C
#include<sys/types.h>
#include<unistd.h>
int setpgid(pid_t pid, pid_t pgid);
```
- pid가 가리키는 프로세스의 PGID를 pgid로 변경
- pid, pgid가 동일한 경우: 그룹 리더
- pid를 0으로 지정: setpgid(2)를 호출한 프로세스의 PID 사용
- pgid를 0으로 지정: pid로 지정한 프로세스가 PGID가 됨
### 6.3.3 세션
#### 세션
- 세션: 사용자가 로그인해 작업하고 있는 터미널 단위로 프로세스 그룹을 묶음(그림 6.3.3)
- 세션에도 id가 할당된다
- 세션 리더: 프로세스가 세션을 생성하면 해당 프로세스가 세션 리더가 됨
#### 세션 검색: getsid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t getsid(pid_t pid);
```
- 인자로 지정한 프로세스가 속한 세션의 SID 리턴
- pid를 0으로 지정: 현재 프로세스의 SID 리턴
#### 예제: 세션 검색(getsid(2))
```C
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(void){
    printf("pid: %d\n", (int)getpid());
    printf("pgrp: %d\n", (int)getpgrp());
    printf("sid: %d\n", (int)getsid(0));
}
```
```
$ sh test.sh
pid: 32317
pgrp: 32311
sid: 8128
$ ps
    PID TTY          TIME CMD
   8128 pts/0    00:00:00 bash
  32349 pts/0    00:00:00 ps
```
- 세션의 리더가 bash 셸인 것을 확인
#### 세션 생성: setsid(2)
```C
#include<sys/types.h>
#include<unistd.h>
pid_t setsid(void);
```
- 호출하는 프로세스가 그룹 리더가 아니면 새로운 세션을 만들어 세션 리더/그룹 리더가 된다
- 새로운 세션과 프로세스 그룹의 유일한 프로세스가 된다
- 성공시: 새로운 SID 리턴
- 실패시 : -1 리턴

## 6.4 프로세스 실행 시간 측정
### 6.4.0

## 6.5 환경 변수의 활용
### 6.5.0
