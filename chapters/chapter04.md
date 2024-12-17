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
* 141 : 파일 오프셋 활용하기(lseek(2))
* 143 : 파일 기술자 복사하기(입출력 방향 전환하기)(dup(2))
* 145 : 파일 기술자를 복사하기(dup2(3))
* 146 : 파일 기술자 제어하기(fcntl(2))
* 148 : 파일 삭제(remove(3))
### 4.3 고수준 파일 입출력
* 157 : 문자열 기반 입출력 함수 사용하기(fgets(3), fputs(3))
* 159 : 파일 읽기(fread(3))
* 161 : 파일 출력하기(fwrite(3))
* 163 : 파일 내용 읽기(fscanf(3))
* 164 : 지정한 파일로 출력하기(fprintf(3))
### 4.4 파일 기술자와 파일 포인터 변환
* 172 : 파일 포인터 생성하기(fdopen(3))
* 173 : 파일 기술자 추출하기(fileno(3))
### 4.5 임시 파일 사용
* 176 : 임시 파일명 만들기(tmpnam(3), mktemt(3))
* 178 : 임시 파일 생성하기(tmpfile(3), mkstemp(3))

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
#### 오프셋
* **오프셋 : 파일의 시작지점부터 현재 위치까지의 바이트 수**
* 파일을 열었을 때 오프셋 : 0(파일의 시작)
* read(2), write(2) 실행때마다 읽은 크기만큼 오프셋이 이동하여 다음 읽을/쓸 위치를 가리킴
* 파일 1개에서 오프셋은 **오직 1개**임
    * 읽기/쓰기 모드로 열었을 때 읽기 오프셋과 쓰기 오프셋이 별도로 있지 않음
* lseek(2) : 오프셋 위치 지정 함수(위치 확인은 whence값 중 SEEK_CUR을 이용함)
#### 파일 오프셋 위치 지정 : lseek(2)
```C
#include<sys/types.h>
#include<unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```
* 인자 설명
    * fd : 파일 기술자
    * offset : 이동할 오프셋 위치
    * whence : 오프셋의 기준 위치(whence(n) : 출처)
* offset에 지정한 크기만큼 (whence의 값을 기준으로 해석하여)오프셋을 이동시킴
* 성공시 : 새로운 오프셋 리턴
* 실패시 : -1 리턴
* off_t : sys/types.h에 long으로 정의되어 있음
#### 오프셋의 기준 위치를 나타내는 whence 값
* SEEK_SET : 파일의 시작을 기준으로 계산
* SEEK_CUR : 현재 위치를 기준으로 계산
* SEEK_END : 파일의 끝을 기준으로 계산
* 예시
    *
    ```C
    lseek(fd, 5, SEEK_SET); //파일의 시작에서 5번재 위치로 이동
    lseek(fd, 0, SEEK_END); //파일의 끝으로 이동
    cur_offset = lseek(fd, 0, SEEK_CUR); //오프셋 현재 위치 확인
    ```
#### 예제 141 : 파일 오프셋 활용하기(lseek(2))
```C
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd, n;
    off_t init, curr;
    char buf[256];

    fd = open("test.txt", O_RDONLY);

    if(fd == -1){
        perror("open");
        exit(1);
    }

    //처음부터 읽기
    init = lseek(fd, 0, SEEK_CUR);
    n = read(fd, buf, 255);
    buf[n] = '\0';
    printf("offset start : %d, n = %d\n", (int)init, n);
    printf("read str : %s\n", buf);

    //읽은 후 오프셋의 위치
    curr = lseek(fd, 0, SEEK_CUR);
    printf("offset current : %d\n", (int)curr);

    //오프셋 위치 지정하여 파일 읽기
    curr = lseek(fd, 6, SEEK_SET);
    n = read(fd, buf, 255);
    buf[n] = '\0';
    printf("offset start : %d, n = %d\n", (int)init, n);
    printf("read str : %s\n", buf);

    close(fd);
    exit(0);
}
```
```
$ ./main.out
offset start : 0, n = 28
read str : linux system programming!!!!
offset current : 28
offset start : 0, n = 22
read str : system programming!!!!
```
### 4.2.5 파일 기술자 복사
#### 개요
* open(2)로 파일을 열면 파일 기술자가 할당됨
* 파일 기술자를 복사해 같은 파일을 가리키는 파일 기술자를 생성할 수 있음
* dup(2), dup2(3) : 파일 기술자 복사 함수
#### 파일 기술자 복사 : dup(2)
```C
#include<unistd.h>

int dup(int oldfd);
```
* 인자 설명
    * oldfd : 복사할 파일 기술자
