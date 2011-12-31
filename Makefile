CFLAGS = -O0 -g -Wall -Werror
CC = gcc

primes.o: primes.c
	${CC} ${CFLAGS} -lm -o $@ $<

clean:
	@rm -fv *.o *.out

.PHONY: clean
