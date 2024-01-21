CC=gcc
CFLAGS=
OBJS=main.o perrortest.o strerrortest.o
LIBS=

all : main.out

main.out : $(OBJS)
	$(CC) $(CFLAGS) -o main.out $(OBJS) $(LIBS)

main.o : main.c
	$(CC) $(CFLAGS) -c main.c
perrortest.o : perrortest.c
	$(CC) $(CFLAGS) -c perrortest.c
strerrortest.o : strerrortest.c
	$(CC) $(CFLAGS) -c strerrortest.c

clean:
	rm -f $(OBJS) main.out *.o core