# 4장 파일 입출력
### 학습 목표
* 파일 입출력의 특징을 이해한다.
* 저수준 파일 입출력 함수를 사용할 수 있다.
* 고수준 파일 입출력함수를 사용할 수 있다.
* 임시 파일을 생성해 파일 입출력을 할 수 있다.
### 중요 개념
* 4.1 개요 : 
* 4.2 저수준 파일 입출력 : 
* 4.3 고수준 파일 입출력 : 
* 4.4 파일 기술자와 파일 포인터 변환 : 
* 4.5 임시 파일 사용 : 

## 예제 명세
### 4.2 저수준 파일 입출력
* 132 : 새 파일 생성하기(open(2), close(2))
* 133 : O_EXCL 플래그 사용하기
* 135 : 파일 기술자 할당하기
* 136 : 파일 읽기(read(2))
* 138 : 파일 쓰기(write(2))
### 4.3 고수준 파일 입출력
* 000 : ...
* 000 : ...
### 4.4 파일 기술자와 파일 포인터 변환
* 000 : ...
* 000 : ...
### 4.5 임시 파일 사용
* 000 : ...
* 000 : ...

## 4.1 개요
### 파일
* 파일 : 관련 있는 데이터의 집합
* 저장 장치에 일정한 형태로 저장됨
* 데이터 저장, 데이터 전송, 장치 접근에 이용됨
### 리눅스 파일의 분류
* 일반 파일(regular file) : 텍스트나 바이너리 형태의 자료를 저장
* 특수 파일(special file) : 데이터 전송 또는 장치 접근에 사용하는 파일
    * 특수 파일 입출력 : 다른 장에서 다룸
### 리눅스 파일 입출력 구분
* 저수준 파일 입출력
    * 리눅스 커널의 시스템 호출 이용
    * 열린 파일 참조시 : '파일 기술자' 이용
    * 접근 속도 빠름
    * 바이트 단위 입출력 수행(특수 파일 입출력 가능)
    * 응용 프로그램 작성시 바이트를 적당한 형태의 데이터로 변환하는 기능 구현이 필요함
* 고수준 파일 입출력
    * C 표준 함수 이용
    * 열린 파일 참조시 : '파일 포인터(열린 파일의 특성에 관한 정보를 저장하는 구조체를 가리킴)' 이용
    * 버퍼 이용(바이트 단위로 한정하지 않음)
    * 입출력 데이터 변환 기능이 구현되어 있음
### 파일 기술자와 파일 포인터 변환
* 파일 기술자/파일 포인터는 상호 변환 가능
    * 기술자 → 포인터 : fdopen(3)
    * 포인터 → 기술자 : fileno(3)
### 임시 파일 사용
* 임시 파일명 함수 : tmpnam(3), mktemp(3)

## 4.2 저수준 파일 입출력
### 개요
* 저수준 파일 입출력 : 바이트 단위로 입출력 수행
* 특수파일 접근 가능
### 4.2.1 파일 기술자
#### 파일 기술자
* **파일 기술자 : 현재 열려있는 파일을 구분할 목적으로 시스템에서 붙여놓은 번호**
* 저수준 파일 입출력에서 열린 파일을 참조하는데 사용하는 지시자 역할을 함
* open(2)로 파일을 열 떄 '정수값'으로 부여됨
#### 파일 기술자 부여 방식
* 0번부터 시작
* 지정된 기본 용도
    * 0 : 표준 입력(standard input) - 키보드
    * 1 : 표준 출력(standard output) - 모니터
    * 2 : 표준 오류 출력 - 모니터
    * 기본 번호를 다른 파일에 지정할 수도 있음
* 프로세스가 파일을 열 때 0번부터 가장 작은 번호가 순서대로 할당됨
### 4.2.2 파일 생성과 열고 닫기
#### 개요
* 파일 열기 : 파일을 읽거나 쓸 수 있는 상태로 변경하는 것을 의미
* 파일 닫기 : 작업이 완료되면 파일을 닫아야 함
    * 하드디스크에 내용을 온전히 기록
    * 버퍼등을 반납
