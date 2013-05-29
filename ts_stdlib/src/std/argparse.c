#include <string.h>
#include <stdlib.h>
#include "twinshadow/macros.h"

typedef struct argopt_t {
	char **case_values;
	int case_count;
	char *name;
	int type;
} *Argopt;

int
argmatch(Argopt opt, char *optstr)
{
	int iter;
	for(iter = 0; iter < opt->case_count && opt->case_values[iter] != NULL; iter++)
	{
		if (strcmp(optstr, opt->case_values[iter]))
			return (1);
	}
	return (0);
}

Argopt
argmatches(struct argopt_t **opts, char *optstr)
{
	int iter;
	for(iter = 0; opts[iter] != NULL; iter++)
	{
		if (argmatch(opts[iter], optstr))
			return opts[iter];
	}
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
	int iter1, iter2;
	Argopt opt;
	char *optcase;

	for (; argc != 0 && argv != NULL; argc--, argv++)
	{
		argmatches(opts, *argv);
	}
	return 0;
}

