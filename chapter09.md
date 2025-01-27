# 9장 메모리 매핑
## 9.1 개요
### 9.1.1 개요
#### 개요
- 실제 응용 프로그램은 하나 이상의 실행 파일이 생성되고 프로세스간 시그널/데이터를 주고받으며 작업을 처리
- *통신 프로그래밍* 필요
- 동일한 시스템 또는 다른 시스템간 프로세스간 통신으로 데이터/시그널을 주고받는다
### 9.1.2 프로세스간 통신(IPC)
#### 프로세스간 통신
- 프로세스간 통신: *동일한* 시스템 안에서 수행 중인 프로세스끼리 데이터를 주고받음
- 종료 상태값/시그널을 주고 받는 것도 프로세스간 통신으로 간주할 수 있다
#### 프로세스간 통신 기법
- *파이프* 사용
- 메모리 영역 사용(메모리 매핑, 공유 메모리 이용 등)
- 메시지 큐
- 공유 메모리
- 세마포어
### 9.1.3 네트워크를 이용한 통신
#### 개요
- 네트워크 환경 발전에 따라 서로 다른 시스템간 네트워크를 이용한 통신이 증가(클라이언트-서버 모델)
- TCP/IP 프로토콜을 기반으로 한다
- 소켓 라이브러리 사용
#### 주요 함수
```C
void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);//메모리 매핑
int munmap(void* addr, size_t length);//메모리 매핑 해제
int mprotect(void* addr, size_t len, int prot);//메모리 보호 모드 변경
int truncate(const char* path, off_t length);//파일 크기 조정
int ftruncate(int fd, off_t length);//파일 크기 조정
void* mremap(void* old_address, size_t old_size, size_t new_size, int flags);//메모리 매핑 변경
int msync(vod8 addr, size_t length, int flags);//매핑된 메모리 동기화
```

## 9.2 메모리 매핑과 해제
### 9.2.0 개요
#### 메모리 매핑
- 메모리 매핑: 파일을 프로세의 메모리에 매핑
- 프로세스에 전달할 데이터를 직접 프로세스의 가상 주소 공간으로 매핑
- read(2), write(2)를 사용하지 않고 파일에서 데이터를 읽고 쓸 수 있다
### 9.2.1 메모리 매핑
#### 메모리 매핑: mmap(2)
```C
#include<sys/mman.h>
void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
```
### 9.2.2 메모리 해제
#### 
### 9.2.3 보호 모드 변경
#### 

## 9.3 파일 확장과 메모리 매핑

## 9.4 매핑된 메모리 동기화와 데이터 교환
