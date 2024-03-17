# 2장 디렉터리 다루기
### 학습목표
* 리눅스 디렉터리와 파일의 특징을 이해한다.
* 함수를 사용해 디렉터리를 생성하고 삭제할 수 있다.
* 함수를 사용해 디렉터리를 관리할 수 있다.
* 함수를 사용해 디렉터리의 내요을 읽을 수 있다.
### 중요 개념
* 2.1 개요 : 리눅스 파일의 구분, 파일의 구성, 디렉터리 관리 함수
* 2.2 리눅스 파일의 특징 : 일반 파일, 특수 파일(장치 파일), 디렉터리, 블록 장치, 문자 장치, 주, 부 장치 번호, 파일 식별 문자, 파일명, inode, 데이터블록
* 2.3 디렉터리 생성과 삭제 : 디렉터리 생성과 삭제
* 2.4 디렉터리 관리 : 
* 2.5 디렉터리 내용 읽기 : 

## 예제 명세
### 2.3 디렉터리 생성과 삭제
* 066 : 디렉터리 생성하기(mkdir(2))
* 067 : 디렉터리 삭제하기(rmdir(2))
### 2.4 디렉터리 관리
* 070 : 현재 디렉터리의 위치 검색하기 1(getcwd(3))
* 072 : 현재 디렉터리의 위치 검색하기 2(get_current_dir_name(3))
* 073 : 디렉터리명 변경하기(rename(2))
* 074 : 디렉터리 이동 1(chdir(2))
* 076 : 디렉터리 이동 2(fchdir(2))
### 2.5 디렉터리 내용 읽기
* 000 : ...
* 000 : ...

## 2.1 개요
### 디렉터리
* 리눅스에서는 디렉터리를 파일의 한 종류로 취급함
* 리눅스 파일의 구분
    * 일반 파일(regular file) : 텍스트 파일, 실행 파일 등 텍스트나 바이너리 형태의 데이터를 저장하고 있는 파일
    * 특수 파일(special file) : 장치를 구동하는데 사용되는 파일-'장치 파일(devoce file)'이라고도 함
    * 디렉터리 : 해당 디렉터리에 속한 파일을 관리하는 특별한 파일
* 디렉터리의 구성
    * 하위 디렉터리
    * 하위 파일
### 파일의 구성
* 파일명 : 사용자가 파일에 접근할 때 이용
* inode : '데이터 블록'의 위치를 나타내는 주소들이 저장되어 있음
    * 외부적으로는 변호로 표시됨
    * **디렉터리에는 디렉터리에 속한 파일의 inode 번호와 이에 매핑된 파일명 목록이 들어 있음**
* 데이터 블록 : 실제로 데이터가 저장되는 하드디스크의 공간
    * 파일 소유자, 크기 등의 정보와 **실제 데이터를 저장**하고 있음
### 디렉터리 관리 함수
* 디렉터리 생성 : mkdir(2)
* 디렉터리 삭제 : rmdir(2)
* 현재 위치 확인 : getcwd(3), get_current_dir_name(3)
* 디렉터리명 변경 : rename(2)
* 디렉터리 이동 : chdir(2), fchdir(2)
* 디렉터리 열기 : opendir(3)
* 디렉터리 닫기 : closedir(3)
* 디렉터리 내용 읽기 : readdir(3)
* 디렉터리 오프셋 : telldir(3), seekdir(3), rewinddir(3)

## 2.2 리눅스 파일의 특징
### 개요
* 리눅스 파일의 이용 : 데이터 저장, 장치 구동, 프로세스간 통신 등에 이용됨
* 디렉터리 이해를 위해 리눅스 파일의 종류와 구성 요소에 대해 알아봄
### 2.2.1 파일의 종류
#### 파일의 구분
* 일반 파일
* 특수 파일(장치 파일)
* 디렉터리
#### 일반 파일
* 일반 파일 : 텍스트 파일, 실행 파일, 라이브러리, 이미지 등 대부분의 파일이 일반 파일에 해당됨
    * 데이터 블록에 텍스트 또는 바이너리 형태의 데이터를 저장함
    * vi등 편집기를 이용해 만들거나 컴파일러 또는 다른 응용 프로그램에서 생성할 수도 있음
