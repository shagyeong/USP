# 1장 리눅스/유닉스 시스템 프로그래밍의 이해

# 2장 디렉터리 다루기

# 3장 파일 다루기

# 4장 파일 입출력

# 5장 시스템 정보

# 6장 프로세스 정보
## 6
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
