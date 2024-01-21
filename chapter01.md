# 1장 리눅스/유닉스 시스템 프로그래밍의 이해
### 개요
* 시스템 프로그래밍 : 시스템에서 제공하는 시스템 호출(system call)과 함수를 사용해 프로그램을 작성하는 것
* 리눅스에서 파일 구분
	* 일반 파일(regular file)
 	* 특수 파일(special file)
	* 디렉터리(directory)
* 파일과 디렉터리러리를 다루는 것은 시스템의 기본으로 볼 수 있음
* 생성, 삭제, 복사, 이동, 내용 읽기 쓰기 등의 기능을 공부함
### 학습목표
* 리눅스/유닉스 시스템과 관련된 표준 이해
* 리눅스/유닉스 시스템 프로그래밍이 무엇인지 이해
* 시스템 호출과 라이브러리 함수의 차이 이해
* 리눅스/유닉스 시스템 기본 명령 사용 가능
* C 컴파일러와 make 도구 사용 가능
### 중요 개념
* 1.1 리눅스/유닉스 시스템 프로그래밍이란 : 리눅스, 시스템 프로그래밍, 시스템 호출, 인터페이스
* 1.2 리눅스/유닉스 시스템 표준 : 유닉스, 시스템V, BSD, 리눅스, ANSI C, POSIX, X/Open 가이드, 단일 유닉스 명세, 시스템 V 인터페이스 정의
* 1.3 시스템 프로그래밍 : 시스템 프로그래밍, 시스템 호출, 라이브러리 함수, 정적 라이브러리, 공유 라이브러리, man 페이지, errno, 시스템 호출과 라이브러리 함수의 오류 처리
* 1.4 시스템 도구 :

## 예제 명세
### 1.3 시스템 프로그래밍
* 029 : man 페이지의 섹션 번호(man(1))
* 031 : 시스템 호출의 오류 처리(errno, access(2))
* 033 : 라이브러리 함수의 오류 처리(errno, fopen(3))
### 1.4 시스템 도구
* 034 : 기본 명령
* 039 : make명령을 사용한 컴파일(Makefile, make(1))
* 042 : 오류 메시지 출력(perror(3), strerror(3))
* 044 : 동적 메모리 할당(malloc(3), calloc(3), realloc(3), free(3))
* 047 : 명령행 인자 출력(argc, argv)
* 051 : 옵션 처리(getopt(3))

## 1.1 리눅스/유닉스 시스템 프로그래밍이란 무엇인가?
### 리눅스
* 리눅스, 유닉스는 서버용 운영체제로 주로 사용됨
* 유닉스와 호환됨
* 오픈소스로 제공됨
* 안정성이 높아지고 성능이 향상되며 다양한 분야에서 사용되고 있음
* U2L : Unix to Linux, 유닉스 시스템을 리눅스 시스템으로 대체하려는 서버 운영체제 시장의 움직임
### 시스템 프로그래밍
* 시스템 프로그래밍 : 시스템에서 제공하는 시스템 호출(system call)을 이용해(라이브러리 함수도 이용) 프로그램을 작성하는 것
* 시스템 호출 : **시스템이 제공하는 서비스**를 **프로그램에서 이용**할 수 있도록 지원하는 프로그래밍 *\*인터페이스*
* 인터페이스(interface)
	* 사전적 의미 : 조화, 경계 등
 	* 공학적 의미 : 장치-장치, 장치-소프트웨어, 소프트웨어-소프트웨어 사이를 연결하는 부분
### 2절 예고
* 리눅스는 유닉스와 호환됨
* 명확하게 정해진 표준은 없지만 유닉스와 관련된 표준에 기반하므로, 유닉스의 표준을 살펴봐야 함
* 리눅스/유닉스의 발전과정과 표준을 간략하게 공부
### 3절 예고
* 시스템 호출과 라이브러리 함수의 유사점과 차이점 공부
* 매뉴얼 페이지
### 4절 예고
* 시스템 프로그래밍에 필요한 기본 도구 공부
	* 리눅스 기본 명령
 	* C 컴파일러
  	* make 명령
  	* perror()
  	* 동적 메모리 할당(dynamic memory allocation)
  	* 명령행 인자(command-line argument) 처리 방법

