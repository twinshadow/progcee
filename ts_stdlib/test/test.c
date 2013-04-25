#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <twinshadow/string.h>

int
main(int argc, char **argv)
{
	if (argc < 2)
		return (EXIT_FAILURE);
	printf("|%s|\n", argv[1]);
	strstrip(argv[1], strlen(argv[1]));
	printf("|%s|\n", argv[1]);
	return (0);
}
