# 2장 디렉터리 다루기
### 학습목표
* 함수를 사용해 파일해 관한 정보를 검색할 수 있다.
* 하드 링크와 심벌릭 링크 파일을 이해하고 관련 함수를 사용할 수 있다.
* 함수를 사용해 파일 사용 권한을 검색하고 조정할 수 있다.
### 중요 개념
* 3.1 개요 : 구조체 stat, 링크
* 3.2 파일 정보 검색 : 
* 3.3 파일 접근 권한 제어 : 
* 3.4 링크 파일 생성 : 

## 예제 명세
### 3.2 파일 정보 검색
* 095 : 파일명으로 inode 검색하기(stat(2))
* 097 : 파일 기술자로 파일 정보 검색하기(fstat(2))
### 3.3 파일 접근 권한 제어
* 099 : 상수를 이용해 파일 종류 검색하기
* 000 : ...
### 3.4 링크 파일 생성
* 000 : ...
* 000 : ...

## 3.1 개요
### 2장 복습
* 파일의 구분
    * 일반 파일
    * 특수 파일
    * 디렉터리
* inode에 저장되는 파일 정보
    * 파일 종류, 접근 권한, 하드 링크 개수, 소유자 UID, GID, 파일의 크기, 파일 접근 및 수정 시각, inode 변경 시각, ...
### stat 구조체
* inode 정보를 검색하면 sys/stat.h에 정의되어 있는 stat 구조체 저장됨
### 파일 정보 검색 함수
* 파일 정보 검색 : stat(2), fstat(2)
### 파일 접근 권한 함수
* stat 구조체를 직접 이용하거나 함수 이용
* 파일 접근 권한 확인 : access(2)
* 파일 접근 권한 변경 : chmod(2), fchmod(2)
### 링크
* **링크** : 기존 파일이나 디렉터리에 접근할 수 있는 새로운 이름
* 링크 사용시 복잡한 파일명에 간단한 파일명으로 접근 가능
* 특수 파일에 같은 링크 파일명을 제공해 동일한 방식으로 접근 가능
* 링크의 구분
    * 하드 링크(hard link) : 기존 파일과 동일한 inode 사용
    * 심벌릭 링크(symbolic link) : 기존 파일에 접근할 수 있는 다른 파일을 만듬, 기존 파일과 다른 inode를 사용
### 링크 함수
* 하드 링크 생성 : link(2)
* 심벌릭 링크 생성 : symlink(2)
* 심벌릭 링크 정보 검색 : lstat(2)
* 심벌릭 링크 내용 읽기 : readlink(2)
* 심벌릭 링크 원본 파일의 경로 검색 : realpath(3)
* 링크 끊기 : unlink(2)

## 3.2 파일 정보 검색
### 개요
* 2장의 내용 : 파일의 정보는 inode에 저장되어 있음
* inode 검색 함수 : stat(2), lstat(2), fstat(2)
* lstat() : '심벌릭 링크 파일'의 inode를 검색하는 함수-4절에 등장
### 파일명으로 파일 정보 검색 : stat(2)* 000 : ...
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int stat(const char* pathname, struct stat* statbuf);
```
* 인자 설명
    * pathname : 정보를 알고자 하는 파일명
    * statbuf : 검색한 파일 정보를 저장할 구조체 주소
* pathname에 지정한 파일의 정보를 검색
* 성공시 : **stat 구조체에 파일 정보를 저장**하고 0을 리턴
* 실패시 : -1 리턴
* pathname에 지정한 파일에 대한 읽기/쓰기 권한이 있어야 하는것은 아님
    * 단, 파일에 이르는 경로 상 각 디렉터리에 대한 읽기 권한은 있어야 함
* 파일 정보를 검색하는데 가장 많이 사용하는 함수임
### stat 구조체
* stat(2) 함수로 검색한 inode 정보는 stat 구조체에 저장됨
* stat 구조체 정의 또는 <stat.h>의 위치는 배포판 또는 유닉스 종류에 따라 차이가 있음
* stat 구조체의 세부 구조
```
$ man -s 2 stat
struct stat{
    dev_t       st_dev;         # 저장되어있는 장치 번호
    ino_t       st_ino;         # inode 번호
    mode_t      st_mode;        # 종류와 접근 권한
    nlink_t     st_nlink;       # 하드 링크의 개수
    uid_t       st_uid;         # 소유자의 UID
    gid_t       st_gid;         # 소유 그룹의 GID
    dev_t       st_rdev;        # 장치 파일일 경우 주/부 장치번호 저장
    off_t       st_size
    blksize_t   st_blksize;     # 파일 입출력시 버퍼 크기 저장
    blkcnt_t    st_blocks;      # 파일에 할당된 파일 시스템의 블록 수(512바이트)
    struct timespec st_atim;    # 마지막으로 파일을 읽거나 실행한 시각
    struct timespec st_mtim;    # 마지막으로 파일의 내용을 변경(쓰기)한 시각
    struct timespec st_ctim;    # 마지막으로 inode의 내용을 변경한 시각(소유자/그룹 변경, 파일 크기 변경, 링크 개수 변경 등)

