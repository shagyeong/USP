/* Makefile과 make */
int subnum(int a){
    int sum = 0;

    for(; a != 0 ; a--){
        sum -= a;
    }

    return sum;
}