## 1.2 리눅스/유닉스 시스템 표준
### 유닉스 개요
* 1969년 개발된 운영체제(어셈블리어)
* 통신회사 AT&T 산하 연구소 Bell Laboratory
* Ken Thomphon, Dennis Ritche가 개발
* 1973년 C로 다시 만들며 고급 언어로 작성된 최초의 운영체제
### 유닉스의 발전
* 초기에 소스 코드가 공개되어 대학, 기업에서 쉽게 이용할 수 있었음
* 이에 따라 다양한 기능이 추가됨
* 이후에 두 개의 계열로 나뉘어 각각 발전
	* AT&T의 상용 유닉스(시스템 V)
	* 버클리 대학의 BSD(Berkeley Software Distribution(배포)) : TCP/IP 기반 네트워크 기능을 추가함
### 리눅스의 등장
* 1991년 등장
* 오픈 소스로 공개되어 지속적으로 발전 중
* 같은 *\*커널*을 기반으로 하는 다양한 형태의 배포판을 사용
	* 커널(kernal) : 하드웨어와 프로세스간의 인터페이스, 1장 수준에서는 좁은 의미의 운영체제로 이해하면 됨
* 대표적인 배포판의 종류 : 레드햇 리눅스, CentOS, 페도라 리눅스, Debian 계열의 우분투 리눅스
* 스마프톤 운영체제 : 안드로이드(리눅스 계열), iOS(BSD 계열)
### 그림1-1 유닉스와 리눅스의 발전 과정
* 생략
### 시스템 프로그래밍 표준 개요
* C로 작성한 프로그램의 호환성 보장을 위해 여러 표준이 있음
* 유닉스 기반 운영체제는 대체로 표준을 준수
* 리눅스는 POSIX, 단일 유닉스 규격과의 호환성을 유지하기 위해 노력중
* 주요 표준
	* ANSI C
 	* POSIX
	* X/Open 가이드
 	* 단일 유닉스 명세
  	* 시스템 V 인터페이스 정의
### ANSI C
* ANSI : 미국 표준 협회(American National Standard Institute)
* ANSI에서 정의한 C 명세
* C 문법과 라이브러리, 헤더 파일 등을 정의함
* 국제 표준 기구(ISO)에서 미국 표준 협회에서 정한 C 명세를 받아들여 국제 표준이 되었음
	* ISO : International Standard Organization
### POSIX
* POSIX : Portable Operating System Interface X
* '파직스'라고 읽음
* 유닉스에 기반을 두고 있는 표준 운영체제 인터페이스
* 유닉스 시스템의 공통 *\*API*를 정리했음
	* API : Application Programming Interface, 응용 프로그래밍 인터페이스
* 서로 다른 유닉스 시스템 사이에서 상호 이식이 가능한 애플리케이션 개발을 위해 정해진 표준
* IEEE(전기전자공학자 협회)에서 정의한 규격
* 마지막 글자 'X'는 유닉스 호환 운영체제에 보통 'X'가 붙는 데서 유래했음
* POSIX 1
	* C API의 표준
 	* 파일과 디렉터리, 프로세스 관리, 입출력 등 기본 서비스 제공을 위한 인터페이스 정의
* POSIX 2
	* 표준 셸과 유틸리티 프로그램 인터페이스
