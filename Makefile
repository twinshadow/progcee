CFLAGS = -O2 -g
CC = clang

prime.o: prime.c
	${CC} -lm -o $@ $<

clean:
	@rm -v *.o *.out

.PHONY: clean
