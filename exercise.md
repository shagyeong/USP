# 1장 리눅스/유닉스 시스템 프로그래밍의 이해

# 2장 디렉터리 다루기

# 3장 파일 다루기

# 4장 파일 입출력
## 06
- 저수준 입출력으로 'newcat' 구현
- 파일명을 명령행 인자로 받아 행 번호를 붙여 표준 출력
- test.c
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>

    int main(int argc, char* argv[]){
        char row[1];
        row[0] = 48;        //ASCII 48: '0'

        char buf[1]; int n;
        int rflags = O_RDONLY;
        int rfd = open(argv[1], rflags);
        int wfd = STDOUT_FILENO;

        write(wfd, "row 0: ", 7);
        while((n = read(rfd, buf, 1)) != 0){
            write(wfd, buf, 1);
            if(buf[0] == 10){  //ASCII 10: new line
                write(wfd, "row ", 4);
                row[0]++; write(wfd, row, 1);
                write(wfd, ": ", 2);
            }
        }
        close(rfd);
    }
    ```
- demo
    ```
    $ ./test test.txt
    row 0: Linux
    row 1: System
    row 2: Programming
    row 3: 
    ```
## 07
- 저수준 입출력을 이용해 파일을 복사하는 프로그램 구현
- 파일명은 명령행 인자로 받음
- test.c
    ```C
    #include<sys/types.h>
    #include<sys/stat.h>
    #include<fcntl.h>
    #include<unistd.h>

    int main(int argc, char* argv[]){
        char buf[10]; int n;
        int rfd; int rflags = O_RDONLY;
        int wfd; int wflags = O_CREAT | O_WRONLY | O_TRUNC;
        mode_t wmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        rfd = open(argv[1], rflags);
        wfd = open(argv[2], wflags, wmode);

        while((n = read(rfd, buf, 5)) > 0){
            write(wfd, buf, 5);
        }

        close(rfd);
        close(wfd);
    }
    ```
- demo
    ```
    $ ./test test.txt test.bak
    $ cat test.bak
    Linux System Programming
    ```
## 8
- 저수준 파일 입출력을 이용해 하위 디렉터리를 생성 후 파일을 이동시키는 프로그램 구현
- 생성할 디렉터리명과 이동할 파일명은 명령행 인자로 받음
- test.c
    ```C
    ```
- demo
    ```
    ```
## 9
- test.c
    ```C
    ```
- demo
    ```
    ```
## 10
- test.c
    ```C
    ```
- demo
    ```
    ```
## 11
- test.c
    ```C
    ```
- demo
    ```
    ```
## 12
- test.c
    ```C
    ```
- demo
    ```
    ```
## 13
- test.c
    ```C
    ```
- demo
    ```
    ```
## 14
- test.c
    ```C
    ```
- demo
    ```
    ```
## 15
- test.c
    ```C
    ```
- demo
    ```
    ```
## 16
- test.c
    ```C
    ```
- demo
    ```
    ```

# 5장 시스템 정보

# 6장 프로세스 정보
## 06
- 명령행 인자로 PID를 입력받아 PGID, SID 출력
- 명령행 인자로 PID가 지정되지 않은 경우 현재 프로세스의 PPID, PGID, SID 출력
- test.c
    ```C
    #include<sys/types.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<stdio.h>
    int main(int argc, char* argv[]){
        pid_t pid;
        if(argc == 1){pid = getpid();printf("PPID: %d\n", getppid());}
        else{pid = atoi(argv[1]);}
        printf("PGID: %d\n", getpgid(pid));
        printf("SID: %d\n", getsid(pid));
    }
    ```
- demo
    ```
    $ ./test
    PPID: 7213
    PGID: 11063
    SID: 7213
    $ ./test 7213
    PGID: 7213
    SID: 7213
    ```

# 7장 프로세스 생성과 실행

# 8장 시그널

# 9장 메모리 매핑

# 10장 파이프

# 11장 시스템 V의 프로세스 간 통신

# 12장 소켓 프로그래밍 기초

# 13장 소켓 프로그래밍 활용