### X/Open 가이드
* X/Open : 1984년 유럽의 유닉스 시스템 제조업체를 중심으로 설립된 단체
* 개방 시스템에 관한 표준 정의와 보급을 목적으로 함
* 초기 목표 : 다양하게 파생되고 있는 유닉스 시스템에서 애플리케이션의 이식성을 높임
* XPG(X/Open Portability Guide) : 운영체제 기본 인터페이스, 국제화, 터미널 인터페이스, 프로세스간 통신, C를 ㅍ함한 프로그래밍 언어, 데이터 관리(ISAM, SQL) 등에 관한 지침의 정의되어 있음
* XPG 3 : 1988년 발표, POSIX 표준 통합
* XPG 4 : 1992년 발표, XPG 최종 버전
* 1996년 X/Open은 오픈 소프트웨어 재단과 합병해 오픈 그룹(The Open Group)으로 새 출발, UNIX®의 상표권을 소지중
### 단일 유닉스 명세
* SUS(Single Unix Specification) : 운영체제가 유닉스라는 이름을 사용하기 위해 지켜야 하는 표준의 총칭
* IEEE, ISO, The Open Group의 표준화 작업의 결과물에 바탕을 두고 있음
* 오스틴 그룹이 개발, 유지, 관리를 담당
### 시스템 V 인터페이스 정의
* SVID(System V Interface Definition) : 프로그램과 장치에서 이용할 수 있는 시스템 호출과 C 라이브러리에 관한 표준을 포함
* POSIX와 단일 유닉스 명세에 포함되며 중요도가 떨어졌음

## 1.3 시스템 프로그래밍
### 개요
* C
	*  C로 유닉스 시스템과 리눅스 시스템을 구현함
 	*  C를 이용하면 제어문, 자료형, 배열, 구조체, 포인터 같은 기본 구문으로도 여러 응용 프로그램을 작성할 수 있음
* 상위 레벨 함수
  	* 그러나 많은 경우 쉽게 사용할 수 있는 형태로 제공되는 상위 레벨 함수로 프로그래밍을 함
	* 이 경우 대부분 리눅스에서 제공하는 시스템 호출 서비스를 직접 이용하지 않음
* 시스템 프로그래밍
	* 시스템 호출(system call)을 이용해 프로그램을 작성
### 1.3.1 시스템 호출과 라이브러리 함수
#### 개요
* 리눅스 시스템 제공 서비스 : 파일 시스템 접근, 사용자 정보, 시스템 정보, 시스템 시간 정보, 네트워킹 서비스, ...
* 시스템 호출 : 위 서비스를 이용해 프로그램을 구현할 수 있도록 제공되는 프로그래밍 인터페이스
* 시스템 호출 이용 : 리눅스 시스템 서비스를 직접 이용해 프로그램을 작성할 수 있음
#### 시스템 호출
* 기본 형식 : C 함수와 같음
```C
return = systemcallname(arg1, arg2, ...);
```
* 시스템 호출명 : 함수명처럼 이름이 정의되어 있음
* 시스템 호출의 리턴 : 대부분 성공, 실패 여부를 알려주는 정수값을 리턴, 일부 결과값을 리턴하기도 함
#### 라이브러리 함수
* 라이브러리(library)
	* 미리 컴파일 된 함수를 묶어서 제공하는 특수한 형태의 파일
 	* C는 응용 프로그램 개발에 필요한 함수를 유형(데이터 입출력, 수학 공식, 문자열 처리, ...)별로 분류해 라이브러리로 제공
* 라이브러리 함수
	* 라이브러리에 포함된 함수
 	* 함수를 묶어서 라이브러리로 만드는 이유 : 자주 사용하는 기능을 독립적으로 구현해두어 프로그램 개발과 디버깅을 쉽게 하고 컴파일을 빠르게 하기 위함
* 리눅스 시스템에서 라이브러리 위치 : /usr/lib
* 대부분의 리눅스 시스템에서 /lib은 /usr/lib에 대한 *\*심벌릭 링크*임
	* \*심벌릭 링크 : 경로 형태로 된 다른 디렉터리나 파일에 대한 참조를 포함하고 있는 파일
#### 라이브러리 함수의 확장자
* 라이브러리 이름 : 일반적으로 'lib'으로 시작
* .a : 정적 라이브러리(static library)
	* 프로그램 컴파일시 같이 적재되어 실행파일 구성(실행 파일 크기가 커짐)
