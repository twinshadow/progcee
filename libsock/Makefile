VERSION_1= 0
VERSION_2= 1
CFLAGS+= -g -O0 -Wall -Werror -std=c99 -D_POSIX_C_SOURCE -fPIC
SOURCES= libsock.c
OBJECTS= libsock.o
prefix:= /usr

%.a: %.o
	ar -cvq $@ $^

%.so: %.o
	${CC} ${CFLAGS} -shared -o $@ $^

build: all

all: libsock.so libsock.a

install: libsock.so libsock.a
	install $^ ${prefix}/lib

clean:
	rm -f *.o *.a *.so
