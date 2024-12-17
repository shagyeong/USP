# 3장 연습문제
## 객관식
### 01 파일명으로 파일 정보를 검색할 때 사용하는 함수는?
* 1 : fstat()
* ***2 : stat()***
* 3 : inode()
* 4 : fopen()
### 02 매크로를 이용해 파일의 종류를 검색하려고 한다. 일반 파일인지 알아내는 매크로는?
* 1 : SISLNK(m)
* 2 : S_ISCHR(m)
* 3 : S_ISFIFO(m)
* ***4 : S_ISREG(m)***
### 03 access(2)를 이용해 han.txt 파일이 존재하는지 확인하려고 한다. 올바르게 사용한 것은?
* 1 : access("han.txt", R_OK);
* 2 : access("han.txt", W_OK);
* 3 : access("han.txt", IS_OK);
* ***4 : access("han.txt", F_OK);***
### 04 chmod(2)를 이용해 han.txt 파일의 권한을 소유자만 읽고 쓸 수 있도록 설정하려고 한다. 올바르게 설정한 것은?
* 1 : chmod("han.txt", S_IRUSR | S_IWGRP);
* 2 : chmod("han.txt", S_IRGRP | S_IWGRP);
* ***3 : chmod("han.txt", S_IRUSR | S_IWUSR);***
* 4 : chmod("han.txt", S_IRWXU | S_IWUSR);
### 05 han.txt 파일의 하드 링크로 han.ln 파일을 만들려고 한다. 맞게 사용한 것은?
* ***1 : symlink("han.txt", "han.ln");***
* 2 : link("han.txt", "han.ln");
* 3 : lin("han.ln", "han.txt");
* 4 : symlink("han.ln", "han.txt");
## 주관식
### 06 명령행 인자로 받은 파일의 크기를 알려주는 프로그램을 작성하시오.
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char* argv[]){
    struct stat statbuf;
    stat(argv[1], &statbuf);
    printf("size : %d\n", (int)statbuf.st_size);
}
```
```
$ ./test test.sh
size : 33
```
### 07 명령행 인자로 받은 파일의 종류를 출력하는 프로그램을 작성하시오.
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char* argv[]){
    struct stat statbuf; stat(argv[1], &statbuf);
    int ftype = statbuf.st_mode & __S_IFMT;
    switch(ftype){
        case(__S_IFSOCK):
            printf("소켓 파일\n");
            break;
        case(__S_IFLNK):
            printf("심벌릭 링크 파일\n");
            break;
        case(__S_IFREG):
            printf("일반 파일\n");
            break;
        case(__S_IFBLK):
            printf("블록 장치 특수 파일\n");
            break;
        case(__S_IFDIR):
            printf("디렉터리\n");
            break;
        case(__S_IFCHR):
            printf("문자 장치 특수 파일\n");
            break;
        case(__S_IFIFO):
            printf("FIFO 파일\n");
            break;
    }
}
```
```
$ ./test test.sh
일반 파일
```
### 08 명령행 인자로 받은 파일의 정보를 추출해 다음 예와 같이 출력하는 프로그램을 작성하시오.
#### 실행 예시
```
$ ./sh test.sh
파일명 : a.c
inode 번호 : *******
파일 종류 : 일반 파일
접근 권한 : ******
UID : ****
```
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
void printstat(char* path);
char* ftype(int type);