* .so : 공유 라이브러리(shared library)
	* 해당 라이브러리가 메모리에 적재됨(실행파일에 포함되지 않음)
 	* 적재된 라이브러리는 다른 실행파일에서도 공유 가능
  	* 메모리 효율을 위해 최근 공유 라이브러리를 많이 사용함
### 1.3.2 시스템 호출과 라이브러리 함수 비교
#### 개요
* 시스템 호출 : 커널(시스템)의 모듈을 직접 호출해 작업
* 라이브러리 함수 : 커널의 모듈을 직접 호출하지 않음(라이브러리 함수에서 커널의 서비스를 이용하려면 '함수 내부'에서 시스템 호출을 사용함)
* 라이브러리 함수가 시스템 호출을 사용하는지까지 알 필요는 없음
#### man 페이지
* 기본 형식과 사용 방법이 유사해 구별이 어려운 경우
* man 페이지의 섹션 번호와 오류 처리 방법을 살피면 구별할 수 있음
* '구별'에 집착할 필요는 없음(사용법을 확인하고 그에 따라 프로그래밍을 하면 됨)
#### man 페이지의 섹션 번호
* man(0) : 리눅스 시스템의 명령, 함수 등 시스템 서비스에 대한 메뉴얼 검색
* 섹션 1 : 일반적인 명령
* 섹션 2 : 시스템 호출
* 섹션 3 : 라이브러리 함수
#### man 페이지 검색
* 같은 이름에 대한 메뉴얼 : 가장 낮은 섹션 번호가 기본으로 출력됨
	* 기본 검색
	```
 	$ man uname
 	UNAME(1)	User Commands	UNAME(1)
 	...(후략)
 	```
 	* 섹션을 지정해 검색
	```
 	$ man -s 2 uname
 	UNAME(2)	Linux Programmer's Manual	Uname(2)
 	...(후략)
 	```
* 리눅스, 유닉스간 결과 출력 형식에 차이가 있음
#### 시스템 호출 오류 처리
* 성공 : 0 리턴
* 실패 : -1 리턴, **전역 변수 errno에 오류 코드를 저장**
* 오류 코드 : man 페이지를 참조
* 예제 : access(2)가 실패한 경우(access는 파일 존재 여부를 확인하는 시스템 호출)
```C
#include<stdio.h>
#include<usinsd.h>
#include<errno.h>

extern int errno;

int main(void){
	if(access("test.txt", F_OK) == -1){
		printf("errno = %d\n", errno);
	}
}
```
```
$ main.o
errno = 2
```
* errno 값의 의미 해석 : 헤더 파일을 참조
```
$ vi / usr/include/asm-generic/errno-base.h
...(중략)
#define EPERM	1	/* Operation not permitted */
#define ENOENT	2	/* NO such file or directory */
...(후략)
```
```
$ man access
...(중략)
ERRORS
	...(중략)
	ENAMETOOLONG
		pathname is too long
	ENOENT A component of pathname does not exist or is a dangling symbolic links
...(후략)
```
#### 라이브러리 함수 오류 처리
* 실패 : NULL 또는 -1(리턴값이 int일 경우) 리턴, **전역 변수 errno에 오류 코드를 저장(시스템 호출과 같음)**
* 예제 : fopen(3)이 실패한 경우
```C
#include<stdlib.h>
#include<usinsd.h>
#include<errno.h>

extern int errno;

int main(void){
	FILE* fp;
	if((fp = fopen("test.txt", "r")) == NULL){
		prinft("errno = %d\n", errno);
		exit(1)
	}
}
```
```
$ main.o
errno = 2
```

