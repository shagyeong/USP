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
* 000 : ...
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
### 파일명으로 파일 정보 검색 : stat(2)
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