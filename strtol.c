#include <stdlib.h>
#include <stdio.h>
int
main(int argc, char **argv)
{
	int i;
	for (i=1; i < argc; i+=1) {
		printf ("strol: %ld\n", strtol(argv[i], NULL, 16));
		printf ("stroll: %lld\n", strtoll(argv[i], NULL, 16));
	}
	return(0);
}