## 1.4 시스템 도구
### 개요
* 시스템을 사용하기 위한 기본 명령
* 컴파일 환경
* 오류 처리 함수
* 동적 메모리 할당
* 명령행 인자 처리
### 1.4.1 기본 명령
#### 개요
* 필수적으로 알아야 할 기본 명령 : 시스템 접속, 파일, 디렉터리 관련 명령
#### 로그인/로그아웃 명령
* telnet, ssh : 리눅스 시스템에 접속
* exit, logout : 리눅스 시스템 접속 해제
```
$ telnet shagyeong.co.kr
$ ssh shagyeong.co.kr
$ exit
$ logout
```
#### 파일/디렉터리 명령
* pwd(print working directory) : 현재 디렉터리 경로 출력
* ls(list) : 디렉터리 내용 출력
	* -a : 숨김 파일 출력
 	* -l : 파일 상세 정보 출력
* cd(change directory) : 디렉터리 이동
* cp(copy) : 파일 복사
	* -r : 디렉터리 복사
* mv(move) : 파일명/디렉터리명 변경, 파일/디렉터리 이동
* rm(remove) : 파일 삭제
	* -r : 디렉터리 삭제
* rmdir(remove directory) : 빈 디렉터리 삭제
* cat(catenate) : 파일 내용 출력
* more : 화면 크기 단위로 파일 내용 출력
* chmod(change mode) : 파일/디렉터리 접근 권한permission 변경
* grep(global regular expression print) : 패턴 검색
```
$ pwd
$ ls -a
$ ls -l
$ cd ..
$ cd /dir1
$ cd ~
$ cp a.txt b.txt
$ cp -r dir1 dir2
$ mv a.txt c.txt
$ mv dir1 dir3
$ mv a.txt dir2
$ rm a.txt
$ rm *
$ rm -r dir2
$ mkdir dir3
$ rmdir dir3
$ cat a.txt
$ more a.txt
$ chmode 755 a.exe
$ chmode go+x a.exe
$ grep abc a.txt
```
#### 프로세스 명령
* ps(process status) : 현재 실행 중인 프로세스의 정보 출력
	* -ef : 모든 프로세스의 상세 정보 출력
* kill : 프로세스 강제 종료
	* -9 : 강제 종료
```
$ ps -ef
$ ps -ef|grep ftp
$ kill 5000
$ kill -9 5001
```
#### 기타 명령
* su(switch user) : 사용자 계정 변경
	* - : 변경할 사용자의 환경 초기화 파일 실행
* tar(tape archive) : 파일/디렉터리 묶기
	* cvf : tar 파일 생성
	* tvf : tar 파일 내용 보기
	* xvf : tar 파일 풀기
* whereis, which : 파일 위치 검색
```
$ su
$ su -
$ su - han02
$ tar cvf a.tar *
$ tar tvf a.tar
$ tar xvf a.tar
$ whereis ls
$ which telnet
```
#### vi 편집기 내부 명령
```
$ vi test.c
```
* 생략
### 1.4.2 컴파일 환경
#### 개요
* 컴파일 : **원시 프로그램**(고급 언어)를 **목적 프로그램**(기계어)로 변환하는 과정
* 링크 : 1개 이상의 **목적 프로그램**을 묶어 **실행 프로그램**으로 변환하는 과정
* 일반적으로 컴파일 과정과 링크 과정을 묶어 '컴파일한다'라고 표현함
* 예제 : printf(3)을 포함한 원시 프로그램을 컴파일 하는 과정
	* test.c 를 컴파일
	* test.o 생성
	* printf.o를 링크하여 실행파일 생성