* 기존 파일 기술자를 인자로 받아 새로운 파일 기술자를 리턴
* **현재 할당할 수 있는 파일 기술자 중 가작 작은 값으로 자동 할당됨**
* **입출력 방향 전환**에 많이 사용됨
#### 예제 143 : 파일 기술자 복사하기(입출력 방향 전환하기)(dup(2))
```C
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd1, fd2;

    fd1 = open("tmp.aaa", O_CREAT | O_WRONLY | O_TRUNC | 0644);
    if(fd1 == -1){
        perror("create");
        exit(1);
    }

    //가장 작은 값(1번)을 할당하여
    // 출력 방향을 표준 출력에서 파일로 전환
    close(1);
    fd2 = dup(fd1);
    printf("dup fd : %d\n", fd2);
    printf("standard output redirection\n");

    close(fd1);
    exit(1);
}
```
```
#tmp.aaa
dup fd : 1
standard output redirection

```
#### 파일 기술자 복사 : dup2(3)
```C
#include<unistd.h>

int dup2(int oldfd, int nwefd);
```
* 인자 설명
    * oldfd : 복사할 파일 기술자
    * newfd : 복사할 곳
* dup(2)는 파일기술자를 '자동으로 할당'함
* dup2(3)는 '지정'할 수 있게 해줌
#### 예제 145 : 파일 기술자를 복사하기(dup2(3))
```C
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


int main(void){
    int fd;
    fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd == -1){
        perror("create");
        exit(1);
    }

    //1번(표준 출력)으로 tmp.bbb 기술자를 복사하여 추력 방향 전환
    dup2(fd, 1);
    printf("dup2 : standard output redirection\n");

    close(fd);
    exit(1);
}
```
```
# tmp.bbb
dup2 : standard output redirection

```
### 4.2.6 파일 기술자 제어
#### 개요
* 현재 열려 있는 파일에 대한 파일 기술자의 속성을 확인하고 제어할 수 있음
* fcntl(2)을 이용해 설정한 플래그를 조정할 수 있음
#### 파일 기술자 제어 : fcntl(2)
```C
#include<unistd.h>
#include<fcntl.h>

int fcntl(int fd, int cmd, .../* arg */);
```
* 인자 설명
    * fd : 파일 기술자
    * cmd : 명령
    * arg : cmd에 따라 필요시 지정하는 인자들
* fd가 가리키는 파일에 cmd로 지정한 명령을 수행
    * cmd의 종류에 따라 인자를 지정해야 할 수도 있음
* 주요 cmd
    * F_GETFL : 상태 플래그 정보를 읽어옴
    * F_SETFL : 상태 플래그 정보를 설정(대부분 open(2)에서 지정하는 플래그)
#### 예제 146 : 파일 기술자 제어하기(fcntl(2))
```C
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd, flags;
    if((fd = open("test.txt", O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    if((flags = fcntl(fd, F_GETFL)) == -1){
        perror("fcntl");
        exit(1);
    }

    flags |= O_APPEND;

    if(fcntl(fd, F_SETFL, flags) == -1){
        perror("fcntl");
        exit(1);
    }

    if(write(fd, "system programming\n", 19) != 19){
        perror("write");
        exit(1);
    }

    close(fd);
    exit(0);
}
```
```
#test.txt
linux system programming!!!!system programming

```
### 4.2.7 파일 삭제
#### 개요
* 파일을 삭제하려면(파일 시스템에서 하드 링크를 끊으려면) unlink(2)를 사용
* remove(3) : path에 지정한 파일/디렉터리를 삭제
    * 파일 : unlink(2) 호출
    * 디렉터리 : rmdir(2) 호출(비어 있을 경우에만 삭제됨)
