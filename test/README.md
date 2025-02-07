example.h
func1.c
func2.c

test.c

gcc -c func*.c
ar rscv libexample.a *.o
gcc -o test test.c -L./ -lexample
