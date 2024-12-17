# 1장 연습문제
## 객관식
### 01 다음 중 리눅스/유닉스 시스템 프로그래밍과 관련이 있는 표준이 아닌 것은?
* 1 : ANSI C 표준
* 2 : POSIX
* ***3 : 다중 유닉스 명세 -> 단일 유닉스 명세***
* 4 : 시스템 V 인터페이스 정의
### 02 man 페이지 번호에서 시스템 호출을 나타내는 섹션 번호는?
* 1 : 1
* ***2 : 2***
* 3 : 3
* 4 : 5
### 03 시스템 호출이 실패하면 -1을 리턴한 뒤 오류 코드를 특정 변수에 저장한다. 이 변수명은?
* 1 : eno
* 2 : error
* 3 : enum
* ***4 : errno***
### 04 리눅스 기본 명령 중 패턴을 검색할 때 사용하는 명령은?
* 1 : ls
* 2 : cat
* ***3 : grep***
* 4 : which
### 05 han.c를 컴파일 할 때 실행 파일명을 han으로 하려고 한다. gcc 옵션을 바르게 설정한 것은?
* 1 : gcc han.c
* 2 : gcc -c han han.c
* 3 : gcc -a han han.c
* ***4 : gcc -o han han.c***

## 주관식
### 06 시스템 호출과 라이브러리 함수의 차이점을 동작 과정 비교를 통해 설명하시오
* 시스템 호출 : 커널의 모듈을 직접 호출함
* 라이브러리 함수 : 커널의 모듈을 직접 호출하지 않음
### 07 man write 명령을 실행했는데, wirte() 함수가 아니라 write 명령에 대한 매뉴얼이 출력되었다. write() 함수의 매뉴얼을 보려면 어떻게 해야 할까?

```
#섹션 지정 옵션 사용
$ man -s 2 write
```
### 08 시스템 호출에서 오류가 발생하면 errno 변수에 오류의 원인을 설명하는 숫자가 저장된다. 오류 번호가 1이라면 어떤 오류일까?
```
$ vi / usr/include/asm-generic/errno-base.h
...(중략)
#define EPERM	1	/* Operation not permitted */
...(후략)
```
### 09 [예제 1-1]을 수정해 errno 번호뿐만 아니라 오류 메시지도 출력되도록 코드를 수정하시오([예제 1-4] 참조)
```C
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

extern int errno;

int main(void){
	if(access("test.txt", F_OK) == -1){
        printf("errno = %d\n", errno);
        perror("test.txt");

        char* buf = strerror(errno);
        printf("error : %s(test.txt)\n", buf);
	}
}
```
```
$ sh test.sh
errno = 2
test.txt: No such file or directory
error : No such file or directory(test.txt)
```
### 10 gcc로 소스 코드를 컴파일했더니 실행 파일 a.out이 만들어졌다. 실행 파일을 ex10.exe로 만드려면 어떻게 해야 할까?
```
$ gcc -o ex10.exe test.c
```
### 11 gcc로 소스 코드를 컴파일해 실행 파일인 ex11.exe를 만들었다. ls 명령으로 확인하면 ex11.exe가 보이는데 ex11.exe를 실행하면 파일을 찾을 수 없다고 한다. 무엇이 문제이고 어떻게 해결할 수 있는지 설명하시오.
* 
### 12 [예제 1-3]에서 인자로 받은 두 정수의 뺄셈을 계산에 리턴하는 subnum()함수를 subnum.c 파일로 만들고 Makefile을 수정해 실행 파일을 생성한 뒤 실행 결과를 확인하시오.
* 
### 13 프로그램을 실행하는 도중에 정숫값 200개를 저장할 수 있도록 메모리를 할당하려면 어떻게 해야 할까?
```C
(...)
int* p = malloc((sizeof(int) * 200));
(...)
```
### 14 명령행 인자로 받은 정숫값(작은 수, 큰 수) 2개를 받아서 앞의 값부터 뒤의 값까지 합계를 구하는 프로그램을 작성하시오.
```C
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	int a = atoi(argv[1]);int b = atoi(argv[2]);
    int sum = 0;
    while(a <= b){sum += a++;}
    printf("%d\n", sum);
}
```
```
$ ./test 1 4
10
```
### 15 명령행 인자와 getopt()함수를 사용해 다음 명령을 처리하는 프로그램을 작성하시오
* *1) 명령의 이름 : ex1_15.out*
* *2) 명령의 옵션과 동작*
    * *인자가 없을 경우 : -h처럼 사용 가능한 옵션의 목록 출력*
    * *-p : "Welcome Linux System Programming!" 출력*
    * *-n 인자 : "Nice to meet 인자" 형태로 출력*
    * *-h : 사용 가능한 옵션의 목록 출력*
```C
#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int n;
	extern char* optarg;

    while((n = getopt(argc, argv, "pn:h")) != -1){
        switch(n){
            case 'p':
                printf("Welcome Linux System Programming!\n");
                break;
            case 'n':
                printf("Nice to meet %s\n", optarg);
                break;
            case 'h':
                printf("-p, -n\n");
                break;
        }
    }
}
```
```
 ./test -phn shagyeong
Welcome Linux System Programming!
-p, -n
Nice to meet shagyeong
```