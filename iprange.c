#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include "ipcalc.h"

int
main(int argc, char **argv)
{
	int i;
	char *myp = calloc(sizeof(char), 80);
	struct oaddr_t *ipr = oaddr_from_str(argv[1]);
	if(ipr == NULL)
		return(1);

	for(i = 0; i < ipr->len; i++)
	{
		printf("%d\n", ipr->addr[i]);
	}

	for(i = 0; i < 10; i++)
	{
		oaddr_incr(ipr);
		oaddr_ntop(ipr, myp);
		printf("%s\n", myp);
	}

	return(0);
}
