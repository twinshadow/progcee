cmdline.o: cmdline.c
	gcc -o $@ $<

hello.o: hello.c
	gcc -o $@ $<

number-guess.o: number-guess.c
	gcc -o $@ $<

prime.o: prime.c
	gcc -lm -o $@ $<

var-args.o: var-args.c
	gcc -o $@ $<

clean:
	@rm -v *.o *.out

.PHONY: clean
