/* 오류 메시지 출력(perror(), strerror()) */
extern void perrortest(void);
extern void strerrortest(void);

int main(void){
    perrortest();
    strerrortest();

    return 0;
}