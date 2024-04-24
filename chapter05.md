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
* 198 : 디렉터리 자원 검색(fpathconf(3), pathconf(3))
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