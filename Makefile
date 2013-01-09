CFLAGS = -Wall -Werror -O0 -g

socks_rx: socks_rx.c libsocks.o
socks_tx: socks_tx.c libsocks.o
	${CC} ${CFLAGS} -lreadline -o $@ $^

prime: prime.c
	${CC} ${CFLAGS} -lm -o $@ $^

iprange: iprange.c
	${CC} -I${PWD}/ipcalc ${CFLAGS} -lm -o $@ $^ ipcalc/ipcalc.o

clean:
	@rm -f *.o *.out

.PHONY: clean
