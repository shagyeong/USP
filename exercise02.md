# 2장 연습문제
## 객관식
### 01 리눅스에서 파일의 정보를 저장하고 있는 자료 구조는?
* ***1 : inode***
* 2 : anode
* 3 : fnode
* 4 : unode
### 02 mkdir은 명령과 시스템 호출에서 같은 이름을 사용한다. man 명령으로 mkdir 시스템 호출을 보는 올바른 방법은?
* 1 : man mkdir
* 2 : man -s mkdir
* ***3 : man -s 2 mkdir***
* 4 : man -c 2 mkdir
### 03 opendir() 함수가 디렉터리를 열고 리턴하는 디렉터리 스트림 객체의 이름은?
* 1 : dir
* 2 : dirp
* 3 : dirent
* ***4 : DIR***
### 04 디렉터리의 내용을 읽어서 해당 디렉터리에 있는 파일명을 출력하려고 한다. 디렉터리의 내용을 가져오는 함수는?
* 1 : opendir()
* 2 : telldir()
* ***3 : readdir()***
* 4 : seekdir()

### 05 디렉터리의 정보를 읽으면 디렉터리의 내용을 읽는 위치가 변겨된다. 디렉터리의 특정 위치로 바로 이동할 때 사용하는 함수는?
* 1 : telldir()
* ***2 : seekdir()***
* 3 : readdir()
* 4 : godir()