#### 파일 열기 : open(2)
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
```
* 인자 설명
    * pathname : 열려느 파일이 있는 경로
    * flags : 파일 상태 플래그
    * mode : 접근 권한
* 성공시 : 파일 기술자 리턴
* 실패시 : -1 리턴, errno에 오류 코드 저장
#### 주요 파일 상태 플래그
* O_RDONLY : 읽기 전용으로 열기
* O_WRONLY : 쓰기 전용으로 열기
* O_RDWR : 읽기/쓰기용으로 열기
* O_CREAT : 파일이 없으면 생성(이미 있을 경우 아무 의미 없음)
* O_EXCL : O_CREAT와 함께 사용하여 파일이 존재할 경우 생성하지 않고 오류메시지 출력
* O_APPEND : 파일의 맨 끝에 내용을 추가
* O_TRUNC : 이미 있는 파일이고 쓰기 옵션으로 열었을 경우 내용을 모두 지우고 파일 길이를 0으로 변경
* O_SYNC/O_DSYNC
    * 파일 쓰기 동작 : 일반적으로 버퍼에만 쓰고 나중에 디스크 등의 저장 장치로 옮겨씀
    * 이 옵션을 설정할 경우 저장 장치에 쓰기를 마쳐야 쓰기 동작이 완료됨
    * O_sync는 파일의 수정 시각 속성도 수정할 때까지 기다림
    * 프로그램 실행 속도는 느려질 수 있지만 디스크에 확실히 저장됨을 보장
#### 플래그 연산 예시
```C
O_WRONLY | O_TRUNC #쓰기 전용으로 열기(파일이 있는 경우)
O_WRONLY | O_CREAT | O_TRUNC #쓰기 전용으로 열기(파일이 없는 경우)
O_RDWR | O_APPEND #읽기/쓰기/추가용으로 열기
```
#### mode
* mode : 파일의 접근 권한을 설정
* O_CREAT 플래그를 지정해 '파일을 생성할 때만' 사용
* 일반적인 파일 권한과 같이 8진수로 설정할 수 있음(예시 : 0644)
* 또는 3.3.3의 파일 접근 권한 상수를 사용할수도 있음
```C
mode = S_IUSR | S_IWUSR | S_IRGRP | S_IROTH;
```
#### 파일 생성 : creat(2)
```C
#include<sys/types.h>
#include<sys/sta.h>
#include<fcntl.h>

int creat(const char* pathname, mode_t mode);

// 다음 두 문장은 같은 의미
creat(pahname, mode);
open(pathname, O_CREAT | O_WRONLY | O_TRUNC, mode);
```
* 인자 설명
    * pathname : 파일을 생성할 경로
    * mode : 접근 권한
* open(2)에 파일 생성 기능이 없던 구버전 유닉스에서 사용
* 플래그를 지정하는 부분이 없음
* 성공시 : 파일 기술자 리턴(open(2)을 호출해 열 필요가 없음)
#### 파일 닫기 : close(2)
```C
#include<unistd.h>

int close(int fd);
```
* 인자 설명
    * fd : 파일 기술자
* 파일 입출력 작업 완료 후 반드시 파일을 닫아야 함
    * 프로세스 한 개가 열 수 있는 파일 개수에 제한이 있음
    * ulimit -n 명령으로 확인
* 성공시 : 0 리턴
* 실패시 : -1리턴, errno에 오류코드 저장
#### 예제 132 : 새 파일 생성하기(open(2), close(2))
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd;
    mode_t mode;

    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open("test.txt", O_CREAT, mode);

    if(fd == -1){
        perror("creat");
        exit(1);
    }

    close(fd);
    exit(0);
}
```
```
$ ./main.out
$ ls -l test.txt
-rw-r--r-- 1 ********* ********* 0  *월 ** **:** test.txt
```
#### 예제 133 : O_EXCL 플래그 사용하기
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd;
    fd = open("test.txt", O_CREAT | O_EXCL, 0644);
    if(fd == -1){
        perror("excl");
        exit(1);
    }

    close(fd);
    exit(0);
}
```
```
$ main.out
excl: File exists
```
#### 예제 135 : 파일 기술자 할당하기
* 0번 파일 기술자(표준 입력)을 닫음
* 파일을 열고 0번 파일 기술자가 할당됨을 확인
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd;
    close(0);
    fd = open("test.txt", O_RDWR);

    if(fd == -1){
        perror("open");
        exit(1);
    }

    printf("fd : %d\n", fd);
    close(fd);
    exit(0);
}
```
```
$ ./main.out
fd : 0
```
### 4.2.3 파일 읽기와 쓰기
#### 개요
* read(2) : 파일 읽기
* write(2) : 파일 쓰기
* ssize_t : read(2), write(2)의 리턴형 - sys/types.h에 int(환경에 따라 long)으로 정의되어 있음
#### 파일 읽기 : read(2)
```C
#include<unistd.h>

ssize_t read(int fd, void* buf, size_t count);
```
* 인자 설명
    * fd : 파일 기술자
    * buf : 파일에 기록할 데이터를 저장한 메모리 영역
    * count : buf의 크기(기록할 데이터의 크기)