#### GNU C 컴파일러 : gcc
* 리눅스, 유닉스에 gcc 설치 가능
* gcc는 ANSI C와 호환성이 있음
```
$ gcc -o test.out test.c
$ ls
test.out test.c
$./test.out
```
#### Makefile과 make
* Makefile : 컴파일 명령, 원시 파일을 컴파일하는 방법, 링크할 파일, 실행 파일명 등을 설정하는 파일
* make : Makefile을 읽고 이 파일에서 지정한대로 컴파일을 실행해 실행 파일 생성
* make 설치
```
$ sudo apt install make
```
* Makefile 예제 : 외부 파일에 정의된 함수를 main()에서 사용
* 
```
# Makefile

CC=gcc					# 컴파일 명령을 gcc로 지정
CFLAGS=					# 컴파일 옵션이 필요한 경우 지정
OBJS=main.o addfunc.o			# 목적 프로그램 파일 명 지정
LIBS=					# 기본 gcc 라이브러리 외 다른 라이브러리가 필요한 경우 지정
all : add.out				# 실행 파일명 지정

# 실행 파일을 어떻게 생성할 것인지 지정
add.out : $(OBJS)
	$(CC) $(CFLAGS) -o add.out $(OBJS) $(LIBS)

# 각 목적 프로그램 파일을 어떻게 생성할지 지정
main.o : main.c
	$(CC) $(CFLAGS) -c main.c
addfunc.o : addfuc.c
	$(CC) $(CFLAGS) -c addfunc.c
# make clean 수행 시 실행할 명령 지정
clean:
	rm -f $(OBJS) add.out *.o core
```
```
$ ls
Makefile addfunc.c main.c
$ make
gcc -c main.c
gcc -c addfunc.c
gcc -o add.out main.o addfucn.o
$ add.out
result of function : (...)
```
```
$ ls
Makefile add.out addfunc.o addfunc.c main.o main.c
$ make clean
rm -f addfunc.o main.o add.out *.o core
$ ls
Makefile addfunc. main.c

```
### 1.4.3 오류 처리 함수
#### 개요
* 1.3절 : 오류 발생 시 errno에 오류 코드 저장됨
* errno에 저장되는 상수만으로는 의미 파악이 어려움
* perror(3), strerror(3) : **오류 코드를 메시지로 변환**하여 출력
#### 차이점
* perror(3) : errno에 저장된 상수를 인자로 받지 않음, 리턴값 없이 오류 메시지만을 출력함
* strerror(3) : errno에 저장된 상수를 인자로 **받음**, **오류 메시지 문자열을 가리키는 포인터를 리턴**하여 사용자가 적절하게 가공 가능
#### 오류 메시지 출력 : perror(3)
* perror(3) : errno에 저장된 값을 읽어 해당 메시지를 표준 오류로 출력
* 출력 순서 : 함수의 인자로 지정한 문자열(일반적으로 프로그램 이름을 지정)-콜론-오류 메시지
* 함수 원형
```C
#include<stdio.h>
void perror(const char* s);
```
* s : 출력할 문자열
* 예제 : access(2) 오류
```C
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

int main(void){
	if(access("test.txt", R_OK) == -1){ /* 시스템 호출은 오류 발생 시 -1 리턴 */
		perror("test.txt");
		exit(1);
	}
	return 0;
}
```
```
$ main.out
test.txt : No such file or directory
```
#### 오류 메시지 출력 : strerror(3)
* strerror(3) : errno에 저장된 값을 인자로 받아 오류 메시지(오류 메시지 문자열을 가리키는 포인터)를 리턴
* ANSI C에서 추가로 정의한 함수임
* 함수 원형
```C
#include<string.h>
char* strerror(int errnum);
```
* errnum : errno에 저장된 값
* 예제 : access(2) 오류
```C
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

extern int errno

int main(void){
	char* err;
	if(access("test.txt", R_OK) == -1){
		err = strerror(errno);
		printf("오류 : %s(test.txt)\n", err); /* 오류 메시지를 사용자가 가공 */
		exit(1);
	}
	return 0;
}
```
```
$ main.out
오류 : No such file or directory(test.txt)
```
### 1.4.4 동적 메모리 할당
#### 개요
* 배열은 프로그램이 시작될 때 필요한 메모리를 미리 확보
* 동적 메모리 할당 : 프로그램 **실행 도중** 필요한 메모리 공간을 할당하고 더 이상 사용하지 않을 시 해당 공간을 해제
	* 데이터 양에 따라 메모리 공간을 효율적으로 사용 가능
