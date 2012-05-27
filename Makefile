CFLAGS = -Wall -Werror -O0 -g
CC = gcc

socks_rx: socks_rx.c libsocks.o
socks_tx: socks_tx.c libsocks.o
	${CC} ${CFLAGS} -lreadline -o $@ $^

prime: prime.c
	${CC} ${CFLAGS} -lm -o $@ $^

clean:
	@rm -f *.o *.out

.PHONY: clean