* count에 지정한 크기만큼 바이트를 읽어 buf로 지정한 메모리 영역에 저장
* 성공시 : 읽은 바이트 수 리턴 또는 0을 리턴(파일의 끝에 도달한 경우)
* 실패시 : -1 리턴
* 파일을 열었을 때 오프셋이 파일의 시작을 가리킴
    * read(2)를 실행할 때마다 읽은 크기만큼 오프셋이 이동해 다음 읽을 위치를 가리킴
* 파일 데이터 종류에 관계없이 무조건 바이트 단위로 읽음
    * 처리 작업은 프로그래머의 몫임
#### 예제 136 : 파일 읽기(read(2))
```C
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd, n;
    char buf[10];

    fd = open("test.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    n = read(fd, buf, 4);
    if(n == -1){
        perror("read");
        exit(1);
    }

    buf[n] = '\0';
    printf("n = %d, buf = %s\n", n, buf);
    close(fd);

    exit(0);
}
```
```
#test.txt
linux system programming!!!!
```
```
$ ./main.out
n = 4, buf = linu
```
#### 파일 쓰기 : write(2)
```C
#include<unistd.h>

ssize_t write(int fd, const void* buf, size_t count);
```
* 인자 설명
    * fd : 파일 기술자
    * buf : 파일에 기록할 데이터를 저장한 메모리 영역
    * count : buf의 크기(기록할 데이터의 크기)
* buf가 가리키느 메모리 영역에서 count로 지정한 크기만큼 읽어 쓰기 수행
* 성공시 : 쓰기를 수행한 바이트 수 리턴
* 실패시 : -1 리턴
#### 예제 138 : 파일 쓰기(write(2))
```C
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    //파일을 읽어 다른 파일에 쓰기
    int rfd, wfd, n;
    char buf[10];

    rfd = open("test.txt", O_RDONLY);
    if(rfd == -1){
        perror("test.txt");
        exit(1);
    }

    wfd = open("test.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(wfd == -1){
        perror("test.bak");
        exit(1);
    }

    while((n = read(rfd, buf, 5)) != 0){
        if(write(wfd, buf, n) != n){
            perror("write");
        }
    }

    if(n == -1){
        perror("read");
    }

    close(rfd);
    close(wfd);

    exit(0);
}
```
```
$ ./main.out
$ cat test.bak
linux system programming!!!!
```
### 4.2.4 파일 오프셋 지정
#### 개요


* 140 : 파일 오프셋 위치 지정(lseek(2))
* 143 : 파일 기술자 복사(dup(2))
* 144 : 파일 기술자 복사(dup2(3))
* 146 : 파일 기술자 제어(fcntl(2))
* 148 : 파일 삭제(remove(3))
* 149 : 파일과 디스크 동기화(fsync(3))
### 4.3 고수준 파일 입출력
* 151 : 파일 열기(fopen(3))
* 152 : 파일 닫기(fclose(3))
* 153 : 문자 기반 입력 함수(fgetc(3), getc(), getchar(), getw(3))
* 154 : fputc 3 putc putchar(putw(3))
* 156 : 문자열 기반 입력 함수(gets(3), fgets(3))
* 157 : 문자열 기반 출력 함수(puts(3), fputs(3))
* 158 : 버퍼 기반 입력 함수(fread(3))
* 160 : 버퍼 기반 출력 함수(fwrite(3))
* 162 : 형식 기반 입력 함수(scanf(3), fscanf(3))
* 164 : 형식 기반 출력 함수(printf(3), fprint(3))
* 166 : 파일 오프셋 이동(fseek(3))
* 167 : 현재 오프셋 구하기(ftell(3))
* 167 : 처음 위치로 오프셋 이동(rewind(3))
* 169 : 파일과 디스크 동기화 함수(fflush(3))
### 4.4 파일 기술자와 파일 포인터 변환
* 171 : 파일 포인터 생성(fdopen(3))
* 173 : 파일 기술자 생성(fileno(3))
### 4.5 임시 파일 사용
* 175 : 임시 파일명 생성(tmpnam(3))
* 175 : 템플릿을 지정한 임시 파일명 생성(mktemp(3))
* 177 : 임시 파일의 파일 포인터와 파일 기술자 생성(mkstemp(3))