    # 리눅스 2.6 이전 버전과의 호환성을 위해 타임스탬프 값을 초 단위 값으로 매핑해 정의
    #define st_atime st_atim.tv_sec
    #define st_mtime st_mtim.tv_sec
    #define st_ctime st_ctim.tv_sec
}
```
* 구조체 timespec : 초와 나노초 저장을 위한 구조체
    * 리눅스 커널 2.6부터 지원
    * 1970년 1월 1일 이후
### 예제 095 : 파일명으로 inode 검색하기(stat(2))
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    stat("linux.txt", &statbuf);

    printf("inode = %d\n", (int)statbuf.st_ino);
    printf("mode = %d\n", (unsigned int)statbuf.st_mode);
    printf("nlink = %d\n", (unsigned int)statbuf.st_nlink);
    printf("uid = %d\n", (int)statbuf.st_uid);
    printf("gid = %d\n", (int)statbuf.st_gid);
    printf("size = %d\n", (int)statbuf.st_size);
    printf("blksize = %d\n", (int)statbuf.st_blksize);
    printf("blocks = %d\n", (int)statbuf.st_blocks);

    printf("time = %d\n", (int)statbuf.st_atime);
    printf("time = %d\n", (int)statbuf.st_mtime);
    printf("time = %d\n", (int)statbuf.st_ctime);
}
```
### 파일 기술자로 파일 정보 검색 : fstat(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int fstat(int fd, struct stat* statbuf);
```
* 인자 설명
    * fd : 열려있는 파일 기술자
    * statbuf : 검색한 파일 정보를 저장할 구조체 주소
* 파일 경로 대신 현재 열려있는 파일의 파일 기술자를 인자로 받아 파일 정보를 검색함
* 성공시 : **stat 구조체에 파일 정보를 저장**하고 0을 리턴
* 실패시 : -1 리턴
### 예제 097 : 파일 기술자로 파일 정보 검색하기(fstat(2))
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd = open("linux.txt", O_RDONLY);;
    struct stat statbuf;
    
    if(fd == -1){
        perror("open: linux.txt");
        exit(1);
    }

    fstat(fd, &statbuf);

    printf("inode = %d\n", (int)statbuf.st_ino);
    printf("uid = %d\n", (int)statbuf.st_uid);
    close(fd);

    exit(0);
}
```
```
$ main.out
inode = 414028
uid = 1000
```

## 3.3 파일 접근 권한 제어
### 개요
* mode_t st_mode : 파일의 종류와 접근 권한 정보가 저장됨
* st_mode의 값 해석을 위해 sys/stat.h에 정의된 상수와 매크로를 이용해야 함
### 3.3.1 st_mode의 구조
#### mode_t(st_mode의 자료형)
* unsigned int로 정의됨
* 16비트 사용
### st_mode의 구조
* 파일 종류(4비트) *\*('-', 'd', 'b', 'c', 'l')*
* 특수 접근 권한(3비트) : setuid, setgid, sticky bit
* 소유자 접근 권한(3비트) : *\*\*r, w, x*
* 그룹 접근 권한(3비트) : r, w, x
* 기타 사용자 접근 권한(3비트) : r, w, x
* \*파일 종류 식별 문자는 2.2.1 참고
* \*\*r(read : 읽기 권한), w(write : 쓰기 권한), x(execute : 실행 권한)
#### sys/stat.h의 상수/매크로
* 위 구조로 저장된 값과 상수를 AND 연산한 결과를 추출함
### 3.3.2 파일의 종류 검색
#### 상수를 이용한 파일 종류 검색
* 상수의 값은 8진수임
* 0170000(S_IFMT) : 파일의 종류 비트를 가져오기 위한 **비트 마스크**
    * 17(8) = 111(2)이므로 AND연산을 하면 st_mode의 값과 AND 연산을 하면 파일 종류 부분만 남음
* 0140000(S_IFSOCK) : 소켓 파일
* 0120000(S_IFLNK) : 심벌릭 링크 파일
* 0100000(S_IFREG) : 일반 파일
* 0060000(S_IFBLK) : 블록 장치 특수 파일
* 0040000(S_IFDIR) : 디렉터리
* 0020000(S_IFCHR) : 문자 장치 특수 파일
* 0010000(S_IFIFO) : FIFO 파일
#### 예제 099 : 상수를 이용해 파일 종류 검색하기
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    int kind;

    stat("linux.txt", &statbuf);
    kind = statbuf.st_mode & __S_IFMT;

    printf("mode = %o\n", (unsigned int)statbuf.st_mode);
    printf("kind = %o\n", kind);

    switch(kind){
    case __S_IFLNK:
        printf("symbolic link\n");
        break;
    case __S_IFDIR:
        printf("directory\n");
        break;
    case __S_IFREG:
        printf("regular file\n");
        break;
    }
}
```
```
mode = 100664
kind = 100000
regular file
```
#### 매크로를 이용한 파일 종류 검색
* POSIX 표준 매크로
    * S_ISLNK(m) : (((m) & S_IFMT) == S_IFLNK)
    * S_ISREG(m) : (((m) & S_IFMT) == S_IFREG)
    * S_ISDIR(m) : (((m) & S_IFMT) == S_IFDIR)
    * S_ISCHR(m) : (((m) & S_IFMT) == S_IFCHR)
    * S_ISBLK(m) : (((m) & S_IFMT) == S_IFBLK)
    * S_ISFIFO(m) : (((m) & S_IFMT) == S_IFFIFO)
    * S_ISSOCK(m) : (((m) & S_IFMT) == S_IFSOCK)
* 비트 마스크(S_IFMT)와 AND 연산 결과를 상수와 비교해 파일의 종류를 판다함
#### 예제 101 : 매크로를 이용해 파일 종류 검색하기
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    int kind;
    stat("linux.txt", &statbuf);

    printf("mode = %d\n", (unsigned int)statbuf.st_mode);
    
    if(S_ISLNK(statbuf.st_mode))
        printf("LNK\n");
    if(S_ISDIR(statbuf.st_mode))
        printf("DIR\n");
    if(S_ISREG(statbuf.st_mode))
        printf("REG\n");
}
```
```
$ main.out
mode = 33204
REG
```
### 3.3.3 파일 접근 권한 검색
#### POSIX 표준