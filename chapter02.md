# 2장 디렉터리 다루기
## 2.1 개요
### 2.1.0 개요
#### 리눅스 파일 구분
- 일반 파일
- 특수 파일
- 디렉터리
#### 리눅스 파일 구성
- 파일명
- inode
- 데이터 블럭
### 2.1.1 디렉터리 생성/삭제
#### 디렉터리 생성/삭제 함수
```C
int mkdir(const char* pathname, mode_t mode);
int rmdir(const char* pathnname);
```
### 2.1.2 디렉터리 관리
#### 디렉터리 관리 함수
```C
//현재 위치 확인
char* getcwd(char* buf, size_t size);
char* get_current_dir_name(void);
//디렉터리명 변경
int rename(const hcar* oldpath, const char* newpath);
//디렉터리 이동
int chdir(const char* path);
int fchdir(int fd);
```
### 2.1.3 디렉터리 읽기
#### 디렉터리 읽기 함수
```C
//열기
DIR* opendir(const char* name);
//닫기
int closedir(DIR* dirp);
//내용 읽기
struct dirent* readdir(DIR* dirp);
//오프셋 조작
long telldir(DIR* dirp);
void seekdir(DIR* dirp, long loc);
void rewinddir(DIR* dirp);
```

## 2.2 리눅스 파일의 특징

## 2.3 디렉터리 생성과 삭제
### 2.3.1 디렉터리 생성
#### 디렉터리 생성: mkdir(2)
```C
#include<sys/stat.h>
#include<sys/types.h>
int mkdir(const char* pathname, mode_t mode);
```
- 성공시: 0 리턴
- 실패시: -1 리턴
#### 예제: 디렉터리 생성
- test.c
    ```C
    #include<sys/stat.h>
    #include<sys/types.h>

    int main(void){
        //0755
        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
        mkdir("TEST", mode);
    }
    ```
- demo
    ```
    $ ./test
    $ ls -l
    drwxr-xr-x 2 (...) TEST
    (...)
    ```
### 2.3.2 디렉터리 삭제
#### 디렉터리 삭제: rmdir(2)
```C
#include<unistd.h>
int rmdir(const char* pathname);
```
#### 예제: 디렉터리 삭제
- test.c
    ```C
    #include<unistd.h>

    int main(void){
        rmdir("TEST");
    }
    ```
- demo
    ```
    $ ./test
    $ ls
    (...)
    ```

## 2.4 디렉터리 관리

## 2.5 디렉터리 내용 읽기
