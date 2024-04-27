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
* 200 : 로그인명, UID 검색(getlogin(3), getuid(2), geteuid(2))
* 204 : 사용자 이름 검색(getpwuid(3))
* 205 : 사용자 정보 검색(getpwname(3))
* 206 : 특정 사용자 정보 읽기(getpwent(3))
* 210 : 사용자 패스워드 정보 검색하기(getspname(3))
* 211 : 패스워드 정보 검색(getspent(3))
* 212 : GID, EGID 검색(getgid(2), getegid(2))
* 215 : 그룹 정보 검색(getgrnam(3))
* 216 : 그룹 정보 읽기(getgrent(3))
* 220 : 로그인명과 터미널 정보 출력(getutent(3))
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
* 시스템 정보를 나타내는 상수를 인자로 받아 설정되어 있는 시스템 자원값/옵션값을 리턴
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

## 5.3 사용자 정보 검색
### 개요
* 리눅스 사용자 정보
    * 각 사용자에 관한 정보
    * 그룹에 관한 정보
    * 로그인 기록 정보
* 관련 파일
    * 패스워드 파일(/etc/passwd)
    * 섀도우 파일(/etc/shadow)
    * 그룹 파일(/etc/group)
    * 로그인 기록 파일(/var/run/utmp)
### 5.3.1 로그인명과 UID 검색
#### 개요
* 사용자 게정 등록시 '로그인명'과 '사용자 ID'가 지정됨
* 로그인명 검색 : getlogin(3)
* 사용자 ID(UID) 검색 : getuid(2), geteuid(2)
#### 로그인명 검색 : getlogin(3)
```C
#include<unistd.h>
char* getlogin(void);
```
* /var/run/utmp 파일을 검색하여 현재 프로세스를 실행한 사용자의 '로그인명'을 찾아 리턴
* 실행자가 로그아웃했거나 rsh(remote shell)등으로 원격에서 실행한 프로세스에서 실행한 경우 사용자명을 찾지 못하고 널 포인터를 리턴
#### UID 검색 : getuid(2), geteuid(2)
```C
#include<unistd.h>
#include<sys/types.h>
uid_t getuid(void); //실제 사용자 ID 리턴
uid_t geteuid(void); //유효 사용자 ID 리턴
```
* 실제 사용자 ID(RUDI(real UID)) : 로그인시 사용한 '로그인명'에 대응하는 '사용자 ID'로, 프로그램을 실행하는 사용자를 나타냄
* 유효 사용자 ID(EUID(effective UID)) : 프로세스에 대한 접근 권한을 부여할 때 사용, setuid(2)가 설정된 프로그램을 실행하거나 다른 사용자 ID로 변경할 경우 EUID가 달라짐
#### 예제 200 : 로그인명, UID 검색(getlogin(3), getuid(2), geteuid(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    uid_t uid = getuid();
    uid_t euid = geteuid();
    char* name = getlogin();
    
    printf("uid : %d\n", (int)uid);
    printf("euid : %d\n", (int)euid);
    printf("name : %s\n", name);
}
```
```
$ sh test.sh
uid : 1000
euid : 1000
name : *********
```
### 5.3.2 패스워드 파일 검색
#### /etc/passwd
* /etc/passwd : 로그인명, UID, GID, 사용자의 홈 디렉터리, 로그인 셸 등 사용자에 관한 기본정보가 들어있음
* 사용자 정보를 각 행에 저장하며 각 행에는 ':'으로 구분된 정보가 있음
```
$ cat /etc/passwd
(...)
*********:x:1000:1000:*********,,,:/home/*********:/bin/bash
```
* 로그인 ID : 패스워드 : UID : GID : 계정 설명 : 홈 디렉터리 : 로그인 셸
* 리눅스에서는 사용자 계정 등록시 UID와 같은 값으로 GID 생성
#### passwd 구조체
* passwd 구조체 : /etc/passwd 파일의 정보를 읽어오기 위해 사용하는 구조체
* <pwd.h>에 정의되어 있음
```C
struct passwd{
    char* pw_name;      //로그인명 저장
    char* pw_passwd;    //암호 저장(최근 대부분의 리눅스는 시스템 암호를 별도의 암호를 별도의 파일(/etc/shadow)에 저장하므로 의미 없음)
    uid_t pw_uid;       //UID 저장
    gid_t pw_gid;       //기본 그룹 GID 저장
    char* pw_gecos;     //사용자 실명이나 기타 정보 저장
    char* pw_dir;       //홈 디렉터리 저장
    char* pw_shell;     //로그인 셸 저장
};
```
#### UID로 /etc/passwd 파일 읽기 : getpwuid(3)
```C
#include<sys/types.h>
#include<pwd.h>
struct passwd* getpwuid(uid_t uid);
```
* 성공시 : passwd 구조체에 결과를 저장하고 주소를 리턴
* 실패시 : 널 포인터 리턴
#### 예제 204 : 사용자 이름 검색(getpwuid(3))
```C
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<stdio.h>

int main(void){
    struct passwd* pw = getpwuid(getuid());

    printf("uid : %d\n", (int)((*pw).pw_uid));
    printf("name : %s\n", (*pw).pw_name);
}
```
```
$ sh test.sh
uid : 1000
name : *********
```
#### 이름으로 passwd 파일 읽기 : getpwnam(3)
```C
#include<sys/types.h>
#include<pwd.h>
struct passwd* getpwnam(const char* name);
```
* '로그인명'을 인자로 받아 검색 수행
* 성공시 : passwd 구조체에 결과를 저장하고 주소를 리턴
* 실패시 : 널 포인터 리턴
#### 예제 205 : 사용자 정보 검색(getpwname(3))
```C
#include<sys/types.h>
#include<pwd.h>
#include<stdio.h>

int main(void){
    struct passwd*pw = getpwnam("xxxxxxxxx");
    printf("uid : %d\n", (int)((*pw).pw_uid));
    printf("home dir : %s\n", (*pw).pw_dir);
}
```
```
$ sh test.sh
uid : 1000
home dir : /home/xxxxxxxxx
```
#### /etc/passwd 파일을 순차적으로 읽기 : getpwent(3), setpwent(3), endpwent(3), fgetpwent(3)
```C
#include<sys/types.h>
#include<pwd.h>
struct passwd* getpwent(void);
void setpwent(void);
void endpwent(void);
struct passwd* fgetpwent(FILE* stream);
```
* getpwent(3) : /etc/passwd 파일에서 사용자 정보를 순차적으로 읽어오며 파일의 끝을 만나면 널 포인터 리턴
* setpwent(3) : /etc/passwd 파일 오프셋을 파일의 처음에 놓음
* endpwent(3) : /etc/passwd 파일을 닫음
* fgetpwent(3) : 파일 포인터가 가리키는 파일에서 사용자 정보를 읽어옴
#### 예제 206 : 특정 사용자 정보 읽기(getpwent(3))
```C
#include<pwd.h>
#include<stdio.h>

int main(void){
    struct passwd* pw;
    int n;

    for(n = 0; n < 3; n++){
        pw = getpwent();
        printf("uid : %d, login name : %s\n", (int)((*pw).pw_uid), (*pw).pw_name);
    }
}
```
```
$ sh test.sh
uid : 0, login name : root
uid : 1, login name : daemon
uid : 2, login name : bin
```
### 5.3.3 섀도우 파일 검색
#### 개요
* 초기 유닉스 : 패스워드 정보를 /etc/passwd에 저장했음
    * 누구나 읽을 수 있어 보안 문제 발생 가능
* 현재 대부분의 유닉스/리눅스 시스템 : /etc/shadow에 별도로 저장
    * root 사용자만 실행 가능
#### /etc/shadow 파일의 구조
* 사용자 정보를 각 행에 저장하며 각 행에는 ':'으로 구분된 정보가 있음
* 로그인명 : 패스워드 : 최종 변경일 : min : max : warn : inactive : expire : flag
#### spwd 구조체
* spwd 구조체 : /etc/shadow 파일의 정보를 읽어오기 위해 사용하는 구조체
* <shadow.h>에 정의되어 있음
```C
struct spwd{
    char* sp_namp;  //로그인명
    char* sp_pwdp;  //암호화된 패스워드
    int sp_lstchg;  //last change : 패스워드를 변경한 날짜 정보(1970-01-01부터 일수로 계산해 저장)
    int sp_min;     //변경된 패스워드를 사용해야 하는 최소 일 수
    int sp_max;     //현재 패스워드를 사용할 수 있는 최대 일 수
    int sp_warn;    //패스워드를 변경할 날이 되기 전에 경고를 시작하는 일 수
    int sp_inact;   //패스워드가 만료된 이후 사용자 계정이 정지될 때까지의 일 수
    int sp_expire;  //사용자 계정이 만료되는 날짜 정보(1970-01-01부터 일수로 계산해 저장)
    unsgined int sp_flag; //나중에 사용하기 위해 예약된 공간(현재는 사용하지 않음)
};
```
#### /etc/shadow 파일 검색 : getspnam(3)
```C
#include<shadow.h>
struct spwd* getspnam(const char* name);
```
* 로그인명을 인자로 지정해 spwd 구조체 주소 리턴
#### 예제 210 : 사용자 패스워드 정보 검색하기(getspname(3))
```C
#include<shadow.h>
#include<stdio.h>

int main(void){
    struct spwd* sp = getspnam("shagyeong");
    printf("namp : %s\n", (*sp).sp_namp);
    printf("pwdp : %s\n", (*sp).sp_pwdp);
    printf("lstchg : %ld\n", (*sp).sp_lstchg);
}
```
```
$ sh test.sh
namp : *********
pwdp : $*$***$(...)
lstchg : *****
```
#### /etc/shadow 파일을 순차적으로 읽기 : etspent(3), setspent(3), endspent(3), fgetspent(3)
```C
struct spwd* getspent(void);
void setspent(void);
void endspent(void);
struct spwd* fgetspent(FILE* stream);
```
* getspent(3) : /etc/shadow 파일에서 패스워드 정보를 순차적으로 읽어오며 파일의 끝을 만나면 널 포인터 리턴
* setspent(3) : /etc/shadow 파일 오프셋을 파일의 처음에 놓음
* endspent(3) : /etc/shadow 파일을 닫음
* fgetspent(3) : 파일 포인터가 가리키는 파일에서 패스워드 정보를 읽어옴
#### 예제 211 : 패스워드 정보 검색(getspent(3))
```C
#include<shadow.h>
#include<stdio.h>

int main(void){
    struct spwd* sp;
    int n;

    for(n = 0; n < 3; n++){
        sp = getspent();
        printf("login name : %s, pw : %s\n", (*sp).sp_namp, (*sp).sp_pwdp);
    }
}
```
```
$ sh test.sh
login name : root, pw : !
login name : daemon, pw : *
login name : bin, pw : *
```
### 5.3.4 그룹 정보 검색
#### 개요
* 리눅스에서 사용자는 하나 이상의 그룹에 속함
* 그룹도 사용자와 같이 그룹명, 그룹 ID가 있음
#### 그룹 ID 검색하기 : getgid(2), getegid(2)
```C
#include<unistd.h>
#include<sys/types.h>
gid_t getgid(void);
gid_t getegid(void);
```
* getgid(2) : 실제 그룹 ID(RGID) 리턴
* getegid(2) : 유효 그룹 ID(EGID) 리턴
* EGID는 프로세스 접근 권한을 부여할 때 사용
#### 예제 212 : GID, EGID 검색(getgid(2), getegid(2))
```C
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    gid_t gid = getgid();
    gid_t egid = getegid();

    printf("gid : %d, egid : %d\n", (int)gid, (int)egid);
}
```
```
$ sh test.sh
gid : 1000, egid : 1000
```
### 5.3.5 그룹 정보 검색
#### 개요
* 그룹 정보를 /etc/group 파일에 별도로 저장
* 기본 그룹 : /etc/passwd 파일의 GID 항목
* 2차 그룹 : /etc/group 파일에서 지정
#### /etc/group 파일의 구조
* 그룹 정보를 각 행에 저장하며 각 행에는 ':'으로 구분된 정보가 있음
#### group 구조체
* group 구조체 : 그룹 정보 검색을 위해 사용하는 구조체
* <grp.h>에 정의되어 있음
```C
struct group{
    char* gr_name;      //그룹명
    char* gr_passwd;    //그룹 패스워드
    gid_t gr_gid;       //그룹 ID 번호
    char** gr_mem;       //그룹 멤버인 로그인명을 저장(문자열을 가리킴)
};
```
* 그룹 패스워드
    * 일반적으로 공백임
    * 그룹 패스워드 지정시 (사용자 패스워드처럼) 암호화된 문자가 저장됨
    * 그룹 패스워드를 설정하는 명령이 없어 사용자 패스워드 파일에서 복사해 삽입해야 함
    * 그룹 패스워드가 지정되어 있으면 newgrp 명령을 사용해 다른 그룹으로 변경시 이 패스워드를 입력해야 함
#### /etc/group 파일 검색 : etgrnam(3), getgrgid(3)
```C
#include<sys/types.h>
#include<grp.h>
struct group* getgrnam(const char* name);
struct group* getgrgid(gid_t gid);
```
* getgrnam(3) : 그룹명으로 그룹 정보 검색
* getgrgid(3) : GID로 그룹 정보 검색
* group 구조체에 결과 저장 후 주소 리턴
#### 예제 215 : 그룹 정보 검색(getgrnam(3))
```C
#include<grp.h>
#include<stdio.h>

int main(void){
    struct group* grp =getgrnam("adm");;
    int n = 0;

    printf("group name : %s\n", (*grp).gr_name);
    printf("gid : %d\n", (int)((*grp).gr_gid));

    printf("members\n");
    while((*grp).gr_mem[n] != NULL)
        printf("%s ", (*grp).gr_mem[n++]);
    printf("\n");
}
```
```
$ sh test.sh
group name : adm
gid : 4
members
syslog ********* 
```
#### /etc/group 파일을 순차적으로 읽기 : getgrent(3), setgrent(3), endgrent(3), fgetgrent(3)
```C
#include<sys/types.h>
#include<grp.h>
struct group* getgrent(void);
void setgrent(void);
void endgren(void);
struct group* fgetgrent(FILE* stream);
```
* getgrent(3) : /etc/group 파일에서 그룹 정보를 순차적으로 읽어오며 파일의 끝을 만나면 널 포인터 리턴
* setgrent(3) : /etc/group 파일 오프셋을 파일의 처음에 놓음
* endgren(3) : /etc/group 파일을 닫음
* fgetgrent(3) : 파일 포인터가 가리키는 파일에서 그룹 정보를 읽어옴
#### 예제 216 : 그룹 정보 읽기(getgrent(3))
```C
#include<grp.h>
#include<stdio.h>

int main(void){
    struct group* grp;
    int n, m;

    for(n = 0; n < 3; n++){
        grp = getgrent();
        printf("group name :%s, gid : %d ", grp->gr_name, (int)grp->gr_gid);

        m = 0;
        printf("members : ");
        while(grp->gr_mem[m] != NULL)
            printf("%s ", grp->gr_mem[m++]);
        printf("\n");
    }
}
```
```
$ sh test.sh
group name :root, gid : 0 members : 
group name :daemon, gid : 1 members : 
group name :bin, gid : 2 members : 
```
### 5.3.6 로그인 기록 검색
#### 개요
* who(1) : 현재 시스템에 로그인한 사용자 정보 검색
* last(1) : 시스템의 부팅 시각 정보, 사용자 로그인 기록 등 검색
* /var/run/utmp, /var/log/wtmp : 우분투 리눅스의 로그인 정보 저장 위치
    * 바이너리 형태로 저장되어 있어 텍스트 편집기로 내용 확인 불가
    * 파일에서 정보를 읽어오려면 파일 구조체와 관련된 함수가 필요함
#### utmp 구조체
* utmp, wtmp 파일은 구조가 같음 - 두 파일을 읽기 위해 utmp 구조체를 사용함
* <utmp.h>에 정의되어 있음
```C
struct utmp{
    short ut_type;              //현재 읽어온 항목에 저장된 데이터 형식
    pid_t ut_pid;               //로그인 프로세스의 PID
    char ut_line[UT_LINESIZE];  //사용자가 로그인한 장치명
    char ut_id[4];              //터미널 이름이거나 /etc/inittab 파일에서 읽어온 ID
    char ut_user[UT_NAMESIZE];  //사용자명 저장
    char ut_host[UT_HOSTSIZE];  //
    struct exit_status ut_exit; //프로세스가 DEAD_PROCSS인 경우 프로세스의 종료 상태 저장
    long ut_session;            //해당 정보의 세션 번호
    struct timeval ut_tv;       //해당 정보를 마지막으로 변경한 시각
    int32_t ut_addr_v6[4];      //원격 접소간 경우 원격 호스트의 인터넷 주소 저장
    char __unused[20];          //추후 사용을 위해 예약해둔 부분
};
```
* ut_type 상수
    * 0(EMPTY) : 빈 항목
    * 1(RUN_LVL) : 시스템의 런 레벨이 변경되었음을 나타냄
    * 2(BOOT_TIME) : 시스템 부팅 시각
    * 3(NEW_TIME) : 시스템 클럭이 변경된 다음의 시간 정보
    * 4(OLD_TIME) : 시스템 클럭이 변경되기 전의 시간 정보
    * 5(INIT_PROCESS) : init이 생성한 프로세스임을 나타냄
    * 6(LOGIN_PROCESS) : 사용자 록인을 위한 세션 리더 프로세스
    * 7(USER_PROCESS) : 일반 프로세스
    * 8(DEAD_PROCESS) : 종료한 프로세스
    * 9(ACCOUNTING) : 사용하지 않는 항목
* ut_exit : exit_status 구조체에 정보 저장
    * man -s 5 utmp에서 확인
    ```C
    struct exit_status{
        short e_termination;
        short e_exit;
    };
    ```
#### /var/log/utmp 파일을 순차적으로 읽기 : getutent(3), setutent(3), endutent(3), utmpname(3)
```C
#include<utmp.h>
struct utmp* getutent(void);
vid setutent(void);
void endutent(void);
int utmpname(const char* file);
```
* getutent(3) : /var/run/utmp 파일에서 로그인 정보를 순차적으로 읽어오며 파일의 끝을 만나면 널 포인터 리턴
* setutent(3) : /var/run/utmp 파일 오프셋을 파일의 처음에 놓음
* endutent(3) : /var/run/utmp 파일을 닫음
* utmpname(3) : 로그인 정보 파일을 file로 지정한 다른 파일로 변경
    * 예시 : last(1)에서 사용하는 /var/adm/wtmp로 변경시 사용
#### 예제 220 : 로그인명과 터미널 정보 출력(getutent(3))
```C
#include<sys/types.h>
#include<utmp.h>
#include<stdio.h>

int main(void){
    struct utmp* ut;
    
    while((ut = getutent()) != NULL){
        if(ut->ut_type != USER_PROCESS)
            continue;
        printf("%s %s\n", ut->ut_user, ut->ut_line);
    }
}
```
```
$ sh test.sh
********* ****
```

## 5.4 시간 관리 함수
### 개요
* 리눅스 시스템의 시간 정보 : 1970-01-01 00:00:00부터 현재까지 경과한 시간을 초 단위로 저장하고 이를 기준으로 시간 정보를 관리함
### 5.4.1 기본 시간 정보 확인
#### 초단위로 현재 시간 정보 얻기 : time(2)
```C
#include<time.h>
time_t time(time_t* tloc);
```
* 인자 설명
    * tloc : 검색한 시간 정보를 저장할 주소
* 1970-01-01 00:00:00부터 현재까지 경과된 시간을 초 단위로 알려줌
* 성공시
    * tloc이 NULL이 아날 때 : tloc이 가리키는 주소에 시간 정보를 저장
    * tloc이 NULL일 때 : 시간 정보를 리턴
* 실패시 : -1 리턴
#### 예제 222 : 초 단위 시간 정보 얻기(time(2))
```C
#include<sys/types.h>
#include<time.h>
#include<stdio.h>

int main(void){
    time_t tloc;
    time(&tloc);
    printf("time : %d\n", (int)tloc);
}
```
```
$ sh test.sh
time : 1*********
```

* 222 : 마이크로초 단위로 시간 정보 얻기(gettimeofday(3))
* 224 : 시간대 설정(tzset(3))
* 227 : 초 단위 시간 정보 분해(gmtime(3), localtime(3))
* 228 : 초 단위 시간으로 역산(mktime(3))
* 230 : 초 단위 시간을 변환하여 출력하기(ctime(3))
* 231 : tm 구조체 시간을 변환하여 출력하기(asctime(3))
* 232 : 출력 형식 기호를 사용하여 출력하기(strftime(3))