#### 파일 삭제 : remove(3)
```C
#include<stdio.h>

int remove(const char* pathname);
```
#### 예제 148 : 파일 삭제(remove(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int ret;
    if((ret = remove("test.bak")) == -1){
        perror("remove");
        exit(1);
    }

    printf("remove success\n");
    exit(0);
}
```
```
$ ./main.out
remove success
$ ls test.bak
ls: 'test.bak'에 접근할 수 없음: 그런 파일이나 디렉터리가 없습니다
```
### 4.2.8 파일과 디스크 동기화 함수
#### 파일과 디스크 동기화 함수 : fsync(3)
```C
#include<unistd.h>
int fsync(int fd);
```
* 메모리에 위치하고 있는 파일의 내용을 디스크로 보내 메모리와 디스크의 내용을 동기화함
* 메모리의 내용이 디스크에 모두 기록되기 전에는 리턴하지 않음
## 4.3 고수준 파일 입출력
### 고수준 파일 입출력
* **'표준 입출력 라이브러리(standard IO library)'**라고도 함
* C 표준 함수로 제공
* 저수준 입출력 : 바이트 단위의 입출력(데이터 가공 작업이 필요함)
* 고수준 입출력 : 문자 단위, 행 단위, 버퍼 단위, 형식 기반 입출력 등 기능이 제공됨
### 4.3.1 파일 포인터
#### 파일 포인터
* **파일 포인터 : 디스크에서 메모리로 읽어온 파일의 위치에 대한 정보를 담고 있는 포인터**
* 자료형 : FILE*
#### 파일 구조체
* 그림 4-2 : 파일 기술자 항목을 포함
* **파일 포인터 파일 기술자 상호변환 가능**
* '플랫폼 독립적 구조'로 어느 플랫폼에서든 동일한 동작을 수행함
### 4.3.2 파일 열기와 닫기
#### 파일 열기 : fopen(3)
```C
#include<stdio.h>

FILE* fopen(const char* pathname, const char* mode)
```
* 인자 설명
    * pathname : 파일의 경로
    * mode : 파일 열기 모드
* 성공시 : 열린 파일의 주소를 FILE* 형태로 리턴
* 실패시 : '0'을 리턴
#### fopen(3)의 mode
* read
    * r : 읽기 전용으로 텍스트 파일을 열기
    * r+ : 읽기와 쓰기용으로 텍스트 파일 열기
    * rb : 읽기 전용으로 바이너리 파일을 열기
    * rb+ : 읽기와 쓰기용으로 바이너리 파일 열기
* write
    * w : 새로 쓰기용으로 텍스트 파일을 열기(기존 내용은 삭제됨)
    * w+ : 쓰기와 읽기용으로 텍스트 파일 열기
    * wb : 새로 쓰기 용으로 바이너티 파일을 열기(기존 내용은 삭제됨)
    * wb+ : 쓰기와 읽기용으로 바이너리 파일 열기
* add
    * a : 기존 내용의 끝에 추가해서 쓰기용으로 텍스트 파일을 열기
    * a+ : 추가 쓰기와 읽기용으로 텍스트 파일 열기
    * ab : 기존 내용의 끝에 추가해서 쓰기용으로 바이넡리 파일을 열기
    * ab+ : 추가 쓰기와 읽기용으로 바이너리 파일 열기
#### 파일 닫기 : fclose(3)
```C
#include<stdioi.h>

int fclose(FILE* stream);
```
* 인자 설명
    * stream : fopen(3)에서 리턴한 파일 포인터
* 메모리에 있는 파일 앤용을 디스크에 저장하고 종료
* 성공시 : 0 리턴
* 실패시 : EOF(-1) 리턴
### 4.3.3 문자 기반 입출력
#### 개요
* 가장 간단한 고수준 파일 입출력 : 저수준과 같은 방식으로 바이트 단위로 입출력하기
* 문자 기반 입출력은 데이터를 '바이트 스트림'으로 이해하고 한 바이트씩 처리하는 함수를 제공함
#### 문자 기반 입력 함수 : fgetc(3), getc(), getchar(), getw(3)
```C
#include<stdio.h>

int fgetc(FILE* stream);
int getc(FILE* stream);
int getchar(void);
int getw(FILE* stream);
```
* fgetc(3) : 파일로부터 문자 한 개를 unsigned char 형태로 읽어옴
* getc() : fgetc(3)과 동일, 매크로로 구현되어 있어 더 빠르지만 메모리를 더 차지함
* getchar() : 표준 입력에서 문자 한 개를 읽어오는 매크로 - getc(stdin)과 같음
* getw(3) : 파일에서 워드word 단위로 읽어옴
    * 워드의 크기는 int형의 크기로, 시스템에 따라 달라질 수 있음
* 문자 입출력 함수에서 오류 발생시 : EOF(-1) 리턴
* 리턴형이 char가 아닌 int인 이유
    * -1과 255(10) 구별 불가능
    * 십진수 255를 char로 해석시 EOF와 같은 형태
    * -1(2) : 11111111, 255(10) = 11111111(char)
#### 문자 기반 출력 함수 : fputs(3), putc(), putchar(), putw(3)
```C
#include<stdio.h>

