# 2장 디렉터리 다루기
### 학습목표
* 함수를 사용해 파일해 관한 정보를 검색할 수 있다.
* 하드 링크와 심벌릭 링크 파일을 이해하고 관련 함수를 사용할 수 있다.
* 함수를 사용해 파일 사용 권한을 검색하고 조정할 수 있다.
### 중요 개념
* 3.1 개요 : 
* 3.2 파일 정보 검색 : 
* 3.3 파일 접근 권한 제어 : 
* 3.4 링크 파일 생성 : 

## 예제 명세
### 3.2 파일 정보 검색
* 095 : 파일명으로 inode 검색하기(stat(2))
* 097 : 파일 기술자로 파일 정보 검색하기(fstat(2))
### 3.3 파일 접근 권한 제어
* 099 : 상수를 이용해 파일 종류 검색하기
* 101 : 매크로를 이용해 파일 종류 검색하기
* 104 : 상수를 이용해 파일의 접근 권한 검색하기
* 106 : 함수를 이용해 접근 권한 검색하기(access(2))
* 108 : 파일명으로 접근 권한 변경하기(chmod(2))
### 3.4 링크 파일 생성
* 111 : 하드 링크 생성하기(link(2))
* 113 : 심벌릭 링크 생성하기(symlink(2))
* 114 : 심벌릭 링크의 정보 검색하기(lstat(2))
* 116 : 심벌릭 링크의 내용 읽기(readlink(2))
* 117 : 원본 파일의 경로 읽기(realpath(3))
* 118 : 링크 끊기(unlink(2))

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
#### 파일 접근 권한 검색 상수
* (0x800)S_ISUID : setuid 설정 확인
* (0x400)S_ISGID : setgid 설정 환인
* (0x200)S_ISVTX : sticky 비트 설정 확인
* (00400)S_ISREAD : 소유자의 읽기 권한 확인
* (00200)S_ISWRITE : 소유자의 쓰기 권한 확인
* (00100)S_ISEXEC : 소유자의 실행 권한 확인
* st_mode와 AND 연산으로 확인
* 그룹, 기타 사용자에 대한 접근 권한에 대한 상수는 별도로 정의되어 있지 않음
    * st_mode의 값 또는 상수값을 **비트 이동**시킨 후 연산 수행
    * ```st_mode & (S_IREAD >> 3)```
#### POSIX 파일 접근 권한 검색 상수
* POSIX에서 번거로운 시프트 연산 없는 상수를 정의함
* 읽기/쓰기/실행 권한
    * S_IRWXU(00700)
    * S_IRWXG(00070)
    * S_IRWXO(00007)
* 읽기 권한
    * S_IRUSR(00400)
    * S_IRGRP(00040)
    * S_IROTH(00004)
* 쓰기 권한
    * S_IWUSR(00200)
    * S_IWGRP(00020)
    * S_IWOTH(00002)
* 실행 권한
    * S_IXUSR(00100)
    * S_IXGRP(00010)
    * S_IXOTH(00001)
#### 예제 104 : 상수를 이용해 파일의 접근 권한 검색하기
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    
    stat("linux.txt", &statbuf);
    printf("mode = %o\n", (unsigned int)statbuf.st_mode);

    if((statbuf.st_mode & __S_IREAD) != 0)
        printf("rusr\n");
    if((statbuf.st_mode & __S_IREAD >> 3) != 0)
        printf("rgrp\n");
    if((statbuf.st_mode & __S_IREAD >> 6) != 0)
        printf("roth\n");
}
```
```
$ main.out
mode = 100664
rusr
rgrp
roth
```
#### 함수를 이용한 접근 권한 검색 : access(2)
```C
#include<unistd.h>