* 메모리 할당 함수 : malloc(3), calloc(3), realloc(3)
* 메모리 해제 함수 : free(3)
#### 메모리 할당 : malloc(3)
* malloc(3) : 인자로 지정한 크기의 메모리를 할당
* 성공시 : 시작 주소 리턴
* 실패시 : NULL 포인터 리턴
* 바이트 단위로 크기 지정
* 어떠한 형태의 데이터도 저장 가능
* 할당된 메모리를 초기화하지 않는다는 점에 주의
* 함수 원형
```C
#include<stdlib.h>
void* malloc(size_t size);
```
* 예제 : 문자(char) 100개를 저장할 수 있는 메모리를 할당
```C
char* ptr = malloc(sizeof(char) * 100);
```
#### 메모리 할당과 초기화 : calloc(3)
* calloc(3) : 배열 요소의 개수, 각 배열 요소의 크기를 인자로 받아 메모리를 할당
* nmemb * size바이트 크기의 배열을 저장할 메모리 할당
* 할당된 메모리를 0으로 초기화
* 함수 원형
```C
#include<stdlib.h>
void* calloc(size_t nmemb, size_t size);
```
* 예제 : 요소의 개수 20, 요소의 크기 10
```C
char* ptr = calloc(20, 10);
```
#### 메모리 추가 할당 : realloc(3)
* realloc(3) : 이미 할당받은 메모리의 포인터와 할당할 메모리의 크기를 인자로 받아 메모리 추가 할당, 새로운 메모리를 할당하고 주소를 리턴(이전 메모리의 내용은 복사됨)
* 함수 원형
```C
#include<stdlib.h>
void* realloc(void* ptr, size_t size);
```
* 예제 : malloc()으로 할당받은 메모리에 100바이트 추가 할당
*
```C
char* ptr = malloc(sizeof(char) * 100);
char* new = realloc(ptr, 100);
free(ptr);
```
#### 메모리 해제 : free(3)
* free(3) : 사용을 마친 메모리를 해제하고 반납
* 함수 원형
```C
#include<stdlib.h>
void free(char* ptr);
```
### 1.4.5 명령행 인자
#### 개요
* 명령행command line : 리눅스 시스템에서 사용자가 명령을 입력하는 행(프롬프트에서 커서가 사용자 입력을 기다리고 있는 행)
* 명령행 인자CLA(~arguments) : 명령행에서 명령 실행시 해당 명령(또는 실행 파일명)과 함께 지정하는 인자
* 명령행 인자의 구성 : 명령의 옵션, 옵션의 인자, 명령의 인자
* 예제 : ls(0)
```
$ ls -l
$ ls /tmp
```
* 명령행 인자 : -l, /tmp
#### 명령행 인자의 전달
* main 함수에서 명령행 인자 전달받기
```C
int main(int argc, char* argv[]){
}
```
* argc : 명령과 인자를 포함한 개수(argv 배열의 크기)
* argv[] : 명령과 각 인자를 담고있는 배열(명령행 인자는 argv에 **문자열 형태**로 저장됨)
* 예제 : 명령행 인자 전달 과정
```C
#include<stdio.h>
int main(int argc, char* argv){
	int n =0;
	printf("argc = %d\n", argc);
	while(n < argc){
		printf("argv[%d] = %s\n", n, argv[n]);
		n += 1;
	}
	return 0;
}
```
```
$ main.out -h 2000
argc = 3
argv[0] = main.out
argv[1] = -h
argv[2] = 2000
```
#### 옵션 처리 : getopt(3)
* argc, argv를 직접 처리 가능하나, 옵션을 일일이 분해해서 처리하는 것은 불편함
* getopt(3) : 명령행 인자로 전달된 함수를 편리하게 처리
* 유닉스(솔라리스) : <stdio.h> 헤더 파일
* 리눅스(POSIX) : <unistd.h> 헤더 파일
* 함수 원형
```C
int getopt(int argc, char* const argv[], const char* opstring);
extern char* optarg;
extern int optind, opterr, optopt;
```
* 
#### 리눅스 명령 기본 규칙 1~14
* Guideline 1
	* Utility names should be between two and nine characters, inclusive.
	* 명령의 이름은  2~9글자 범위 내에서 허용한다.
