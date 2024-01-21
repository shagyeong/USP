# Makefile

CC=gcc
CFLAGS=
OBJS=main.o addnum.o subnum.o
LIBS=

all : main.out

main.out : $(OBJS)
	$(CC) $(CFLAGS) -o main.out $(OBJS) $(LIBS)

main.o : main.c
	$(CC) $(CFLAGS) -c main.c
addnum.o : addnum.c
	$(CC) $(CFLAGS) -c addnum.c
subnum.o : subnum.c
	$(CC) $(CFLAGS) -c subnum.c

clean:
	rm -f $(OBJS) main.out *.o core