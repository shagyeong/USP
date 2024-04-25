# 5장 시스템 정보
### 학습 목표
* 함수를 사용해 리눅스 시스템 정보를 검색할 수 있다.
* 함수를 이용해 사용자 정보를 검색할 수 있다.
* 함수를 사용해 시스템 시간을 관리할 수 있다.
### 중요 개념
* 5.1 개요 :
* 5.2 시스템 정보 검색 :
* 5.3 사용자 정보 검색 :
* 5.4 시간 관리 함수 :

## 예제 명세
### 5.2 시스템 정보 검색
* 193 : 운영체제 정보 검색(uname(2))
* 196 : 시스템 자원 정보 검색(sysconf(3))
* 198 : 디렉터리 자원 검색(pathconf(3))
### 5.3 사용자 정보 검색
* 000 : ...
* 000 : ...
### 5.4 시간 관리 함수
* 000 : ...
* 000 : ...

## 5.1 개요
### 개요
* 5장의 함수
    * 리눅스 시스템과 관련된 기본 정보 검색 함수
    * 사용자 정보 검색 함수
    * 시스템 시간 관리 함수
* 환경 정보 검색 함수
    * 기본 환경과 관련된 구조체/상수를 이용해 정보를 검색함
* 환경 정보 검색 함수의 검색 대상 정보
    * 하드웨어/운영체제 종류 정보
    * 메모리 페이지의 크기
    * 최대 패스워드 길이
    * ...
### 시스템 정보 함수
* 시스템 정보
    * 시스템 기본 정보(운영체제 정보)
    * 시스템 자원 정보
    * 파일과 디레거리 자원 정보 검색
```C
//운영체제 정보 검색
int uname(struct utsname* buf);
//시스템 자원 정보 검색
long sysconf(int name);
//파일/디렉터리 자원 검색
long fpathconf(int fd, int name);
long pathconf(const char* path, int name);
```
### 사용자 정보 함수
* 리눅스 시스템의 사용자 정보
    * 사용자 계정 정보 : 로그인명, UID, 패스워드 파일(/etc/passwd), 섀도우 파일(/etc/shadow)에서 사용자 정보를 읽어오는 함수로 구성
    * 그룹 정보 : GID 검색, 그룹 파일(/etc/group)에서 그룹 정보를 읽어오는 함수로 구성
    * 로그인 기록 정보 : /var/log/utmp 파일에서 로그인 기록을 읽어옴
```C
//로그인명 검색
char* getlogin(void);
//UID 검색
uid_t getuid(void);
uid_t geteuid(void);
//패스워드 파일 검색
struct passwd* getpwuid(uid_t uid);
struct passwd* getpwnam(const char* name);
struct paswd* getpwent(void);
void setpwent(void);
void endpwent(void);
struct passwd* fgetpwent(FILE* stream);
//섀도우 파일 검색
struct spwd* getspnam(const char* name);
struct spwd* getspent(void);
void setspent(void);
void endspent(void);
struct spwd* fetspent(FILE* stream);
//그룹 정보 검색
gid_t getgid(void);
gid_t getegid(void);
struct group* getgrnam(const char* name);
struct group* getgrgid(gid_t gid);
struct group* getgr(void);
void setgrent(void);
void endgrent(void);
struct group* fgetgrent(FILE* stream);
//로그인 기록 검색
struct utmp* getutent(void);
void setutent(void);
void endutent(void);
int utmpname(const char* file);
```
### 시간 관리 함수
* 시간 정보의 필요
    * 파일/디렉터리 생성
    * 사용자 정보 변경 등
* 리눅스 시간 관리 함수
    * 현재 시간 정보 검색 함수
    * 시간대 설정 함수
    * 시간 정보를 분해하여 구조체로 리턴하는 함수
    * 시간 정보 출력 형식 지정 함수
```C
//기본 시간 읽기
time_t time(time_t* tloc);
int gettimeofday(struct timeval* tv, struct timezone* tz);
int settimeofday(const struct timeval* tv, const struct timezone* tz);
//시간대 설정
void tzset(void);
//시간 정보 분해
struct tm* gmtime(const time_t* timep);
struct tm* localtime(const time_t* timep);
//초 단위 시간 생성
time_t mktime(struct tm* tm);
//형식 지정 시간 출력
char* ctime(const time_t* timep);
char* asctime(const struct tm* tm);
size_t strftiem(char* s, size_t max, const char* format, const struct tm* tm);
```

## 5.2 시스템 정보 검색
### 개요
* 리눅스 시스템 정보
    * 운영체제에 관한 정보
    * 호스트명 저보
    * 하드웨어 종류
* 리눅스 시스템은 하드웨어에 따라 사용할 수 있는 자원의 최댓값이 설정되어 있음
    * 최대 프로세스 개수
    * 프로세스 하나에 대한 열 수 있는 최대 파일 개수
    * 메모리 페이지 크기
    * ...
### 5.2.1 운영 체제 기본 정보 검색
#### uname(1)
* uname(1) : 시스템에 정보 검색 명령
```
$ uname -a
Linux ********* 6.5.0-28-generic #29~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  4 14:39:20 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
```
* 커널명 - 호스트명 - 커널 릴리즈 - 커널 버전 - 하드웨어명 - 프로세서명 - 플랫폼명 - 운영체제명
#### 운영체제 정보 검색 : uname(2)
```C
#include<sys/utsname.h>
int uname(struct utsname* buf);
```
* 인자 설명
    * buf : utsname 구조체 주소
