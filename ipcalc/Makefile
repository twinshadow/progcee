CC=clang
VERSION_1= 0
VERSION_2= 1
CFLAGS+= -g -O0 -Wall -Werror -std=c99 -D_POSIX_C_SOURCE -fPIC
LDFLAGS+= -lm
SOURCES= ipcalc.c
OBJECTS= ipcalc.o
prefix:= /usr

%.a: %.o
	ar -cvq $@ $^

%.so: %.o
	${CC} ${CFLAGS} -shared -o $@ $^

build: all

all: ipcalc.o

clean:
	rm -f *.o *.a *.so
