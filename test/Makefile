# 매크로 정의

# 룰
# 명령어
# 명령어
# (...)

# 룰
# 명령어
# 명령어
# (...)


CC = gcc
CFLAGS = -W -Wall
TARGET = test

all : $(TARGET)
$(TARGET) : gethour.o getminute.o getsec.o test.o
	$(CC) $(CFLAGS) -o $(TARGET) gethour.o getminute.o getsec.o test.o
__itoa.o : __itoa.c
	$(CC) $(CFLAGS) -c -o __itoa.o __itoa.c
gethour.o : gethour.c
	$(CC) $(CFLAGS) -c -o gethour.o gethour.c
getminute.o : getminute.c
	$(CC) $(CFLAGS) -c -o getminute.o getminute.c
getsec.o : getsec.c
	$(CC) $(CFLAGS) -c -o getsec.o getsec.c
test.o : test.c
	$(CC) $(CFLAGS) -c -o test.o test.c

clean:
	rm -f *.o test