* Guideline 2
	* Utility names should include lowercase letters (the lower character classification) and digits only from the portable character set.
	* 명령의 이름은 오직 portable character set에 있는 소문자와 숫자만 포함할 수 있다.
	* portable character set : POSIX에서 정의한 이식 가능한 문자 집합
* Guideline 3
	* Each option name should be a single alphanumeric character (the alnum character classification) from the portable character set. The -W (capital-W) option shall be reserved for vendor options.
	* Multi-digit options should not be allowed.
	* 옵션의 이름은 한개의 문자(portable character set으로 부터 온 alphanumeric(a. 문자와 숫자를 구별없이 처리하는) 문자)여야 하며, 다중 숫자(두 자리 수 이상을 의미) 옵션은 허용되지 않는다.
	* (옵션의 이름은 한 글자여야 한다.)
* Guideline 4
	* All options should be preceded by the '-' delimiter character.
	* 모든 옵션 앞에 구획 문자 '-'이 선행해야 한다.
* Guideline 5
	* One or more options without option-arguments, followed by at most one option that takes an option-argument, should be accepted when grouped behind one '-' delimiter.
	* 한 개 이상의 인자 없는 옵션들과, 인자를 취하는 최대 한개의 옵션(가장 오른쪽에 위치)를 하나의 구획 문자 '-'로 묶는 것을 허용한다.
	* (인자가 없는 옵션은 하나의 구획문자 '-' 다음에 묶여서 올 수 있다.(마지막 한 개는 인자가 있을 수 있음))
	* 예시 : util -abcdefg에서 a~f는 반드시 인자를 취하지 않으며 마지막 1개의 옵션인 g는 인자를 취할 수도 있음
* Guideline 6
	* Each option and option-argument should be a separate argument, except as noted in Utility Argument Syntax, item (2).
	* 모든 옵션과 옵션 인자는 구별된 인자여야 한다.(공백또는 탭으로 띄고 입력해야 한다.) Utilty Argument Syntax, item(2)에 명시된 경우는 제외
* Guideline 7
	* Option-arguments should not be optional.
	* 옵션 인자(의 입력)은 선택이 아니다.
	* (인자가 있는 옵션에서 인자를 생략할 수 없다.)
* Guideline 8
	* When multiple option-arguments are specified to follow a single option, they should be presented as a single argument, using <comma> characters within that argument or <blank> characters within that argument to separate them.
	* 한 개의 옵션에 여러 개의 옵션 인자를 명시할 때 <쉼표> 또는 <공백> 문자로 구분하여 한 개의 인자(명령의 인자)로 제공되어야 한다.
* Guideline 9
	* All options should precede operands on the command line.
	* 모든 옵션은 명령행에서 피연산자(명령의 인자)보다 선행해야 한다.
* Guideline 10
	* The first -- argument that is not an option-argument should be accepted as a delimiter indicating the end of options. Any following arguments should be treated as operands, even if they begin with the '-' character.
	* 옵션 인자가 아닌 첫 번째 '--'로 옵션의 끝을 나타낼 수 있으며, 후행 인자는 '-'로 시작하더라도 피연산자(명령의 인자)로 간주된다.
* Guideline 11
	* The order of different options relative to one another should not matter, unless the options are documented as mutually-exclusive and such an option is documented to override any incompatible options preceding it. If an option that has option-arguments is repeated, the option and option-argument combinations should be interpreted in the order specified on the command line.
* Guideline 12
	* The order of operands may matter and position-related interpretations should be determined on a utility-specific basis.
* Guideline 13
	* For utilities that use operands to represent files to be opened for either reading or writing, the '-' operand should be used to mean only standard input (or standard output when it is clear from context that an output file is being specified) or a file named -.
* Guideline 14
	* If an argument can be identified according to Guidelines 3 through 10 as an option, or as a group of options without option-arguments behind one '-' delimiter, then it should be treated as such.