int fputc(int c, FILE* stream);
int putc(int c, FILE* stream);
int putchar(int c);
int putw(int w, FILE* stream);
```
* 인자 설명
    * c, w : 출력할 문자
    * stream : 파일 포인터
* fputc(3) : 인자로 받은 데이터를 unsigned char로 변환해 파일에 씀
* putc() : fputc(3)와 같은 동작 수행, getc와 동일하게 매크로로 구현됨
* putchar() : 표준 출력으로 한 문자를 출력하는 매크로 - putc(c, stdout)과 같음
* putw(3) : 워드 단위로 파일에 출력
* 성공시 : 해당 문자값을 리턴
* 오류시 : EOF(-1) 리턴
#### 예제 154 : 문자 기반 입출력 함수 사용하기(파일 내용 복사하기)(fopen(3), fclose(3), fgetc(3), fputc(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp;FILE* wfp;
    int c;

    if((rfp = fopen("test.txt", "r")) == NULL){
        perror("read");
        exit(1);
    }
    if((wfp = fopen("test.out", "w")) == NULL){
        perror("write");
        exit(1);
    }

    while((c = fgetc(rfp)) != EOF){
        fputc(c, wfp);
    }

    fclose(rfp);
    fclose(wfp);
    exit(0);
}
```
### 4.3.4 문자열 기반 입출력
#### 문자열 기반 입력 함수 : gets(3), fgets(3)
```C
#include<stdio.h>

char* gets(const char* s);
char* fgets(char* s, int size, FILE* stream);
```
* 인자 설명
    * s : 문자열을 저장한 버퍼의 시작 주소
    * size : 버퍼의 크기
    * stream : 파일 포인터
* gets(3) : 표준 입력에서 문자열을 읽어들임
    * 엔터키 입력 또는 EOF까지
    * 읽어들인 문자열의 끝에서 개행 문자를 제외하고 '\0'을 채워 버퍼(s)에 저장하고 리턴
    * s가 확보하고 있는 메모리의 크기를 알 수 없어 s가 가득 찬 후에도 계속 읽을 수 있음
    * 보안 문제가 생길 수 있으므로 가능하면 사용하지 않는 것이 좋음
* fgets(3) : 파일 포인터가 가리키는 파일에서 size에 지정한 길이보다 하나 적게 문자열을 읽어 버퍼(s)에 저장
    * 개행 문자를 만나거나 EOF를 만나면 해당 지점까지만 읽어옴
    * gets(3)와 달리 개행 문자도 s에 저장하고 마지막 문자 다음에 '\0'을 저장함
* 성공시 : 버퍼의 시작 주소를 리턴
* 실패시 : NULL 리턴
#### 문자열 기반 출력 함수 : puts(3), fuputs(3)
```C
#include<stdio.h>

int puts(const char* s);
int fputs(const char* s, FILE* stream);
```
* 인자 설명
    * s : 문자열 주소
    * stream : 파일 포인터