#### 특수 파일
* 특수 파일 : 리눅스에서 통신을 하거나 터미널 또는 디스크 등의 장치를 사용할 때 관련된 특수 파일을 이용해야 함
* 장치 파일 : 장치 관련 특수 파일을 다른파일과 구분하여 장치파일이라고도 함
    * 장치 파일은 **데이터 블록을 이용하지 않음**(데이터 블록에 정보를 직접 저장하지 않고 inode에 장치 관련 정보를 저장하여 간접적으로 이용함)
    * 블록 장치(block device)
        * '블록 단위'로 데이터를 읽고 씀
        * 블록 크기(block size) : 1-8KB 범위에서 조정 가능
    * 문자 장치(character device)
        * '로우 디바이스(*\*raw* device)'라고도 함
            * \*raw : 가공하지 않은, 날것의
        * 하드디스크의 경우 섹터 단위(기본값 512KB)로 데이터를 읽고 씀
* 장치 번호
    * ls -l의 결과에서 나타남
    * 주 장치 번호(major device number)
        * 부 장치 번호 앞에 위치
        * 장치의 종류를 나타냄
    * 부 장치 번호(minor device number)
        * 주 장치 번호 뒤에 위치
        * 장치의 개체 번호를 의미
    * 기본적인 장치 파일은 처음 리눅스를 설치할 때 생성됨
    * 추가로 장착하는 장치의 장치 파일은 장치 추가 절차에 따라 생성됨
#### 디렉터리
* 리눅스에서는 **디렉터리도 파일로 취급**함(리눅스 파일의 종류를 분류할 때 디렉터리가 있었음)
* 디렉터리와 연관된 데이터 블록에는 해당 디렉터리에 속한 파일의 목록과 inode를 저장함('디렉터리의 데이터 블록에 하위 파일의 데이터 블록의 주소(inode)가 저장됨')
#### 파일 종류 식별 문자
* '-' : 일반 파일
* 'd' : 디렉터리
* 'b' : 블록 장치 특수 파일
* 'c' : 문자 장치 특수 파일
* 'l' : 심벌릭 링크
### 2.2.2 파일의 구성 요소
#### 파일명
* 파일명
    * 사용자가 파일에 접근할 때 사용
    * 파일명과 관련된 inode가 반드시 있어야 함
* 파일명 작성 규칙
    * 파일명 길이
        * 이전 : 최대 14자
        * 현재 : 최대 255바이트(단, 리눅스의 경우 255바이트 이상도 가능)
    * 사용 불가 문자
        * '/' : 디렉터리 계층을 구분
        * null문자 : 경로 이름의 끝을 나타냄
        * 출력이 가능한 문자 사용
        * 가능한 특수문자 사용 자제
    * 그 외 규칙
        * 알파벳 대소문자를 구별한다.
        * '.'으로 시작하는 파일(파일과 디렉터리)은 숨김 파일로 간주한다.
#### inode
* inode
    * 파일에 대한 정보를 저장하고 있는 객체
    * 실제로 디스크(데이터 블록)에 저장되어 있음('디렉터리의 데이터 블록에 하위 파일의 inode가 저장되어 있음')
    * 외부적으로는 번호로 표현
    * 내부적으로는 두 부분으로 나누어 정보를 저장함(파일 정보, 데이터블록 주소)
* 파일에 관한 정보
    * 파일 종류, 접근 권한, 크기, 소유자, 소유 그룹, 변경 시각, 하드 링크 수, 데이터 블록 수 등
    * ls -l은 inode의 정보를 읽어서 출력함
* 데이터 블록의 주소
    * ls -i 명령으로 조회
#### 데이터 블록
* 데이터 블록
    * 실제로 데이터가 저장되는 하드 디스크의 공간
    * 일반 파일, 디렉터리, 심벌릭 링크는 데이터 블록에 관련 정보를 '직접' 저장함
    * 장치 파일은 데이터 블록을 사용하지 않고(직접 사용하지 않고) 장치에 관한 정보를 inode에 저장함(inode 또한 실제로 디스크에 저장되어 있으므로 간접적으로 사용함)