int access(const char* pathname, int mode);
```
* 인자 설명
    * pathname : 파일 경로
    * mode : 접근 권한
* pathname에 지정된 파일이 mode로 지정된 권한을 가지고 있는지 확인
* 단, EUID(effective user ID : 유효 사용자 ID)가 아닌 RUID(real user ID : 실제 사용자 ID)에 대한 접근 권한만 확인 가능함
* 성공시(접근 권한이 있을 시) : 0 리턴
* 오류가 있을 시 : -1 리턴
    * ENOENT : 해당 파일이 존재하지 않거나 심벌릭 링크의 경우 원본 파일이 없음
    * EACCES : 접근 권한이 없음
* mode 상수
    * <unistd.h>에 정의되어 있음
    * R_OK : 읽기 권한 확인
    * W_OK : 쓰기 권한 확인
    * X_OK : 실행 권한 확인
    * F_OK : 파일이 존재하는지 확인
#### 예제 106 : 함수를 이용해 접근 권한 검색하기(access(2))
```C
#include<sys/errno.h>
#include<unistd.h>
#include<stdio.h>

extern int errno;

int main(void){
    if(access("linuxxxx.txt", F_OK) == -1 && errno == ENOENT)
        printf("file not exitst\n");

    if(access("linux.txt", R_OK) == 0)
        printf("read permission is permitted\n");
    else if(access("linux.txt", R_OK) == -1 && errno == EACCES)
        printf("read permission is not permitted\n");
}
```
```
$ main.out
file not exitst
read permission is permitted
```
### 3.3.4파일 접근 권한 변경
#### 개요
* chmod(1) : 파일 접근 권한을 변경하는 명령
* chmod(2) : 파일 접근 권한을 변경하는 시스템 호출
* fchmod(2) : (파일 기술자를 이용하여)파일 접근 권한을 변경하는 시스템 호출
#### 파일명으로 접근 권한 변경 : chmod(2)
```C
#include<sys/stat.h>

int chmod(const char* pathname, mode_t mode);
```
* 인자 설명
    * pathname : 파일의 경로
    * mode : 접근 권한
* pahtname에 지정한 파일을 mode에 지정한 상수값으로 권한 변경
* 특수 접근 권한 변경시 3.3.3의 파일 접근 권한 상수를 이용함
    * S_ISUID
    * S_ISGID
    * S_ISVTX
* 소유자/그룹/기타 사용자의 접근 권한 변경시 3.3.3의 POSIX 파일 접근 권한 검색 상수를 이용함
* stat(2) 함수로 기존 권한을 읽고 권한 연산을 할 수 있음
    * 권한을 더할 때는 OR 연산
    * 권한 제거시 제거하려는 권한에 NOT 연산 후 AND 연산
```C
// 예시 : 그룹 쓰기 권한 추가 및 제거
mode |= S_IWGRP;
mode &= ~(S_IWGRP);
chmod(pahtname, mode); //mode 변경 후 chmod(2)를 호출해야 접근 권한이 적용됨
```
#### 예제 108 : 파일명으로 접근 권한 변경하기
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    
    chmod("linuxt.txt", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
    stat("linux.txt", &statbuf);

    printf("mode = %o\n", (unsigned int)statbuf.st_mode);

    statbuf.st_mode |= S_IWGRP;
    statbuf.st_mode &= ~(S_IROTH);
    chmod("linux.txt", statbuf.st_mode);
    stat("linux.txt", &statbuf);

    printf("mode = %o\n", (unsigned int)statbuf.st_mode);
}
```
```
$ ls -l linux.txt
-rw-rw-r-- 1 ********* ********* 0  *월  * **:** linux.txt
$ main.out
mode = 100664
mode = 100660
$ ls -l linux.txt
-rw-rw---- 1 ********* ********* 0  *월  * **:** linux.txt
```
#### 파일 기술자로 접근 권한 변경 : fchmod(2)
```C
#include<sys/stat.h>

int fchmod(int fd, mode_t mode);
```
* 인자 설명
    * fd : 열려 있는 파일의 파일 기술자
    * mode : 접근 권한
* 접근 권한 지정 방법은 chmod(2)와 같음
* 일반적으로 chmod(2) 함수를 많이 사용함
## 3.4 링크 파일 생성
### 개요
* 링크 : 파일이나 디렉터리에 접근할 수 있는 새로운 이름
    * 하드 링크
    * 심벌릭 링크
    * 모두 ln(1) 명령으로 생성
