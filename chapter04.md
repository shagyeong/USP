# 4장 파일 입출력
## 4.1 개요

## 4.2 저수준 파일 입출력
### 4.2.1 fd
#### fd
- 파일 기술자: 열린 파일 구분을 위한 저수준 파일 입출력 지시자
- 0: 표준 입력
- 1: 표준 출력
- 2: 표준 오류 출력
- 가장 작은 번호가 자동 할당됨
### 4.2.2 파일 생성/열기/닫기
#### 파일 열기: open(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
```
#### 주요 플래그
- man(1)로 확인 가능
- O_RDONLY: 읽기 전용
- O_WRONLY: 쓰기 전용
- O_RDWR: 읽기/쓰기용
- O_CREAT: 파일이 없는 경우 생성
- O_EXCL: O_CREAT와 같이 사용 - 이미 존재하는 경우 오류 메시지 출력
- O_APPEND: 파일 맨 끝에 내용추가
- O_TRUNC: 이미 존재하는 파일이고 쓰기 옵션으로 연 경우 내용을 모두 지우고 파일 길이를 0으로 변경
- O_SYNC/O_DSYNC: 디스크에 대한 쓰기까지 완료되어야 쓰기 동작 완료로 간주하는 옵션
#### 파일 접근 권한
- 파일 접근 권한 상수(3.3.3 참고) 또는 0644 형식
    ```
    mode_t mode = 0644;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    ```
- U/USR(user): 소유자
- G/GRP(group): 그룹
- O/OTH(other): 기타 사용자
- R(read): 읽기
- W(write): 쓰기
- X(execution): 실행
#### 파일 생성: creat(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int creat(const char* pathname, mode_t mode);
```
- open(2)에 파일 생성 기능이 없던 구 버전 유닉스에서 사용
#### 파일 닫기: close(2)
```C
#include<unistd.h>
int close(int fd);
```
#### 예제: 파일 생성(open(2), close(2))
- test.c
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        int fd;
        int flags = O_CREAT | O_EXCL;
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        if((fd = open("./test.txt", flags, mode)) == -1){
            perror("open");
            exit(1);
        }
        close(fd);
    }
    ```
- demo
    ```
    $ ./test
    $ ls
    (...) test.txt
    $ ./test
    open: File exists
    ```
#### 예제: fd 확인(open(2), close(2))
- 0번 fd(표준 입력)을 close 후 파일 open시 할당되는 fd 확인
- test.c
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        close(0);
        int fd;
        int flags = O_CREAT | O_EXCL;
        mode_t mode = S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH;
        fd = open("./test.txt", flags, mode);
        printf("test.txt fd: %d\n", fd);
        close(fd);
    }
    ```
- demo
    ```$ ./test
    test.txt fd: 0
    ```
    - 가장 작은 0이 fd로 할당되었음을 확인
### 4.2.3 파일 읽기와 쓰기
#### 파일 읽기: read(2)
```C
#include<unistd.h>
ssize_t read(int fd, void* buf, size_t count);
```
- 지정한 크기만큼 파일을 읽어 buf로 지정한 *메모리 영역*에 저장
- 자동으로 '\0'을 추가하지 않음
- 성공시: 읽은 바이트 수 리턴(0인 경우 EOF 도달을 의미)
- 실패시: -1 리턴
#### 예제: 파일 읽기(read(2))
- test.c
    ```C
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        char buf[10]; int n;
        int fd;
        int flags = O_RDONLY;
        fd = open("./test.txt", flags);
        n = read(fd, buf, 5); buf[n] = '\0';
        printf("n = %d, buf = %s\n", n, buf);
        close(fd);
    }
    ```
- demo
    ```
    $ cat test.txt
    Linux System Programming
    $ ./test
    n = 5, buf = Linux
    ```
#### 파일 쓰기: write(2)
```C
#include<unistd.h>
ssize_t write(int fd, const void* buf, size_t count);
```
- buf로 지정한 *메모리 영역*에서 데이터를 읽어 쓰기 수행
- 성공시: 쓰기를 수행한 바이트 수 리턴
- 실패시: -1 리턴
#### 예제: 파일 쓰기(write(2))
- test.c
    ```C
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        char buf[10]; int n;
        int rfd; int rflags = O_RDONLY;
        int wfd; int wflags = O_CREAT | O_WRONLY;
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

        rfd = open("./test.txt", rflags);
        wfd = open("./test.bak", wflags, mode);

        while((n = read(rfd, buf, 5)) > 0){
            write(wfd, buf, n);
        }

        close(rfd);
        close(wfd);
    }
    ```
- demo
    ```
    $ cat test.txt
    Linux System Programming
    $ ./test
    $ cat test.bak
    Linux System Programming
    ```
### 4.2.4 파일 오프셋 지정
#### 오프셋
- 오프셋: 파일의 시작 지점에서 현재 위치까지의 바이트 수
- 한 파일에서 오프셋은 한 개이다(읽기/쓰기 오프셋이 별도로 있지 않음)
#### 파일 오프셋 지정: lseek(2)
```C
#include<sys/types.h>
#include<unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```
- offset: 이동할 바이트 수
- whence: 오프셋 기준 위치
#### 주요 whence 값
- |값|기능|
  |---|---|
  |SEEK_SET|파일 시작 기준|
  |SEEK_CUR|현재 위치 기준|
  |SEEK_END|파일 끝 기준|