* puts(3) : s가 가리키는 문자열을 개행문자를 추가해 표준 출력으로 출력
* fputs(3) : 개행 문자를 추가하지 않음
* 성공시 : 음수가 아닌 수 리턴
* 파일의 끝 : 오류 리턴
#### 예제 157 : 문자열 기반 입출력 함수 사용하기(fgets(3), fputs(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp;FILE* wfp;
    char buf[BUFSIZ];
    if((rfp = fopen("test.txt", "r")) == NULL){
        perror("read");
        exit(1);
    }
    if((wfp = fopen("test.out", "w")) == NULL){
        perror("write");
        exit(1);
    }

    while(fgets(buf, BUFSIZ, rfp) != NULL){
        fputs(buf, wfp);
    }

    fclose(rfp);
    fclose(wfp);
}
```
### 4.3.5 버퍼 기반 입출력
#### 버퍼 기반 입력 함수 : fread(3)
```C
#include<stdio.h>
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
```
* 인자 설명
    * ptr : 버퍼 주소
    * size : 버퍼 크기
    * nmemb : 읽어올 항목 수
    * stream : 파일 포인터
* 항목의 크기가 size인 데이터를 nmemb에서 지정한 개수만큼 읽어 ptr이 가리키는 버퍼에 저장
* 성공시 : 읽어온 항목 수 리턴
* 읽을 항목이 없을시 : 0 리턴
* 파일의 끝을 만났을시 : EOF 리턴
#### 예제 159 : 파일 읽기(fread(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp;
    char buf[BUFSIZ];
    int n;
    if((rfp = fopen("test.txt", "r")) == NULL){
        perror("read");
        exit(1);
    }

    while((n = fread(buf, sizeof(char) * 2, 4, rfp)) > 0){
        buf[8] = '\0';
        printf("n = %d, buf = %s\n", n, buf);
    }

    fclose(rfp);
    exit(0);
}
```
```
$ ./main.out
n = 4, buf = linux sy
n = 4, buf = stem pro
n = 4, buf = gramming
n = 4, buf = !!!!syst
n = 4, buf = em progr
n = 3, buf = amming
r
```
#### 버퍼 기반 출력 함수 : fwrite(3)
```C
#include<stdio.h>

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
```
* 인자 설명
    * ptr : 버퍼 주소
    * size : 항목의 크기
    * nmemb : 항목 수
    * stream : 파일 포인터