* 사용자 편의성
    * 이전 시스템과의 호환성 유지
    * 복잡한 경로의 파일에 대해 간단한 경로를 제공
* 예시 : /lib은 실제 디렉터리가 아닌 /usr/lib에 대한 심벌릭 링크임
    * lib 디렉터리는 예전 시스템과의 호환을 위해 필요함
### 3.4.1 하드 링크
#### 개요
* 하드 링크 : 기존 파일에 접근할 수 있는 새로운 '파일명'을 생성
* 기존 파일과 **동일한 inode를 사용**
* 하드 링크 생성시 inode에 저장된 링크 개수(link count)가 증가함
#### 하드 링크 생성 : link(2)
```C
#include<unistd.h>

int link(const char* oldpath, const char* newpath);)
```
* 인자 설명
    * oldpath : 기존 파일의 경로
    * newpath : 새로 생성할 링크의 경로
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 하드 링크는 **같은 파일 시스템**에 있어야 함
#### 예제 111 : 하드 링크 생성하기(link(2))
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;

    stat("linux.txt", &statbuf);
    printf("link count : %d\n", (int)statbuf.st_nlink); //링크 전 링크 개수

    link("linux.txt", "linux.ln");
    stat("linux.txt", &statbuf);
    printf("link count : %d\n", (int)statbuf.st_nlink); //링크 후 링크 개수
}
```
```
$ ls -l linux.*
-rw-rw-r-- 1 ********* ********* 0  *월 ** **:** linux.txt
$ main.out
link count : 1
link count : 2
$ ls -l linux.*
-rw-rw-r-- 2 ********* ********* 0  *월 ** **:** linux.ln
-rw-rw-r-- 2 ********* ********* 0  *월 ** **:** linux.txt
```
### 3.4.2 심벌릭 링크
#### 개요
* 심벌릭 링크 : 기존 파일에 접근할 수 있는 새로운 '다른 파일'을 생성
* 기존 파일과 **다른 inode를 사용**하며, 기존 파일의 경로를 저장함
* lstat(2) : ('다른 파일'을 생성하므로)stat(2)가 아닌 lstat(2)를 이용해 심벌릭 링크의 정보를 검색함
* readlink(2): 심벌릭 링크 자체가 담고 있는 내용 검색
#### 심벌릭 링크 생성 : symlink(2)
```C
#include<unistd.h>

int symlink(const char* target, const char* linkpath);
```
* 인자 설명
    * target : 기존 파일의 경로
    * linkpath : 새로 생성할 심벌릭 링크의 경로
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 심벌릭 링크는 기존 파일과 **다른 파일 시스템**에 생성할 수 있음
#### 예제 113 : 심벌릭 링크 생성하기(symlink(2))
```C
#include<unistd.h>

int main(void){
    symlink("linux.txt", "linux.sym");
}
```
```
$ ls -l linux.*
-rw-rw-r-- 1 shagyeong shagyeong 0  4월 10 09:20 linux.txt
$ main.out
$ ls -l linux.*
lrwxrwxrwx 1 shagyeong shagyeong 9  4월 10 09:20 linux.sym -> linux.txt
-rw-rw-r-- 1 shagyeong shagyeong 0  4월 10 09:20 linux.txt
```
#### 심벌릭 링크의 정보 검색 : lstat(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int lstat(const char* pathname, struct stat* statbuf);
```
* 인자 설명
    * pathname : 심벌릭 링크의 경로
    * statbuf : 새로 생성할 링크의 경로
