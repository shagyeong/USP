/* 시스템 호출의 오류 처리 방법 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

extern int errno;

/* access 매뉴얼 페이지 섹션 2(시스템 호출) */

int main(void){
    if(access("test.txt", F_OK) == -1){ /* test.txt가 없음 */
        printf("errno = %d\n", errno);
        exit(1);
    }

    return 0;
}

/*
errno = 2

코드스페이스에서 헤더 파일 참조 불가
...
(중략)
...
#deine ENOENT 2 /* No such file or directory */


/*man access
...
(중략)
...
ENOENT A component of pathname does not exist or is a dangling symbolic link.

*/