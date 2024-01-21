# 3장 파일 다루기
## 3.1 개요
### 2장 복습
* 파일의 분류 : 일반 파일, 특수 파일, 디렉터리
* 파일 정보는 inode에 저장함
* inode로부터 검색할 수 있는 정보
  파일의 종류
  접근 권한
  하드링크 개수
  소유자의 UID, GID
  파일의 크기
  파일 접근 시각
  파일의 inode 변경 시각
  ...
* inode 정보를 검색하면 sys/stat.h에 정의되어 있는 stat구조체에 저장된다.
### inode 정보 검색 함수
* stat()
* fstat()
### inode 파일 접근 권한 함수
* 접근 권한 확인 : stat 구조체를 직접 이용하거나 함수를 사용
                  access()
* 접근 권한 변경 : 'chmod'와 같이 접근 권한을 변경할 수 있다.
                  fchmod()
### 링크
* 링크 : 기존 파일이나 디렉터리에 접근할 수 있는 새로운 이름
* 플랫폼에 따라 달라지는 특수 파일에 같은 링크 파일명을 제공해 동일한 방식으로 접근할 수 있음
### 링크의 구분
* 하드 링크 : 기존 파일과 동일한 inode 사용
* 심벌릭 링크 : 기존 파일에 접근할 수 있는 다른 파일을 만듬
               다른 inode를 사용하며 기존 파일의 경로를 저장
### 심벌릭 링크 함수
* 하드 링크 생성 : link()
* 심벌릭 링크 생성 : symlink()
* 심벌릭 링크 정보 검색 lstat();
* 심벌릭 링크 내용 읽기 readlink()
* 심벌릭 링크 원본 파일의 경로 검색 realpath()
* 링크 끊기 unlink()


## 3.2 파일 정보 검색
### 개요
* ls : 파일 정보 검색
* inode : 파일 정보가 저장되어 있음
* inode 정보 검색시 : stat(), lstat(), fstat() 사용
* lstat : 심벌릭 링크 파일의 inode를 검색(4장에서 다룸)
### 파일명으로 파일 검색(stat(2))
* #include<sys/types.h>
  #include<sys/stat.h>
  #include<unistd.h>
  int stat(const char* pathname, struct stat* statbuf);
* 인자 설명
  pathname : 정보를 알고자 하는 파일명
  statbuf : 검색한 파일 정보를 저장할 구조체 구조
* phatname에 지정한 파일의 정보를 검색
* 읽기/쓰기 권한이 반드시 있을 필요는 없음
* 파일에 이르는 경로 상 디렉터리에 대한 읽기 권한은 있어야 함
* 성공시 : 0 리턴, stat 구조체에 파일 정보 저장
* 오류 발생시 : -1 리턴
### stat 구조체
* stat()으로 검색한 inode 정보는 stat 구조체에 저장되어 리턴
* stat 구조체의 정의, stat.h 위치는 배포판과 유닉스 종류에 따라 상이
  본 교재에서는 함수에 정의에 따라 sys/stat.h로 사용
* 세부 구조 확인 : man -s 2 stat
  dev_t      st_dev;       /\* 파일이 저장되어 있는 장치의 번호 \*/
  ino_t      st_ino;       /\* 파일의 inode 번호 \*/
  mode_t     st_mode;      /\* 파일의 종류와 접근 권한 \*/
  nlink_t    st_nlink;     /\* 하드 링크의 개수 \*/
  uid_t      st_uid;       /\* 파일 소유자의 UID \*/
  gid_t      st_gid;       /\* 파일 소유 그룹의 GID \*/
  dev_t      st_rdev;      /\* 장치 파일일 때만 주, 부 장치 번호 \*/
  off_t      st_size;      /\* ??? \*/
  blksize_t  st_blksize;   /\* 파일 입출력시 사용하는 버퍼의 크기 \*/
  blkcnt_t   st_blocks;    /\* 파일에 할당된 파일 시스템의 블록 수 \*/
  struct timespec st_atim; /\* 마지막으로 파일을 읽거나 실행한 시각을 timespec 구조체로 저장 \*/
  struct timespec st_mtim; /\* 마지막으로 파일의 내용을 변경(쓰기)한 시간을 timespec 구조체로 저장 \*/
  struct timespec st_ctim; /\* 마지막으로 inode의 내용을 변경한 시간을 timespec 구조체로 저장 \*/
  #define st_atime st_atim.tv_sec
  #define st_mtime st_mtim.tv_sec
  #define st_ctime st_ctim.tv_sec
* 리눅스 커널 2.6 이전 버전과의 호환성을 위해 #define으로 타임스탬프 값을 초 단위 값으로 매핑해 정의함
* timespec : 나노초를 저장하기 위한 구조체
  struct timespec{
    __kernel_time_t     tv_sec; /\* 초 \*/
    liong               tv_nsec; /\* 나노초 \*/
  }
### 파일 기술자로 파일 정보 검색 (fstat(2))
* #include<sys/types.h>
  #include<sys/stat.h>
  #include<unistd.h>
  int fstat(int fd, struct stat* statbuf);
* 인자 설명
  fd : 열려 있는 파일의 파일 기술자
  statbuf : 검색한 파일 정보를 저장할 구조체 주소
* 파일 경로 대신 현재 열려 있는 파일의 파일 기술자를 인자로 받아 파일정보를 검색
* statbuf로 지정한 구조체에 저장

## 3.3 파일 접근 권한 제어
### 개요
* st_mode : stat 구조체의 항목
            파일 종류와 접근 권한 정보가 저장됨
 