- 예제
    ```
    lseek(fd, 5, SEEK_SET); //파일 시작부터 5바이트
    lseek(fd, 0, SEEK_END); //파일 끝(끝에서 0번째)으로 이동
    lseek(fd, 0, SEEK_CUR); //현재 위치 구하기
    ```
#### 예제: 파일 오프셋 지정(lseek(2))
- test.c
    ```C
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        off_t start;
        char buf[10]; int n;
        int rfd; int rflags = O_RDONLY;
        int wfd; int wflags = O_CREAT | O_WRONLY;
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        rfd = open("./test.txt", rflags);
        wfd = open("./test.bak", wflags, mode);
        //파일을 처음부터 끝까지 읽기
        printf("current offset: %d\n", (int)lseek(rfd, 0, SEEK_CUR));
        while((n = read(rfd, buf, 5)) > 0){
            printf("%s", buf);
        }
        printf("current offset: %d\n", (int)lseek(rfd, 0, SEEK_CUR));
        //특정 위치로 이동후 파일 읽기
        start = lseek(rfd, 6, SEEK_SET); //6번째로 이동해 'System'의 'S'부터 읽음
        while((n = read(rfd, buf, 5)) > 0){
            write(wfd, buf, n);
        }
        close(rfd);
        close(wfd);
    }
    ```
- demo
    ```
    $ ./test
    current offset: 0
    Linux System Programming
    current offset: 25
    $ cat test.txt
    Linux System Programming
    $ cat test.bak
    System Programming
    ```
### 4.2.5 fd 복사
#### fd 복사: dup(2)
```C
#include<unistd.h>
int dup(int oldfd);
```
- 인자 fd가 가리키는 파일에 대해 새로운 fd 리턴
- 할당할 수 있는 fd 중 가장 작은 값 리턴
#### 예제: 출력 리디렉션(dup(3))
- 표준 출력 fd(1)를 닫고 파일을 가리키도록 함
- test.c
    ```C
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        int wfd; int wflags = O_WRONLY | O_APPEND; wfd = open("./test.txt", wflags);
        int sfd; close(1); sfd = dup(wfd);
        char buf[256] = "hello from write fd\n"; write(wfd, buf, 256);
        printf("hello from standard output\n");
        close(wfd);
    }
    ```
- demo
    ```
    $ ./test
    $ cat test.txt
    Linux System Programming
    hello from write fd
    hello from standard output
    ```
#### fd 복사: dup2(3)
```C
#include<unistd.h>
int dup2(int oldfd, int newfd);
```
- dup(3): 파일 기술자를 자동으로 할당
- dup2(3): 파일 기술자를 지정(인자 oldfd)
#### 예제: 출력 리디렉션(dup2(3))
- test.c
    ```C
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        int wfd; int wflags = O_WRONLY | O_APPEND;
        wfd = open("./test.txt", wflags);
        dup2(wfd, STDOUT_FILENO);
        printf("hello from standard output\n");
        close(wfd);
    }
    ```
- demo
    ```
    $ ./test
    $ cat test.txt
    Linux System Programming
    hello from standard output
    ```
### 4.2.6 fd 제어
#### fd 제어: fcntl(2)
```C
#include<unistd.h>
#include<fcntl.h>
int fcntl(int fd, int cmd, /* arg */);
```
- cmd: 명령
- arg: cmd에 따라 필요시 지정하는 인자
- 파일이 열려있는 상태에서 플래그를 조정할 수 있다
#### fcntl(2) 인자 cmd
- <fcntl.h>에 정의되어 있다
- F_GETFL: 상태 플래그 정보를 읽어온다
- F_SETFL: 상태 플래그를 설정한다
#### 예제: fd 제어(fcntl(2))
- O_APPEND 플래그를 추가해 쓰기 수행
- test.c
    ```C
    #include<sys/types.h>
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>

    int main(void){
        char buf[256] = "hello world\n";
        int fd; int flags = O_WRONLY;
        fd = open("./test.txt", flags);
        write(fd, buf, 256);

        flags = fcntl(fd, F_GETFL);
        flags |= O_APPEND;
        fcntl(fd, F_SETFL, flags);

        write(fd, buf, 256);
        close(fd);
    }
    ```
- demo
    ```
    $ cat test.txt
    hello world
    hello world
    ```
### 4.2.7 파일 삭제
#### 파일 삭제: remove(3)
```C
#include<stdio.h>
int remove(const char* pathname);
```
- remove(3)이 내부에서 시스템 호출 사용
- 삭제 대상이 파일: unlink(2) 호출
- 삭제 대상이 디렉터리: rmdir(2) 호출
#### 예제: 파일 삭제(remove(3))
- test.c
    ```C
    #include<stdio.h>
    int main(void){
        remove("test.txt");
    }
    ```
- demo
    ```
    $ ls
    (...) test.txt
    $ ls
    (...)
    ```
### 4.2.8 디스크 동기화
#### 디스크 동기화 함수: fsync(3)
```C
#include<unistd.h>
int fsync(int fd);
```
- 메모리에 위치한 파일 내용을 디스크로 보냄
- 디스크에 쓰기 수행이 완료되기 전 리턴하지 않음

## 4.3 고수준 파일 입출력
### 4.3.1 fp
### 4.3.2 파일 열기/닫기
### 4.3.3 문자 기반 입출력
### 4.3.4 문자열 기반 입출력
### 4.3.5 버퍼 기반 입출력
### 4.3.6 형식 기반 입출력
### 4.3.7 파일 오프셋 지정
### 4.3.8 파일과 디스크 동기화

## 4.4 파일 기술자와 파일 포인터 변환

## 4.5 임시 파일 사용
