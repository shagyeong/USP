# 10장 파이프
## 10.1 개요
### 10.1.1 파이프
#### 파이프
- **파이프**: 두 프로세스 사이에서 한 방향으로 통신할 수 있도록 지원
- 한 명령의 표준 출력을 다음 명령에서 표준 입력으로 받아 수행
- '|': 셸 파이프 기호
#### 예제
```
$ cat test.c | more
```
- cat(1)의 표준 출력을 more(1)의 표준 입력으로 사용
- 화면 단위로 출력
### 10.1.2 익명 파이프: pipe
#### 익명 파이프
- 익명(이름 없는) 파이프: 부모-자식 프로세스간 통신을 할 수 있게 해준다
- 수식어가 없는 경우 일반적으로 익명 파이프를 의미
- fork(2)로 자식 프로세스 생성한 자식 프로세스와통신
- 단방향 통신: 한 방향을 선택해야 함
- 양방향 통신: 파이프 2개 생성해야 함
#### 주요 함수
```C
FILE* popen(const char* command, const char* type); //간단한 파이프 생성
int pclose(FILE* stream);   //간단한 파이프 생성
int pipe(int pipefd[2]);    //복잡한 파이프 생성
```
### 10.1.3 이름 있는 파이프: FIFO
#### 이름 있는 파이프
- FIFO: 부모-자식 관계가 아닌 독립적인 프로세스의 파이프 이용 지원
- '이름'으로 식별
#### 주요 함수
```
mknod 파일명 p
mkfifo [-m mode] ...NAME...
```
```C
int mknod(const char* pathname, mode_t mode, dev_t dev);
int mkfifo(const char* pathname, mode_t mode);
```

## 10.2 이름 없는 파이프

## 10.3 이름 있는 파이프