int main(int argc, char* argv[]){
    printstat(argv[1]);
}
void printstat(char* path){
    struct stat statbuf; stat(path, &statbuf);
    printf("파일명 : %s\n", path);
    printf("inode 번호 : %d\n", (int)statbuf.st_ino);
    printf("파일 종류 : %s\n", ftype(statbuf.st_mode & __S_IFMT));
    printf("접근 권한 : %d\n", statbuf.st_mode);
    printf("UID : %d\n", statbuf.st_uid);
}
char* ftype(int type){
    switch(type){
        case(__S_IFSOCK):return "소켓 파일";
        case(__S_IFLNK):return "심벌릭 링크 파일";
        case(__S_IFREG):return "일반 파일";
        case(__S_IFBLK):return "블록 장치 특수 파일";
        case(__S_IFDIR):return "디렉터리";
        case(__S_IFCHR):return "문자 장치 특수 파일";
        case(__S_IFIFO):return "FIFO 파일";
    }
}
```
```
$ sh test.sh
파일명 : test.sh
inode 번호 : 403943
파일 종류 : 일반 파일
접근 권한 : 33204
UID : 1000
```
### 09 명령행 인자로 받은 파일의 UID와 접근 권한을 다음 예와 같이 출력하는 프로그램을 작성하시오.
#### 실행 예시
```
$ test.c 1000 rw-r--r--
```
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
void printstat(char* path);
void mode(struct stat statbuf, char* charmode);

int main(int argc, char* argv[]){
    printstat(argv[1]);
}
void printstat(char* path){
    struct stat statbuf; stat(path, &statbuf);
    char charmode[9];mode(statbuf, charmode);
    printf("%s %d %s\n", path, (int)statbuf.st_uid, charmode);
}
void mode(struct stat statbuf, char* charmode){
    unsigned int intmode = statbuf.st_mode;
    //oth
    if(intmode & 1 == 1){charmode[8] = 'x';}else{charmode[8] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[7] = 'w';}else{charmode[7] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[6] = 'r';}else{charmode[6] = '-';} intmode >>= 1;
    //grp
    if(intmode & 1 == 1){charmode[5] = 'x';}else{charmode[5] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[4] = 'w';}else{charmode[4] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[3] = 'r';}else{charmode[3] = '-';} intmode >>= 1;
    //usr
    if(intmode & 1 == 1){charmode[2] = 'x';}else{charmode[2] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[1] = 'w';}else{charmode[1] = '-';} intmode >>= 1;
    if(intmode & 1 == 1){charmode[0] = 'r';}else{charmode[0] = '-';}
}
```
```
$ sh test.sh
test.sh 1000 rw-rw-r--
```
### 10 현재 디렉터리에 있는 모든 파일 및 하위 디렉터리의 이름과 inode를 출력하는 프로그램을 작성하시오.
```C
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

int main(void){
    DIR* dp = opendir(".");
    struct dirent* dent;
    while((dent = readdir(dp)) != NULL){
        printf("%s : %d\n", dent->d_name, (int)dent->d_ino);
    }
    closedir(dp);
}
```
```
$ sh test.sh
test : 392666
.git : 417869
. : 417868
*********.md : 412558
(...)
```
### 11 현재 디렉터리에서 '.', '..' 항목을 제외하고 하위 디렉터리만 출력하는 usrdir프로그램을 작성하시오.
```C
//readdir(3)으로 디렉터리 내 파일 순회
// dent구조체 멤버 d_name을 통해 stat(2)의 인자로 전달
//statbuf->mode_t로 디렉터리인지 일반 파일인지 구분하여 출력
// 일반 파일 : 10xxxx(8) 또는 1000 xxx xxx xxx(2)
// 디렉터리 : 4xxxx(8) 또는 0100 xxx xxx xxx(2)
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main(void){
    mkdir("dir01", 0755);
    mkdir("dir02", 0755);

    DIR* dp = opendir(".");
    struct dirent* dent;
    struct stat statbuf;
    unsigned int mode;

    while((dent = readdir(dp)) != NULL){
        stat(dent->d_name, &statbuf);
        mode = statbuf.st_mode >> 12; //파일 종류 비트만 남김
        if(mode == 4 && strcmp(dent->d_name, ".") != 0 && strcmp(dent->d_name, "..") != 0)
            printf("%s ", dent->d_name);
    }

    rmdir("dir01");
    rmdir("dir02");
}
```
```
$ sh test.sh
.git dir02 .vscode dir01
```
### 12 명령행 인자로 받은 파일의 기존 접근 권한을 출력하고 접근 권한을 변경하는 프로그램을 작성하시오.(문자 모드 기능 구현)
#### 실행 예시
```
$ usrchmod g+w test.c
```
```C
/*
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

void printbinary(int integer){
    for(int j = 15; j > -1; j--){
        printf("%d", integer >> j & 1);
    }
    printf("\n");
}
int returnmask(char* ugo, char* rwx){
    int mask = 0B0000000000000000;
    if(strcmp(rwx, 'x') == 0){mask +=0B001;}
    else if(strcmp(rwx, 'w') == 0){mask +=0B010;}
    else if(strcmp(rwx, 'wx') == 0){mask +=0B011;}
    else if(strcmp(rwx, 'r') == 0){mask +=0B100;}
    else if(strcmp(rwx, 'rx') == 0){mask +=0B101;}
    else if(strcmp(rwx, 'rw') == 0){mask +=0B110;}
    else if(strcmp(rwx, 'rwx') == 0){mask +=0B111;}    
}

int main(int argc, char* argv[]){
    char* fname = argv[argc - 1];
    struct stat statbuf; stat(fname, &statbuf);
    int mode = statbuf.st_mode;
    
    int index1 = 0;
    int index2 = 0;

    char sign; //+-=
    char ugo[3];
    char rwx[3];

    for(int i = 1; i < argc - 1; i++){
        while(argv[i][index1] != '+' && argv[i][index1] != '-'){
            ugo[index2] = argv[i][index1];
            index1++;
            index2++;
        }
        printf("%s", ugo);
        sign = argv[i][index1];
        index1++;
        index2 = 0;
        while(argv[i][index1] != '\0'){
            rwx[index2] = argv[i][index1];
            index1++;
            index2++;
        }
        
        printf("%c %s %s\n", sign, ugo, rwx);
        ugo[0] = '\0';ugo[1] = '\0';ugo[2] = '\0';
        rwx[0] = '\0';rwx[1] = '\0';rwx[2] = '\0';
        index1 = 0;
        index2 = 0;
    }
}



ugo rwx
./test ug+rw test.txt
./test u+rwx g-x o-x test.txt
*/
```
```
```
### 13 명령행 인자로 받은 파일의 기존 접근 권한을 출력하고 접근 권한을 변경하는 프로그램을 작성하시오.(숫자 모드 기능 구현)
#### 실행 예시
```
$ usrchmod 777 test.c
```
```C
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printbinary(int integer){
    for(int j = 15; j > -1; j--){
        printf("%d", integer >> j & 1);
    }
    printf("\n");
}

//세 자리의 팔진수를 십진수로 변환
int octodeci(int octo){
    int deci = 0;
    deci += octo / 100 * 64; octo -= (octo / 100) * 100;
    deci += octo / 10 * 8; octo -= (octo / 10) * 10;
    deci += octo;
    return deci;    
}

int main(int argc, char* argv[]){
    int mode = octodeci(atoi(argv[1]));
    mode |= 0B1111111000000000; //st_mode와 &연산을 하므로 선행하는 7비트는 1로 마스크
    struct stat statbuf; stat(argv[2], &statbuf);
    
    printf("prev mode : "); printbinary(statbuf.st_mode);
    statbuf.st_mode |= 0B0000000111111111;
    statbuf.st_mode &= mode;
    printf("curr mode : "); printbinary(statbuf.st_mode);
}
```
```
$ ./test 777 test.c
prev mode : 1000000110110100
curr mode : 1000000111111111
```
### 14 현재 디렉터리의 파일을 지정한 디렉터리로 이동시키는 프로그램을 작성하시오.
#### 실행 예시
```
$ usrmv test.c dir
```
```C
```
```
```
### 15 다른 파일 시스템에 있는 파일의 하드 링크를 생성하면 어떤 오류 메시지가 발생하는지 확인하시오.
```C
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    if(link("test.java", "test.ln") == -1){
        perror("link");
        exit(1);
    }
}
```
```
$ ./test
link: No such file or directory
```
### 16 명령행 인자로 받은 파일의 심벌릭 링크를 생성하고 심벌릭 링크 파일의 내용과 원본 파일의 경로를 출력하는 프로그램을 작성하시오.
* 실행 예
```
$ usrsym test.c
```
```C
#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    if(symlink(argv[1], "test.sym") == -1){
        perror("symlink");
    }
    char buf[BUFSIZ];
    readlink("test.sym", buf, BUFSIZ); printf("%s\n", buf);
    realpath("test.sym", buf); printf("%s\n", buf);
}
```
```
$ ./test test.txt
test.txt
/home/*********/***/*****/***/test.txt
```

### 17 현재 디렉터리에서 inode가 같은 파일을 검색해 파일명을 출력하는 프로그램을 작성하시오.
```C
```
```
```
### 18 현재 디렉터리에 어떤 파일의 하드 링크가 여러 개 있을 때 그중에 한 파일만 남기고 링크를 모두 끊는 프로그램을 작성하시오.
```C
```
```
```