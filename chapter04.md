# 4장 파일 입출력
## 4.1 개요
### 4.1.1 개요
#### 파일
- 파일: 데이터 집합
- 일반 파일: 텍스트/바이너리 형태 자료 저장
- 특수 파일: 데이터 전송/장치 접근
### 4.1.2 파일 입출력
#### 저수준 파일 입출력
- 저수준 파일 입출력: 시스템 호출로 파일 입출력 수행
- 파일 지시자: 파일 기술자(int)
- 고수준 파일 입출력에 비해 빠름
- 바이트 단위 입출력
- 특수 파일 접근가능
#### 저수준 파일 입출력 함수
```C
//파일 열고 닫기
int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
int creat(const char* pathname, mode_t mode);
int close(int fd);
//입출력
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, const void* buf, size_t count);
//오프셋 조작
off_t lseek(int fd, off_t offset, int whence);
//fd 복사
int dup(int oldfd);
int dup2(int oldfd, int newfd);
//fd 조작
int fcntl(int fd, int cmd, /* arg */);
//파일 삭제
int remove(const char* pathname);
//디스크와 동기화
int fsync(int fd);
```
#### 고수준 파일 입출력
- 고수준 파일 입출력: C 표준 함수로 파일 입출력 수행
- 파일 지시자: 파일 포인터(FILE*)
- 사용하기 쉬움
- 버퍼 단위 입출력
- 데이터 입출력 동기화 쉬움
- 형식 기반 입출력 제공
#### 고수준 파일 입출력 함수
```C
//파일 열고 닫기
FILE* fopen(const char* pathname, const char* mode);
int fclose(FILE* stream);
//character 기반 입출력
int fgetc(FILE* stream);
int getc(FILE* stream);
int getchar(void);
int getw(FILE* stream);
int fputc(int c, FILE* stream);
int putc(int c, FILE* stream);
int putchar(int c);
int putw(int w, FILE* stream);
//string 기반 입출력
char* gets(const char* s);
char* fgets(char* s, int size, FILE* stream);
int puts(const char* s);
int fputs(const char* s, FILE* stream);
//버퍼 기반 입출력
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
//format 기반 입출력
int scanf(const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
//오프셋 조작
int fseek(FILE* stream, long offset, int whence);
long ftell(FILE* stream);
void rewind(FILE* stream);
//디스크 동기화
int fflush(FILE* stream);
```
### 4.1.3 파일 지시자 전환
#### 파일 지시자 전환 함수
```C
//파일 포인터 생성(fd → fp)
FILE* fdopen(nit fd, const char* mode);
//파일 기술자 추출(fp → fd)
int fileno(FILE* stream);
```
### 4.1.4 임시 파일
#### 임시 파일명 함수
```C
char* tmpnam(char* s);
char* mktemp(char* template);
```
#### 임시 파일 지시자 함수
```C
FILE* tmpfile();
int mkstemp(char* template);
```

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
#### fp
- 파일 포인터: 고수준 파일 입출력 지시자 - 디스크에서 메모리로 읽어온 파일에 대한 주소 정보를 담은 포인터
### 4.3.2 파일 열기/닫기
#### 파일 열기: fopen(3)
```C
#include<stdio.h>
FILE* fopen(const char* pathname, const char* mode);
```
#### 열기 모드
|모드|기능|
|---|---|
|r|읽기|
|w|새로 쓰기|
|a|추가 쓰기(append)|
|rb|바이너리 파일 읽기|
|wb|바이너리 파일 새로 쓰기|
|ab|바이너리 파일 추가 쓰기|
|r+|읽기/쓰기|
|w+|쓰기/읽기|
|a+|추가 쓰기/읽기|
|rb+|바이너리 파일 읽기/쓰기|
|wb+|바이너리 파일 쓰기/읽기|
|ab+|바이너리 파일 추가 쓰기/읽기|
#### 파일 닫기: fclose(3)
```C
#include<stdio.h>
int fclose(FILE* stream);
```
- 메모리에 있는 파일 내용을 디스크에 저장 후 종료
- 성공시: 0 리턴
- 오류시: EOF 리턴
### 4.3.3 문자 기반 입출력
#### 문자 기반 입력 함수: fgetc(3), getc(3), getchar(3), getw(3)
```C
#include<stdio.h>
int fgetc(FILE* stream);
int getc(FILE* stream);
int getchar(void);
int getw(FILE* stream);
```
- fgetc(3): fp가 가리키는 파일로부터 문자 한개를 unsigned char 형태로 읽어옴
- getc(3): fgetc(3)와 동일한 기능 - 매크로로 구현
- getchar(3): 표준 입력에서 문자 한개를 읽어옴 - getc(stdin)과 같음
- getw(3): 파일에서 워드 단위로 읽어옴
- 오류시: EOF 리턴
#### 문자 기반 출력 함수: fputc(3), putc(3), putchar(3), putw(3)
```C
#include<stdio.h>
int fputc(int c, FILE* stream);
int putc(int c, FILE* stream);
int putchar(int c);
int putw(int w, FILE* stream);
```
- c, w: 입력할 문자/워드
- 성공시: 해당 문자값 리턴
- 오류시: EOF 리턴
#### 예제: 문자 기반 입출력(fopen(3), fclose(3), fgetc(3), fputc(3))
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        int c;
        FILE* rfp = fopen(argv[1], "r");;
        FILE* wfp = fopen(argv[2], "w");
        while((c = fgetc(rfp)) != EOF){
            fputc(c, wfp);
        }
        fclose(rfp);
        fclose(wfp);
    }
    ```
- demo
    ```
    $ ./test test.txt test.bak
    $ cat test.bak
    Linux System Programming
    ```
### 4.3.4 문자열 기반 입출력
#### 문자열 기반 입력: gets(3), fgets(3)
```C
#include<stdio.h>
char* gets(const char* s);
char* fgets(char* s, int size, FILE* stream);
```
- gets(3): 표준 입력 - 개행 문자 저장하지 않음
- fgets(3): size보다 하나 적게 또는 개행 문자/EOF 전까지 문자열 저장 - 개행 문자 저장함
- 성공시: 문자열 주소 리턴
- 실패시: NULL리턴
#### 문자열 기반 출력: puts(3), fputs(3)
```C
#include<stdio.h>
int puts(const char* s);
int fputs(const char* s, FILE* stream);
```
- puts(3): 표준 출력 - 개행 문자를 추가해 출력
- fputs(3): 개행 문자 추가하지 않음
#### 예제: 문자열 기반 입출력(fgets(3), fputs(3))
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        char buf[BUFSIZ];
        FILE* rfp = fopen(argv[1], "r");
        FILE* wfp = fopen(argv[2], "a");
        while(fgets(buf, BUFSIZ, rfp) != NULL){
            fputs(buf, wfp);
        }
        fclose(rfp); fclose(wfp);
    }
    ```
