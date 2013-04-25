#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
	int *dingo = malloc(sizeof(int));
	printf("valid 0x%x\n", dingo);
	free(dingo);
	printf("Freed 0x%x\n", dingo);
	dingo = NULL;
	printf("NULL 0x%x\n", dingo);
	return(0);
}
