CC=clang
VERSION_1= 0
VERSION_2= 1
CFLAGS+= -g -O0 -Wall -Werror -std=c99 -D_POSIX_C_SOURCE -fPIC
LDFLAGS+= -lm
SOURCES= libipcalc.c
OBJECTS= libipcalc.o libipcalc.so libipcalc.a
prefix:= /usr

%.a: %.o
	ar -cvq $@ $^

%.so: %.o
	${CC} ${CFLAGS} ${LDFLAGS} -shared -o $@ $^

build: all

all: ${OBJECTS}

clean:
	rm -f *.o *.a *.so