- demo
    ```
    $ ./test test.txt test.bak
    $ cat test.bak
    Linux System Programming
    Linux System Programming
    ```
### 4.3.5 버퍼 기반 입출력
#### 버퍼 기반 입력: fread(3)
```C
#include<stdio.h>
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
```
- ptr: 버퍼 주소
- size: 버퍼 크기
- nmemb: 읽어올 항목 수 - fread(buf, sizeof(char)*2, 4, rfp)는 한 번에 문자열 8개를 읽음
- stream: 파일 포인터
- 성공시: 읽어온 항목 수 리턴
- 읽을 항목이 없음: 0 리턴
- EOF: EOF 리턴
#### 예제: 버퍼 기반 파일 읽기(fread(3))
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        char buf[BUFSIZ]; int n;
        FILE* rfp = fopen(argv[1], "r");
        while((n = fread(buf, sizeof(char), 4, rfp)) != 0){
            printf("n: %d, buf: %s\n", n, buf);
        }
        fclose(rfp);
    }
    ```
- demo
    ```
    $ ./test test.txt
    n: 4, buf: Linu
    n: 4, buf: x Sy
    n: 4, buf: stem
    n: 4, buf:  Pro
    n: 4, buf: gram
    n: 4, buf: ming
    n: 1, buf: 
    ing
    ```
#### 버퍼 기반 출력: fwrite(3)
```C
#include<stdio.h>
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
```
#### 예제: 버퍼 기반 입출력(fread(3), fwrite(3))
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        char buf[BUFSIZ]; int n;
        FILE* rfp = fopen(argv[1], "r");
        FILE* wfp = fopen(argv[2], "w");
        while((n = fread(buf, sizeof(char), 8, rfp)) > 0){
            fwrite(buf, sizeof(char), 8, wfp);
        }
        fclose(rfp);
        fclose(wfp);
    }
    ```
- demo
    ```
    $ ./test test.txt test.bak
    $ cat test.bak
    Linux System Programming
    ```