* 운영체제 정보를 검색하여 utsname 구조체에 저장함
* 성공시 : 0 리턴
* 실패시 : -1 리턴, errno에 오류 코드 지정
#### utsname 구조체
* <sys/utsname.h>에 정의되어 있음
* man -s 2 uname으로 확인 가능
* 구조체의 각 항목은 문자형 배열임
* 각 값은 널 정료 문자열(nul terminated string)로 저장됨
```C
struct utsname{
    char sysname[]; //현재 운영체제의 이름
    char nodename[]; //네트워크를 통해 통신할 때 사용하는 시스템의 이름
    char release[]; //운영체제의 릴리즈 번호
    char version[]; //운영체제의 버전 번호
    char machine  []; //운영체제가 동작하는 하드웨어의 표준 이름(아키텍처)
};
```
#### 예제 193 : 운영체제 정보 검색(uname(2))
```C
#include<sys/utsname.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    struct utsname uts;
    if(uname(&uts) == -1){
        perror("uname");
        exit(1);
    }

    printf("sysname : %s\n", uts.sysname);
    printf("nodename : %s\n", uts.nodename);
    printf("release : %s\n", uts.release);
    printf("version : %s\n", uts.version);
    printf("machine : %s\n", uts.machine);

    exit(0);
}
```
```
$ sh test.sh
sysname : Linux
nodename : *********
release : 6.5.0-28-generic
version : #29~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Thu Apr  4 14:39:20 UTC 2
machine : x86_64
```
#### 참고 : BSD 계열, 솔라리스 유닉스 호스트명 검색 함수
```C
//BSD 계열
#include<unistd.h>
int gethostname(char* name, size_t len);
int sethostname(const char* name, size_t len);
// 솔라리스
#include<sys/systeminfo.h>
long sysinfo(int comand, char* buf, long count);
```
### 5.2.2 시스템 자원 정보 검색
#### 개요
* <limits.h>
    * 하드웨어에 따라 사용할 수 있는 자원의 최댓값
    * POSIX 표준에 따른 정의 위치
#### 시스템 자원 정보 검색 : sysconf(3)
```C
#include<unistd.h>
long sysconf(int name);
```
* 인자 설명
    * name : 검색할 정보를 나타내는 상수
* 시스템 정보를 나타내느 상수를 인자로 받아 설정되어 있는 시스템 자원값/옵션값을 리턴
* 성공시 : 시스템 자원값/옵션값을 리턴
* 실패시 : -1 리턴
#### sysconf(3) 주요 상수값
* man sysconf로 모든 상수값 확인
* POSIX.1에서 정의함
* _SC_ARG_MAX : exec() 계열 함수에 사용하는 인자의 최대 크기
* _SC_CHILD_MAX : 한 UID에 허용되는 최대 프로세스 개수
* _SC_HOST_NAME_MAX : 호스트명의 최대 길이
* _SC_LOGIN_NAME_MAX : 로그인명의 최대 길이
* _SC_CLK_TCK : 초당 클록 틱 수
* _SC_OPEN_MAX : 프로세스당 열 수 있는 최대 파일 수
* _SC_PAGESIZE : 시스템 메모리의 페이지 크기
* _SC_VERSION : 시스템이 지원하는 POSIX.1의 버전
#### 예제 196 : 시스템 자원 정보 검색(sysconf(3))
```C
#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("_SC_ARG_MAX : %ld\n", sysconf(_SC_ARG_MAX));
    printf("_SC_CLK_TCK : %ld\n", sysconf(_SC_CLK_TCK));
    printf("_SC_OPEN_MAX : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("_SC_LOGIN_NAME_MAX : %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
}
```
```
$ sh test.sh
_SC_ARG_MAX : 2097152
_SC_CLK_TCK : 100
_SC_OPEN_MAX : 8192
_SC_LOGIN_NAME_MAX : 256
```
#### 파일과 디렉터리 자원 검색 : fpathconf(3), pathconf(3)
```C
#include<unistd.h>
long fpathconf(int fd, int name);
long pathconf(const char* path, int name);
```
* 인자 설명
    * fd : 파일 기술자
    * path : 파일/디렉터리 경로
    * name : 검색할 정보를 지정하는 상수
* fpathconf(3)
    * 열린 파일의 파일기술자를 인자로 받아 파일과 관련된 자원값 검색
    * 실패시 : -1 리턴
* pathonf(3)
    * 파일/디렉터리 경로를 인자로 받아 자원값 검색
    * 성공시 : 자원값/옵션값 리턴
    * 실패시 : -1 리턴
#### fpathconf(3), pathconf(3) 주요 상수
* _PC_LINK_MAX : 파일에 가능한 최대 링크 수
* _PC_NAME_MAX : 파일명에 최대 길이를 바이트 크기로 푯
* _PC_PATH_MAX : 상대 경로명의 최대 길이를 바이트로 표시
#### 예제 198 : 디렉터리 자원 검색(pathconf(3))
```C
#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("_PC_LINK_MAX : %ld\n", pathconf(".", _PC_LINK_MAX));
    printf("_PC_NAME_MAX : %ld\n", pathconf(".", _PC_NAME_MAX));
    printf("_PC_PATH_MAX : %ld\n", pathconf(".", _PC_PATH_MAX));
}
```
```
$ sh test.sh
_PC_LINK_MAX : 65000
_PC_NAME_MAX : 255
_PC_PATH_MAX : 4096
```