## 2.3 디렉터리 생성과 삭제
### 개요
* 디렉터리 생성 : mkdir(2)
* 디렉터리 삭제 : rmdir(2)
### 디렉터리 생성 : mkdir(2)
* mkdir(2) : 생성하려는 디렉터리명을 포함한 경로를 받고 생성하는 디렉터리의 기본 접근 권한을 지정
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 함수 원형
```C
#include<sys/stat.h>
#include<sys/types.h>
int mkdir(const char* pathname, mode_t mode);
```
* pathname : 디렉터리가 포함된 경로
* mode : 접근 권한
* 예제 066 : 디렉터리 생성하기
```C
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(mkdir("dir01", 0755) == -1){
        perror("dir01");
        exit(1);
    }
    exit(0);
}
```
### 디렉터리 삭제 : rmdir(2)
* rmdir(2) : 삭제하려는 디렉터리명을 포함한 경로를 인자로 받고 삭제
* rmdir(1)과 동일한 기능 수행
* 삭제하려는 디렉터리는 '.', '..'을 제외하고 비어있어야 함
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 함수 원형
```C
#include<unistd.h>
int rmdir(const hcar* pathname)
```
* 예제 067 : 디렉터리 삭제하기
```C
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(rmdir("dir01") == -1){
        perror("dir01");
        exit(1);
    }
    exit(0);
}
```

## 2.4 디렉터리 관리
### 개요
* 디렉터리 관리
    * 현재 작업 중인 디렉터리의 위치 검색
    * 디렉터리명 변경
    * 디렉터리 이동
    * ...
### 2.4.1 현재 작업 디렉터리의 위치 검색
#### 개요
* 현재 작업 디렉터리의 위치를 검색할 때 사용하는 함수 : **getcwd(), get_current_dir_name()**, getwd()
#### 현재 작업 디렉터리의 위치 검색 : getcwd(3)
* getcwd(3) : 현재 디렉터리의 절대 경로를 리턴
* 함수 원형
```C
#include<unistd.h>
char* getcwd(char* buf, size_t size);
```
* buf : 현재 디렉터리의 절대 경로를 저장할 버퍼 주소
* size : 버퍼 크기
* 인자 지정 방식
    * buf에 경로를 저장할 만큼 충분한 메모리를 할당, 그 크기를 size에 지정
        * 사용자가 지정한 버퍼에 경로를 저장
    * buf에 NULL을 지정, 할당이 필요한 메모리 크기를 size에 저장
        * size에 지정한 크기로 버퍼를 할당하고 이 버퍼에 겨오를 저장
        * 시스템 내부에서 malloc(3) 함수로 버퍼가 할당되므로 free(3) 함수로 **메모리를 해제해야 함**
    * buf에 NULL을 지정, size는 0으로 지정
        * 저장할 경로의 크기에 맞게 시스템이 알아서 버퍼를 할당하고 경로를 저장
        * 시스템 내부에서 malloc(3) 함수로 버퍼가 할당되므로 free(3) 함수로 **메모리를 해제해야 함**
* 저장할 경로가 버퍼의 크기를 넘으면 NULL을 리턴함
* 예제 070 : 현재 디렉터리의 위치 검색하기 1
```C
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* cwd;
    char wd1[BUFSIZ];
    char wd2[10];

    /*(1)buf, size를 지정하는 경우*/
    getcwd(wd1, BUFSIZ);
    printf("wd1 = %s\n", wd1);
    
    /*(2)buf는 NULL로 지정, size를 지정하는 경우*/
    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd1 = %s\n", cwd);
    free(cwd);

    /*(3)buf는 NULL로 지정, size를 0으로 지정하는 경우*/
    cwd = getcwd(NULL, 0);
    printf("cwd2 = %s\n", cwd);
    free(cwd);

    /*경로가 버퍼의 크기를 넘는 경우*/
    if(getcwd(wd2, 10) == NULL){
        perror("getcwd");
        exit(1);
    }

    exit(0);
}
```
```
$ main.out
wd1 = /home/shagyeong/***/*****/***
cwd1 = /home/shagyeong/***/*****/***
cwd2 = /home/shagyeong/***/*****/***
getcwd: Numerical result out of range
```
* 'BUFSIZ'는 <stdio.h>에  정의되어 있는 상수임
#### 현재 작업 디렉터리의 위치 검색 2 : get_current_dir_nam(3)
* get_current_dir_name(3) : 현제 디렉터리의 절대 경로를 리턴
* void 함수이며, getcwd(NULL, 0)과 같은 방식으로 동작한다고 생각하면 됨
    * free(3) 함수로 **메모리를 해제해야 함**
