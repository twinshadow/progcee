#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define unless(X) if(!(X))

void
usage()
{
	puts("Enter a value for prime determiniation.");
}

int
isprime(int64_t primeint)
{
	int64_t mod, limit, index;

	switch (primeint)
	{
		case 0:
		case 1:
			return (EXIT_FAILURE);
		case 2:
		case 3:
			return (EXIT_SUCCESS);
	}

	/* divisible by two or three*/
	unless (primeint & 1 &&
		primeint % 3 )
		return (EXIT_FAILURE);

	limit = sqrt(primeint) + 1;
	for (index = 6; index <= limit; index += 6)
	{
		unless (primeint % (index - 1) &&
			primeint % (index + 1))
			return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

int
main(int argc, char **argv)
{
	int64_t i;
	if (argc < 2)
	{
		usage();
		return (EXIT_FAILURE);
	}

	i = atoll(argv[1]);
	return (isprime(i));
}