### 4.3.6 형식 기반 입출력
#### 형식 기반 입력: scanf(3), fscanf(3)
```C
#include<stdio.h>
int scanf(const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
```
- 성공시: 읽은 항목 개수 리턴
- 형식에 맞지 않는 입력: 0 리턴
- 너무 빨리 EOF에 도달: 0 리턴
- 형식 확인 전 EOF에 도달: EOF 리턴
#### 예제: 성적 파일에서 평균 구하기(fscanf(3))
- grade.dat
    ```
    ID      OS  DS  SP  ST  NW
    21001  98  98  98  99  97
    21002  95  90  94  93  99
    ```
    - 머리글 행은 예제에서 작성하지 않는다
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        int n;
        int id;
        int os, ds, sp, st, nw; int avg;
        FILE* rfp = fopen(argv[1], "r");

        printf("ID\t\tAVG\n");
        while((n = fscanf(rfp, "%d %d %d %d %d %d", &id, &os, &ds, &sp, &st, &nw)) != EOF){
            avg = (os + ds + sp + st + nw) / 5;
            printf("%d\t\t%d\n", id, avg);
        }
        fclose(rfp);
    }
    ```
- demo
    ```
    $ ./test grade.dat
    ID              AVG
    21001           98
    21002           94
    ```
#### 형식 기반 출력: printf(3), fprintf(3)
```C
#include<stdio.h>
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
```
- 성공시: 출력한 문자 수 리턴
- 오류시: EOF 리턴
#### 예제: 성적 파일에서 평균 구하기(fscanf(3), fprintf(3))
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        int n;
        int id;
        int os, ds, sp, st, nw; int avg;
        FILE* rfp = fopen(argv[1], "r");
        FILE* wfp = fopen(argv[2], "w");

        fprintf(wfp, "ID\t\tAVG\n");
        while((n = fscanf(rfp, "%d %d %d %d %d %d", &id, &os, &ds,&sp, &st, &nw)) != EOF){
            avg = (os + ds + sp + st + nw) / 5;
            fprintf(wfp, "%d\t\t%d\n", id, avg);
        }
        fclose(rfp);fclose(wfp);
    }
    ```
- demo
    ```
    $ ./test grade.dat avg.dat
    $ cat avg.dat
    ID              AVG
    21001           98
    21002           94
    ```
### 4.3.7 파일 오프셋 지정
#### 파일 오프셋 이동: fseek(3)
```C
#include<stdio.h>
int fseek(FILE* stream, long offset, int whence);
```
- offset: 이동할 바이트 수
- whence: 오프셋 기준 위치
- 성공시: 0 리턴(오프셋을 리턴하지 않음)
- 실패시: EOF 리턴
#### 주요 whence 값
- lseek(2)와 동일
- |값|기능|
  |---|---|
  |SEEK_SET|파일 시작 기준|
  |SEEK_CUR|현재 위치 기준|
  |SEEK_END|파일 끝 기준|
#### 현재 오프셋 구하기: ftell(3)
```C
#include<stdio.h>
long ftell(FILE* stream);
```
#### 파일 시작으로 이동: rewind(3)
```C
#include<stdio.h>
void rewind(FILE* stream);
```
#### 예제: 파일 오프셋 이동(fseek(3), ftell(3), rewind(3))
- test.c
    ```C
    #include<stdio.h>

    int main(int argc, char* argv[]){
        long offset;
        char buf[BUFSIZ]; int n;
        FILE* rfp = fopen(argv[1], "r");

        offset = ftell(rfp); printf("current offset: %d\n", (int)offset);
        fread(buf, sizeof(char), 5, rfp);
        printf("buf: %s\n", buf);

        fseek(rfp, 1, SEEK_CUR);  //공백 건너뛰도록 오프셋 이동
        offset = ftell(rfp); printf("current offset: %d\n", (int)offset);
        fread(buf, sizeof(char), 6, rfp);
        printf("buf: %s\n", buf);

        fseek(rfp, 1, SEEK_CUR);
        offset = ftell(rfp); printf("current offset: %d\n", (int)offset);
        fread(buf, sizeof(char), 11, rfp);
        printf("buf: %s\n", buf);

        //rewind
        rewind(rfp); offset = ftell(rfp);
        printf("rewind offset: %d\n", (int)offset);

        fclose(rfp);
    }
    ```
- demo
    ```
    $ ./test test.txt
    current offset: 0
    buf: Linux
    current offset: 6
    buf: System
    current offset: 13
    buf: Programming
    rewind offset: 0
    ```
### 4.3.8 파일과 디스크 동기화
#### 디스크 동기화: fflush(3)
```C
#include<stdio.h>
int fflush(FILE* stream);
```
- 버퍼에 있는 데이터를 파일에 기록