* 함수 원형
```C
#include<unistd.h>
char* get_current_dir_name(void);
```
* 예제 072 : 현재 디렉터리의 위치 검색하기 2
```C
#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char* cwd = get_current_dir_name();
    printf("cwd = %s\n", cwd);
    free(cwd);
}
```
```
$ main.out
cwd = /home/shagyeong/***/*****/***
```
### 2.4.2 디렉터리명 변경
#### 디렉터리명 변경 : rename(2)
* renmae(2) : 디렉터리명을 새로운 디렉터리명으로 바꿈
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 실행 도중 오류 발생시 원본과 새로운 디렉터리명에 해당하는 파일이 모두 남음
* 함수 원형
```C
#include<stdio.h>
int rename(const char* oldpath, const char* newpath);
```
* oldpath : 변경할 파일(파일과 디렉터리)명
* newpath : 새로운 파일(파일과 디렉터리)명 - 이미 있는 경우 해당 파일/디렉터리를 지움
* 예제 073 : 디렉터리명 변경하기
```C
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(rename("dir01", "dir02") == -1){
        perror("rename");
        exit(1);
    }
    exit(0);
}
```
```
$ ls
****.**, ****.**, ..., dir01
$ main.out
$ ls
****.**, ****.**, ..., dir02
```
### 2.4.3 디렉터리 이동
#### 디렉터리 이동 1 : chdir(2)
* chdir(2) : 이동하려는 디렉터리의 경로를 인자로 받음
* 절대 경로(absolute path), 상대 경로(relative path) 모두 사용 가능
* 단, 디렉터리 이동은 프로그램 내부에서만 진행됨
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 함수 원형
```C
#include<unistd.h>
int chdir(const char* path);
```
* 예제 074 : 디렉터리 이동 1
```C
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    char* cwd;
    
    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd = %s\n", cwd);
    
    chdir("dir01");
    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd = %s\n", cwd);

    free(cwd);
}
```
```
$ main.out
cwd = /home/shagyeong/***/*****/***
cwd = /home/shagyeong/***/*****/***/dir01
$ pwd
/home/shagyeong/***/*****/*** #디렉터리 이동이 프로그램 내에서만 진행된 것을 확인
```
#### 디렉터리 이동 2 : fchdir(2)
* fchdir(2) : *\*파일 디스크립터*를 인자로 받음
    * \*파일 디스크립터 : open() 함수로 디렉터리를 열고 리턴받는 것(3장에 등장)
* 단, 디렉터리 이동은 프로그램 내부에서만 진행됨
* 성공시 : 0 리턴
* 실패시 : -1 리턴
* 함수 원형
```C
#include<unistd.h>
int fchdir(int fd);
```
* 예제 076 : 디렉터리 이동하기
```C
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    char* cwd;
    int fd;

    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd = %s\n", cwd);

    fd = open("dir01", O_RDONLY);
    fchdir(fd);

    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd = %s\n", cwd);

    close(fd);
    free(cwd);
}
```
```
$ main.out
cwd = /home/shagyeong/***/*****/***
cwd = /home/shagyeong/***/*****/***/dir01
$ pwd
/home/shagyeong/***/*****/*** #디렉터리 이동이 프로그램 내에서만 진행된 것을 확인
```


# test
