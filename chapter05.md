# 5장 시스템 정보
## 5.1 개요

## 5.2 시스템 정보 검색
### 5.2.0 개요
#### 리눅스 시스템 정보
- 리눅스 시스템에서 제공하는 구조체/매개변수를 이용해 환경 정보를 검색할 수 있다
- 운영체제에 관한 정보
- 호스트명 정보
- 하드웨어 종류에 대한 정보
- 자원값: 최대 프로세스 개수, 프로세스당 최대 파일 개수, 메모리 페이지 크기, ...
### 5.2.1 운영체제 기본 정보 검색
#### 운영체제 정보 검색: uname(1)
- ```
  $ uname
  Linux
  $ uname -a
  Linux shagyeong 6.5.0-35-generic #35~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Tue May  7 09:00:52 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
  ```
- 옵션 -a: 현재 시스템에 설치되어 있는 OS 정보 출력
#### 운영체제 정보 검색: uname(2)
```C
#include<sys/utsname.h>
int uname(struct utsnme* buf);
```
- 운영체제 정보를 검색해 utsname 구조체에 저장
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 구조체 utsname
- <sys/utsname.h>에 정의됨
- man -s 2 uname으로 확인 가능
    ```
    $ man -s 2 uname
    (...)
    struct utsname {
        char sysname[];     //OS명
        char nodename[];    //네트워크를 통한 통신에 사용하는 시스템 이름 저장
        char release[];     //OS 릴리즈 번호 저장
        char version[];     //OS 버전 번호 저장
        char machine[];     //하드웨어 아키텍처(표준 이름) 저장
        char domainname[];  //
    };
    ```
#### 예제: 운영체제 정보 검색(uname(2))
- test.c
    ```C
    #include<sys/utsname.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        struct utsname uts;
        uname(&uts);
        printf("sysname: %s\n", uts.sysname);
        printf("nodename: %s\n", uts.nodename);
        printf("release: %s\n", uts.release);
        printf("version: %s\n", uts.version);
        printf("machine: %s\n", uts.machine);
    }
    ```
- demo
    ```
    $ ./test
    sysname: Linux
    nodename: shagyeong
    release: 6.5.0-35-generic
    version: #35~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Tue May  7 09:00:52 UTC 2
    machine: x86_64
    ```
### 5.2.2 시스템 자원 정보 검색
#### 자원 최대값
- <limits.h>에 정의됨
#### 시스템 자원 정보 검색: sysconf(3)
```C
#include<unistd.h>
long sysconf(int name);
```
- name: 검색할 정보를 나타내는 상수
- 성공시: 설정된 시스템 자원값/옵션값 리턴
- 오류시: -1 리턴
#### 주요 상수
- <sys/unistd.h>에 정의됨
    |상수|기능|
    |---|---|
    |_SC_ARG_MAX|exec() 함수군 인자 최대 크기|
    |_SC_CHILD_MAX|한 UID에 허용되는 최대 프로세스 개수|
    |_SC_HOST_NAME_MAX|호스트명 최대 길이|
    |_SC_LOGIN_NAME_MAX|로그인명 최대 길이|
    |_SC_CLK_TCK|초당 클록 틱 수|
    |_SC_OPEN_MAX|프로세스당 열 수 있는 최대 파일 수|
    |_SC_PAGESIZE|시스템 메모리의 페이지 크기|
    |_SC_VERSION|시스템이 지원하는 POSIX.1의 버전|
#### 예제: 시스템 자원 정보 검색(sysconf(3))
- test.c
    ```C
    #include<unistd.h>
    #include<stdio.h>

    int main(void){
        printf("ARG_MAX: %ld\n", sysconf(_SC_ARG_MAX));
        printf("CLK_TCK: %ld\n", sysconf(_SC_CLK_TCK));
        printf("OPEN_MAX: %ld\n", sysconf(_SC_OPEN_MAX));
        printf("LOGIN_NAME_MAX: %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
    }
    ```
- demo
    ```
    $ ./test
    ARG_MAX: 2097152
    CLK_TCK: 100
    OPEN_MAX: 8192
    LOGIN_NAME_MAX: 256
    ```
#### 파일과 디렉터리 자원 검색: fpathconf(3), pathconf(3)
```C
#include<unistd.h>
long fpathconf(int fd, int name);
long pathconfF(const char* path, int name);
```
- fpathconf(3): 파일 기술자를 인자로 받아 자원 검색
- pathconf(3): 경로를 인자로 받아 파일 검색
#### 주요 상수
- <unistd.h>에 정의됨
    |상수|기능|
    |---|---|
    |_PC_LINK_MAX|파일에 가능한 최대 링크 수|
    |_PC_NAME_MAX|파일명의 최대 길이를 바이트 크기로 표시|
    |_PC_PAHT_MAX|상대 경로명의 최대 길이를 바이트 크기로 표시|
#### 예제: 현재 디렉터리 자원 검색(pathcon(3))
- test.c
    ```C
    #include<unistd.h>
    #include<stdio.h>

    int main(void){
        printf("_PC_LINK_MAX: %ld\n", pathconf(".", _PC_LINK_MAX));
        printf("_PC_NAME_MAX: %ld\n", pathconf(".", _PC_NAME_MAX));
        printf("_PC_PATH_MAX: %ld\n", pathconf(".", _PC_PATH_MAX));
    }
    ```
- demo
    ```
    $ ./test
    _PC_LINK_MAX: 65000
    _PC_NAME_MAX: 255
    _PC_PATH_MAX: 4096
    ```

## 5.3 사용자 정보 검색

## 5.4 시간 관리 함수