* 심벌릭 링크(원본과 별개의 파일)의 파일 정보를 검색(stat(2) 함수 사용시 원본 파일에 대한 검색)
#### 예제 114 : 심벌릭 링크의 정보 검색하기(lstat(2))
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    struct stat statbuf;
    symlink("linux.txt", "linux.sym");

    stat("linux.txt", &statbuf);
    printf("stat : linux.txt\n");
    printf("link count : %d\n", (int)statbuf.st_nlink);
    printf("inode : %d\n", (int)statbuf.st_ino);
    
    stat("linux.sym", &statbuf);
    printf("stat : linux.sym\n");
    printf("link count : %d\n", (int)statbuf.st_nlink);
    printf("inode : %d\n", (int)statbuf.st_ino);

    lstat("linux.sym", &statbuf);
    printf("lstat : linux.sym\n");
    printf("link count : %d\n", (int)statbuf.st_nlink);
    printf("inode : %d\n", (int)statbuf.st_ino);
}
```
```
$ main.out
stat : linux.txt
link count : 1
inode : 397696
stat : linux.sym
link count : 1
inode : 397696
lstat : linux.sym
link count : 1
inode : 397622
```
#### 심벌릭 링크의 내용 읽기 : readlink(2)
```C
#include<unistd.h>

ssize_t readlink(const char* pahtname, char* buf, size_t bufsiz);
```
* 인자 설명
    * pathname : 심벌릭 링크의 경로
    * buf : 읽어온 내용을 저장할 버퍼
    * bufsiz : 버퍼의 크기
* 심벌릭 링크 자체의 내용을 읽음
* 성공시 : 읽어온 데이터의 크기(바이트 수) 리턴
* 실패시 : -1 리턴
#### 예제 116 : 심벌릭 링크의 내용 읽기(readlink(2))
```C
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    symlink("linux.txt", "linux.sym");

    char buf[BUFSIZ];
    int n = readlink("linux.sym", buf, BUFSIZ);
    if(n == -1){
        perror("readlink");
        exit(1);
    }

    buf[n] = '\0';
    printf("%s\n", buf);

    exit(0);
}
```
```
$ main.out
linux.txt
#ls -l 명령으로 확인했을 때 '->' 다음에 오는 원본 파일의 경로가 심벌릭 링크의 데이터 블록에 저장되어 있는 내용임
$ ls -l linux.sym
lrwxrwxrwx 1 shagyeong shagyeong 9  4월 10 09:54 linux.sym -> linux.txt
#심벌릭 링크의 크기는 'linux.txt'의 바이트 수인 9
```
#### 심벌릭 링크 원본 파일의 경로 읽기 : realpath(3)
```C
#include<limits.h>
#include<stdlib.h>

char* realpath(const char* path, char* resolved_path);
```
* 인자 설명
    * path : 심벌릭 링크의 경로명
    * resolved_path : 경로명을 저장할 버퍼 주소
* path에 해당하는 심벌릭 링크에 대한 원본 파일의 실제 경로명을 resolved_path에 저장
#### 예제 117 : 원본 파일의 경로 읽기(realpath(3))
```C
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    symlink("linux.txt", "linux.sym");
    char buf[BUFSIZ];
    
    realpath("linux.sym", buf);
    printf("linux.sym realpath : %s\n", buf);
}
```
```
$ main.out
linux.sym realpath : /home/*********/***/*****/***/linux.txt
```
### 3.4.3 링크 끊기
#### 개요
* 링크 끊기 : 파일 시스템에서 링크를 삭제
* unlink(2) 함수를 사용
#### 링크 끊기 : unlink(2)
```C
#include<unistd.h>
int unlink(const char* pathname);
```
* 인자 설명
    * pathname : 삭제할 링크의 경로
* 연결을 끊은 경로명이 그 파일을 참조하는 마지막 링크일 경우 파일은 삭제됨
* 심벌릭 링크를 잉ㄴ자로 지정한 경우 원본 파일이 아닌 심벌릭 링크 파일이 삭제됨
#### 예제 118 : 링크 끊기(unlink(2))
```C
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    link("linux.txt", "linux.ln");
    symlink("linux.txt", "linux.sym");
    struct stat statbuf;

    stat("linux.ln", &statbuf);
    printf("link count : %d\n", (int)statbuf.st_nlink);

    unlink("linux.ln");
    stat("linux.txt", &statbuf);
    printf("link count : %d\n", (int)statbuf.st_nlink);

    unlink("linux.sym");
}
```
```
$ main.out
link count : 2
link count : 1
```