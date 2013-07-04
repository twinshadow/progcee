#include <string.h>
#include <stdlib.h>
#include "twinshadow/twinshadow.h"

typedef struct argopt_t {
	char **case_values;
	int case_count;
	char *name;
	int type;
} *Argopt;

int
argmatch(Argopt opt, char *optstr)
{
	return (0);
}

Argopt
argmatches(struct argopt_t **opts, char *optstr)
{
	return (NULL);
}

/*
   process all the args and assign them according to the available argopt list

   return 0 on success
   return -1 on failure
*/
int
argparse(int argc, char **argv, struct argopt_t **opts)
{
	return (0);
}

