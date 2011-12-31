/*
 * prime
 * Displays prime numbers up to 120
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

/*
 * http://rosettacode.org/wiki/Sieve_of_Eratosthenes#C
 *
 */
char * prime_sieve (unsigned long n)
{
  unsigned long i;
  unsigned long j;
  unsigned long m;
  char *sieve;

  sieve = calloc (n+1, sizeof(char));
  if (sieve == NULL)
          exit(ENOMEM);
  m = (unsigned long) sqrt((double) n);

  sieve[0] = 1;
  sieve[1] = 1;

  for (i=2; i <= m; i+=1)
  {
    if (sieve[i] == 0)
    {
      for (j = (i*i); j <= n; j+=i)
      {
        sieve[j] = 1;
      }
    }
  }

  return sieve;
}

int main(int argc, char **argv)
{
        unsigned long i, n;

        if (argc > 1)
                n = atoll(argv[1]);
        if (n == 0)
                n = 120;

        char *primes = prime_sieve(n);

        for (i=2; i <= n; i+=1)
        {
                if (primes[i] == 0)
                        printf("%lu\n", i);
        }

        free(primes);
        return 0;
}