## 주관식
### 06 mkdir() 함수를 사용해 디렉터리 2개(dir1, dir2) 만들고, 이 중 dir1은 rmdir() 함수로 삭제하고 dir2는 rename() 함수를 사용해 hanbit으로 바꾸는 프로그램을 작성하시오.
```C
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
    mkdir("dir1", 0755);
    mkdir("dir2", 0755);
    
    rmdir("dir1");
    rename("dir2", "hanbit");
}
```
```
$ sh test.sh
$ ls
(...) hanbit (...)
```
### 07 mkdir() 함수를 사용해 존재하지 않는 디렉터리를 삭제하려고 하면 어떤 오류 메시지가 출력되는지 확인하시오.
```C
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(void){
    if(rmdir("test") == -1){
        perror("rmdir");
        exit(1);
    }
}
```
```
$ sh test.sh
rmdir: Not a directory
```
### 08 현재 디렉터리를 기억하고 있다가 다른 디렉터리로 이동해 작업한 후 원래 디렉터리로 돌아오도록 프로그램을 작성하시오.
```C
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(void){
    char buf1[BUFSIZ];
    char buf2[BUFSIZ];

    //현재 디렉터리
    getcwd(buf1, BUFSIZ);
    printf("cwd : %s\n", buf1);

    //디렉터리 이동 후 작업(파일 생성)
    mkdir("dir", 0755);
    chdir("dir");
    int fd;
    fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    close(fd);
    getcwd(buf2, BUFSIZ);
    printf("cwd : %s\n", buf2);

    //현재 디렉터리로 복귀
    chdir(buf1);
    printf("cwd : %s\n", buf1);
}
```
```
$ sh test.sh
cwd : /****/*********/***/*****/***
cwd : /****/*********/***/*****/***/dir
cwd : /****/*********/***/*****/***
$ cd dir
$ ls
test.txt
```
### 09 [예제 2-6]에는 getcwd() 함수가 오류를 리턴할 떄 처리하는 코드가 없다. 오류가 발생할 경우 처리하는 코드를 추가해 예제를 작성하시오.
```C
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    char* cwd;
    if((cwd = getcwd(NULL, BUFSIZ)) == NULL){
        perror("getcwd");
        exit(1);
    }    
    printf("cwd = %s\n", cwd);
    
    chdir("dir01");
    if((cwd = getcwd(NULL, BUFSIZ)) == NULL){
        perror("getcwd");
        exit(1);
    }
    printf("cwd = %s\n", cwd);
    free(cwd);
}
```
### 10 디렉터리가 비어 있는지 확인한 후 디렉터리가 비어 있다는 메시지를 출력하고 해당 디렉터리를 삭제하는 프로그램을 작성하시오.
```C
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int usrrmdir(DIR* dp);

int main(void){
    mkdir("dir", 0755);
    DIR* dp = opendir("dir");
    if(usrrmdir(dp) == -1){
        perror("usrrmdir");
        exit(1);
    }
    rmdir("dir");
}
int usrrmdir(DIR* dp){
    struct dirent* dent;
    dent = readdir(dp); //현재 디렉터리(".");
    dent = readdir(dp); //상위 디렉터리("..");
    if((dent = readdir(dp)) == NULL){
        printf("directory is empty\n");
        return 0;
    }
    printf("directory is not empty\n");
    return -1;
}
```
```
$ sh test.sh
directory is empty
```
### 11 디렉터리명을 명령행 인자로 입력받아 생성하고, 작업 디렉터리를 새로 생성한 디렉터리로 이동시키는 프로그램을 작성하시오.
```C
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char* argv[]){
    mkdir(argv[1], 0755);
    chdir(argv[1]);
    char buf[BUFSIZ];
    printf("cwd : %s\n", getcwd(buf, BUFSIZ));
}
```
```
$ cat test.sh
gcc -o test test.c
./test dir
$ sh test.sh
cwd : /****/*********/***/*****/***/dir
```
### 12 '.'과 '..'항목을 제외하고 디렉터리에 있는 파일이나 하위 디렉터리명을 출력하는 usrls 프로그램을 작성하시오.
```C
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>

void usrls(DIR* dp);

int main(void){
    DIR* dp = opendir(".");
    usrls(dp);
    closedir(dp);
}
void usrls(DIR* dp){
    struct dirent* dent;
    while((dent = readdir(dp)) != NULL){
        if(strcmp(dent->d_name, ".") == 0 | strcmp(dent->d_name, "..") == 0){
            continue;
        }
        else{
            printf("%s ", dent->d_name);
        }
    }
}
```
```
$ sh test.sh
test .git *********.md *********.md ******.md *********.md *** *********.md **********.md
*********.md  .vscod **********.md test.sh *********.md test.c *********.md **********.md
**********.md *********.md *******.md *********.md **********.md 
```
### 13 현재 디렉터리에 파일의 전체 목록을 출력한 후 seekdir()로 디렉터리 스트림의 위치를 바꿔서 세 번째 파일명을 바로 출력하는 프로그램을 작성하시오.
```C
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

int main(void){
    DIR* dp = opendir(".");
    struct dirent* dent;
    long loc;
    int i = 1;

    while((dent = readdir(dp)) != NULL){
        printf("%s ", dent->d_name);
        if(i++ == 3)
            loc = telldir(dp);
    }
    seekdir(dp, loc);
    dent = readdir(dp);
    printf("\n%s\n", dent->d_name);
    closedir(dp);
}

```
```
$ sh test.sh
test .git *******03.md .. (...)
*******03.md
```
### 14 파일명을 명령행 인자로 입력받고 이 파일이 현재 디렉터리에 있는지 확인하는 프로그램을 작성하시오.
```C
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>

int main(int argc, char* argv[]){
    DIR* dp = opendir(".");
    struct dirent* dent;
    while((dent = readdir(dp)) != NULL){
        if(strcmp(argv[1], dent->d_name) == 0){
            printf("%s is in cwd\n", argv[1]);
            return 0;
        }
    }
    printf("%s is not in cwd\n", argv[1]);
    closedir(dp);
    return 1;
}
```
```
$ ./test test.c
test.c is in cwd
$ ./test test.java
test.java is not in cwd
```
### 15 파일명과 디렉터리 경로명을 명령행 인자로 입력받고 인자로 입력한 파일이 해당 디렉터리에 있는지 확인하는 프로그램을 작성하시오.
```C
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

int ismember(char* dir, char* name);

int main(int argc, char* argv[]){
    //가상 환경 : "dir" 디렉터리에 "test.txt" 파일이 있음
    mkdir("dir", 0755);
    chdir("dir");
    int fd;
    fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    close(fd);

    //현재 디렉터리로 되돌아 온 후 테스트
    chdir("..");
    if(ismember(argv[1], argv[2]) == -1){
        perror("ismember");
        exit(1);
    }
}

int ismember(char* dir, char* name){
    DIR* curdp = opendir(".");
    DIR* subdp = NULL; //하위 디렉터리의 디렉터리 포인터를 저장
    struct dirent* dent;
    
    //현재 디렉터리의 하위 디렉터리로 존재하는지 확인
    while((dent = readdir(curdp)) != NULL){
        if(strcmp(dir, dent->d_name) == 0){
            subdp = opendir("dir");
            break;
        }
    }
    //할당받은 디렉터리 주소가 없다면 종료
    if(subdp == NULL){
        printf("directory \"%s\" is not in cwd\n", dir);
        closedir(curdp);
        return -1;
    }
    //하위 디렉터리에 파일이 존재하는지 확인
    while((dent = readdir(subdp)) != NULL){
        if(strcmp(name, dent->d_name) == 0){
            printf("file \"%s\" is  in cwd/%s\n", name, dir);
            closedir(curdp);
            closedir(subdp);
            return 0;
        }
    }
    printf("file \"%s\" is not in cwd/%s\n", name, dir);
    closedir(curdp);
    closedir(subdp);
    return -1;
}
```
```
$ ./test dir test.txt
file "test.txt" is  in cwd/dir
$ ./test dir test.md
file "test.md" is not in cwd/dir
ismember: File exists
$ ./test dir2 test.txt
directory "dir2" is not in cwd
ismember: File exists
```