* 항목의 크기가 size인 데이터를 nmemb에서 지정한 개수만큼 ptr에서 읽어 stream으로 지정한 파일에 출력
* 성공시 : 출력한 항목의 수 리턴
* 실패시 : EOF 리턴
#### 예제 161 : 파일 출력하기(fwrite(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp; FILE* wfp;
    char buf[BUFSIZ];
    int n;
    if((rfp = fopen("test.txt", "r")) == NULL){
        perror("read");
        exit(1);
    }
    if((wfp = fopen("test.out", "a")) == NULL){
        perror("write");
        exit(1);
    }

    while((n = fread(buf, sizeof(char) * 2, 4, rfp)) > 0){
        fwrite(buf, sizeof(char) * 2, n, wfp);
    }

    fclose(rfp);
    fclose(wfp);
    exit(0);
}
```
### 4.3.6 형식 기반 입출력
#### 개요
```
ID       LIN ENG CP
2021001 100 85  100
2021002 95  95  100
```
* 위와 같이 형식이 있는 파일 입출력시 유용한 함수가 제공됨
#### 형식 기반 입력 함수 : scanf(3), fscanf(3)
```C
#include<stdio.h>
int scanf(const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
```
* 인자 설명
    * format : 입력 형식(%d, %s 등의 형태)
    * stream : 파일 포인터
* scanf(3) : 표준 입력에서 입력을 받음
* fscanf(3) : 지정한 파일로부터 입력을 받음
* 성공시 : 읽은 항목의 개수 리턴
* 실패시
    * 0 리턴 : 입력값이 형식에 맞지 않거나 너무 빨리 파일의 끝에 도달함
    * EOF 리턴 : 형식에 맞는지 확인하기 전에 파일의 끝을 만남
#### 예제 163 : 파일 내용 읽기(fscanf(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp; int n;
    int id, lin, eng, cp;
    if((rfp = fopen("test.dat", "r")) == NULL){
        perror("fopen");
        exit(1);
    }

    while((n = fscanf(rfp, "%d %d %d %d", &id, &lin, &eng, &cp)) != EOF){
        printf("id : %d, avg = %d\n", id, (lin + eng + cp) / 3);
    }

    exit(0);
}
```
```
$ cat test.dat
2021001 100 85  100
2021002 95  95  100
$ sh test.sh
id : 2021001, avg = 95
id : 2021002, avg = 96
```
#### 형식 기반 출력 함수 : printf(3), fprintf(3)
```C
#include<stdio.h>
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
```
* 인자 설명
    * stream : 파일 포인터
    * format : 출력 형식
* printf(3) : 표준 출력으로 출력
* fprintf(3) : 지정한 파일로 출력
* 성공시 : 출력한 문자 수 리턴
* 실패시 : EOF 리턴
#### 예제 164 : 지정한 파일로 출력하기(fprintf(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* rfp; FILE* wfp; int n;
    int id, lin, eng, cp;
    if((rfp = fopen("test.dat", "r")) == NULL){
        perror("read");
        exit(1);
    }
    if((wfp = fopen("test.scr", "w")) == NULL){
        perror("write");
        exit(1);
    }

    fprintf(wfp, "학번  평균\n");
    while((n = fscanf(rfp, "%d %d %d %d", &id, &lin, &eng, &cp)) != EOF){
        fprintf(wfp, "id : %d, avg = %d\n", id, (lin + eng + cp) / 3);
    }

    fclose(rfp);
    fclose(wfp);
    exit(0);
}
```
```
$ sh test.sh
$ cat test.scr
학번  평균
id : 2021001, avg = 95
id : 2021002, avg = 96
```
### 4.3.7 파일 오프셋 지정
#### 파일 오프셋 이동 : fseek(3)
```C
#include<stdio.h>
int fseek(FILE* stream, long offstet, int whence);
```
* 인자 설명
    * stream : 파일 포인터
    * offset : 이동할 오프셋
    * whence : 오프셋의 기준 위치
* lseek(2)와의 차이
    * lseek(2) : 성공시 변경된 오프셋 리턴
    * fseek(3) : 성공시 0을 리턴(현재 오프셋을 구하는 함수가 별도로 있음 : ftell(3))
#### 현재 오프셋 구하기 : ftell(3)
```C
#include<stdio.h>
long ftell(FILE* stream);
```
* 성공시 : 인자로 지정한 파일의 현재 오프셋 리턴
* 실패시 : EOF 리턴
#### 처음 위치로 오프셋 이동 : rewind(3)
```C
#include<stdio.h>
void rewind(FILE* stream);
```
#### 예제 168 : 오프셋 이동하며 읽어서 출력하기(fseek(3), ftell(3), rewind(3))
```C
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* fp;
    int n;
    long cur;
    char buf[BUFSIZ];
    if((fp = fopen("test.txt", "r")) == NULL){
        perror("fopen");
        exit(1);
    }

    cur = ftell(fp);
    printf("current offset : %d\n", (int)cur);
    n = fread(buf, sizeof(char), 5, fp);
    buf[n] = '\0';
    printf("str : %s\n", buf);

    fseek(fp, 1, SEEK_CUR);
    cur = ftell(fp);
    printf("current offset : %d\n", (int)cur);
    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = '\0';
    printf("str : %s\n", buf);

    fseek(fp, 1, SEEK_CUR);
    cur = ftell(fp);
    printf("current offset : %d\n", (int)cur);
    n = fread(buf, sizeof(char), 11, fp);
    buf[n] = '\0';
    printf("str : %s\n", buf);

    rewind(fp);
    cur = ftell(fp);
    printf("rewind offset : %d\n", (int)cur);

    fclose(fp);
}
```
```
$ sh test.sh
current offset : 0
str : linux
current offset : 6
str : system
current offset : 13
str : programming
rewind offset : 0
```
### 4.3.8 파일과 디스크 동기화 함수 : fflush(3)
```C
#include<stdio.h>
int fflush(FILE* stream);
```
* 고수준 입출력 함수는 기본적으로 버퍼의 내용을 디스크로 옮겨 씀
    * 이를 항상 보장할 수 없으므로 필요한 경우 강제 수행시킴
* 버퍼에 있는 데이터를 파일에 기록함
* 읽기 전용으로 연 경우 버퍼에 있는 내용을 모두 비움
* 파일 포인터가 NULL이면 쓰기 전용으로 연 모든 파일에 데이터를 씀
## 4.4 파일 기술자와 파일 포인터 변환
### 개요
* fdopen(3) : 파일 기술자 -> 파일 포인터
* flieno(3) : 파일 포인터 -> 파일 기술자
### 파일 포인터 생성 : fdopen(3)
```C
#include<stdio.h>
FILE* fdopen(int fd, const char* mode);
```
* 인자 설명
    * fd : 파일 기술자
    * mode : 열기 모드
* mode는 파일 기술자를 열 때와 같은 종류의 값으로 지정해야 함
    * 예시 : 저수준에서 O_RDONLY로 열고 변환시 'w'로 지정하면 작동하지 않음
* 성공시 : 파일 포인터 리턴
* 실패시 : 널 포인터 리턴
### 예제 172 : 파일 포인터 생성하기(fdopen(3))
```C
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* fp;
    int fd;
    char str[BUFSIZ];
    fd = open("test.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    fp = fdopen(fd, "r");
    fgets(str, BUFSIZ, fp);
    printf("read : %s\n", str);

    fclose(fp);
    exit(0);
}
```
```
$  sh test.sh
read : linux system programming!!!!
```
### 파일 기술자 생성 : fileno(3)
```C
#include<stdio.h>
int fileno(FILE* stream);
```
### 예제 173 : 파일 기술자 추출하기(fileno(3))
```C
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* fp;
    int fd, n;
    char str[BUFSIZ];
    if((fp = fopen("test.txt", "r")) == NULL){
        perror("fopen");
        exit(1);
    }

    fd = fileno(fp);
    printf("fd : %d\n", fd);

    n = read(fd, str, BUFSIZ);
    str[n] = '\0';
    printf("read : %s", str);

    close(fd);
    exit(0);
}
```
```
$ sh test.sh
fd : 3
read : linux system programming!!!!
```
## 4.5 임시 파일 사용
### 개요
* 임시파일명이 동일하지 않도록 생성해야함
### 4.5.1 임시 파일명 생성
#### 개요
* 임시 파일명 생성 함수 : tmpnam(3), mktemp(3)
* 파일명만 리턴하므로 파일 생성함수로 파일을 생성하여 사용
#### 임시 파일명 생성 : tmpnam(3)
```C
#include<stdio.h>
char* tmpnam(char* s);
```
* 인자 설명
    * s : 파일명을 저장할 버퍼의 시작 주소
* 인자가 있을 경우 : 인자가 가리키는 곳에 임시파일명 '저장'
* 인자가 NULL일 경우 : 임시파일명을 '리턴'
#### 템플릿을 지정한 임시 파일명 생성 : mktemp(3)
```C
#include<stdlib.h>
char* mktemp(char* template);
```
* 인자 설명
    * template : 임시 파일명의 템플릿
* 성공시 : 임시 파일의 템플릿을 인자로 받아 임시 파일명으로 변환해 리턴
* 실패시 : 널 문자열 리턴
* 템플릿 : X 6개로 마쳐야 함
#### 예제 176 : 임시 파일명 만들기(tmpnam(3), mktemt(3))
```C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
    char* fname1; char* fname2;
    char fntmp[BUFSIZ];
    char template[32];

    fname1 = tmpnam(NULL);
    tmpnam(fntmp);
    strcpy(template, "/tmp/testXXXXXX");
    fname2 = mktemp(template);

    printf("tmp file name(tmpnam) : %s\n", fname1);
    printf("tmp file nmae(tmpnam) : %s\n", fntmp);
    printf("tmp file nmae(mktemp) : %s\n", fname2);
}
```
```
$ sh test.sh
# 보안에 취약한 함수들이므로 경고 메시지가 나올 수 있음
...
warning: the use of `tmpnam' is dangerous, better use `mkstemp'
warning: the use of `mktemp' is dangerous, better use `mkstemp' or `mkdtemp'
tmp file name(tmpnam) : /tmp/file8I9IVQ
tmp file nmae(tmpnam) : /tmp/fileEXfxLq
tmp file nmae(mktemp) : /tmp/testIIsffM
```
### 4.5.2 임시 파일의 파일 포인터와 파일 기술자 생성
#### 개요
* tmpnam(3), mktemp(3) : 임시 파일 이름만 생성함
* 임시 파일 대상 입출력 수행을 위해 파일을 열어야 함
* tmpfile(3), mkstemp(3) : 임시 파일명을 알 필요 없이 파일 포인터, 파일 기술자 리턴
#### 임시 파일의 파일 포인터와 파일 기술자 생성 : tmpfile(3), mkstemp(3)
```C
#include<stdio.h>
FILE* tmpfile(void);
#include<stdlib.h>
int mkstemp(char* template);
```
#### 예제 178 : 임시 파일 생성하기(tmpfile(3), mkstemp(3))
```C
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE* fp;
    int fd;
    char template[32];
    int ret;

    fp = tmpfile();
    fpust("tmep file", fp);
    fclose(fp);

    strcpy(template, "/tmp/testXXXXXX");
    fd = mkstemp(template);
    write(fd, "temp file", 10);
    close(fd);
}
```
```
#프로그램 내에서 임시로 생성했다가 종료하므로 결과로 확인할 수 없음
```