## 4.4 파일 기술자와 파일 포인터 변환
### 4.4.0 개요
#### 개요
|기능|함수|
|---|---|
|파일 포인터 '생성'(fd → fp)|FILE* fdopen(nit fd, const char* mode);|
|파일 기술자 '추출'(fp → fd)|int fileno(FILE* stream);|
### 4.4.1 파일 포인터 생성
#### 파일 포인터 생성: fdopen(3)
```C
#include<stdio.h>
FILE* fdopen(nit fd, const char* mode);
```
#### 열기 모드
- fopen(3)의 열기 모드와 동일(4.3.2)
- open(2)의 플래그에 대응되는 모드를 지정해야 함
- 성공시: 파일 포인터 리턴
- 실패시: 널 포인터 리턴
#### 예제: 파일 포인터 생성(fdopen(3))
- test.c
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdio.h>

    int main(int argc, char* argv[]){
        int rfd;    int rflags = O_RDONLY;
        FILE* rfp;  char rmode[1] = "r";
        int c;

        rfd = open(argv[1], rflags);
        rfp = fdopen(rfd, rmode);

        while((c = fgetc(rfp)) != EOF){
            fputc(c, stdout);
        }
        close(rfd);
        fclose(rfp);
    }
    ```
- demo
    ```
    $ ./test test.txt
    Linux System Programming
    ```
### 4.4.2 파일 기술자 추출
#### 파일 기술자 추출: fileno(3)
```C
#include<stdio.h>
int fileno(FILE* stream);
```
#### 예제: 파일 기술자 추출(fileno(3))
- test.c
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>
    #include<stdio.h>

    int main(int argc, char* argv[]){
        char buf[10]; int n;
        int rfd;
        FILE* rfp;

        rfp = fopen(argv[1], "r");
        rfd = fileno(rfp);

        while((n = read(rfd, buf, 5)) > 0){
            write(STDOUT_FILENO, buf, 5);
        }
        close(rfd);
        fclose(rfp);
    }
    ```
- demo
    ```
    $ ./test test.txt
    Linux System Programming
    ```

## 4.5 임시 파일 사용
### 4.5.1 임시 파일명 생성
#### 임시 파일명 생성: tmpnam(3)
```C
#include<stdio.h>
char* tmpnam(char* s);
```
- s: 파일명을 저장 버퍼 시작 주소
- 인자를 지정하지 않은 경우: 임시 파일명 리턴
#### 탬플릿 지정 임시 파일명 생성: mktemp(3)
```C
#include<stdlib.h>
char* mktemp(char* template);
```
- 지정 템플릿: 대문자 X 6개로 마쳐야 함
- 시스템에서 다른 문자로 대체해 임시 파일명 생성
#### 예제: 임시 파일명 생성(tmpnam(3), mktemp(3))
- test.c
    ```C
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    int main(void){
        char* fname;
        char fntmp[BUFSIZ];
        char template[32];

        fname = tmpnam(NULL);
        printf("tmp file name: %s\n", fname);
        tmpnam(fname);
        printf("tmp file name: %s\n", fname);
        strcpy(template, "/tmp/testXXXXXX");
        fname = mktemp(template);
        printf("tmp file name: %s\n", fname);
    }
    ```
- demo
    ```
    $ ./test
    tmp file name: /tmp/fileH0DKW1
    tmp file name: /tmp/fileL8RMWd
    tmp file name: /tmp/testcQzy4v
    ```
### 4.5.2 임시 파일에 대한 파일 지시자 생성
#### 개요
- 대부분의 경우 임시 파일명을 알 필요는 없음
- tmpfile(3): 임시 파일명 없이 fp만 사용
- mkstemp(3): 임시 파일명 없이 fd만 사용
#### 임시 파일에 대한 파일 지시자 생성
```C
//fp 생성
#include<stdio.h>
FILE* tmpfile()
//fd 생성
#include<stdlib.h>
int mkstemp(char* template);
```
#### 예제: 임시 파일에 대한 파일 지시자 생성(tmpfile(3), mkstemp(3))
- test.c
    ```C
    #include<stdlib.h>
    #include<stdio.h>
    #include<unistd.h>
    
    int main(void){
        char template[32] = "/tmp/testXXXXXX";
        int tfd = mkstemp(template);
        FILE* tfp = tmpfile();
    
        char buf[10] = "hello"; write(tfd, buf, 10);
        fprintf(tfp, "hello");
    
        close(tfd);
        fclose(tfp);
    }
    ```
- demo
    ```
    $ cat /tmp/test*
    hello
    ```
