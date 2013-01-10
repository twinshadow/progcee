#include <stdio.h>
#include <stdbool.h>
#include "libipcalc.h"

int
main(int argc, char **argv)
{
	int ret = 1;
	if(argc < 3)
	{
		puts("USAGE: subnetcheck 1.2.3.4 1.2.3.0/24");
		return(1);
	}

	struct oaddr_t *oa = oaddr_from_str(argv[1]);
	struct oaddr_t *ob = oaddr_from_str(argv[2]);

	if(oa == NULL || ob == NULL)
	{
		fprintf(stderr, "Address is not valid");
		return(1);
	}
	if(in_subnet(oa, ob))
		ret = 0;

	oaddr_free(oa);
	oaddr_free(ob);
	return(ret);
}
