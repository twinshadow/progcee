/*
 * prime
 * Displays prime numbers up to 120
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char * prime_sieve (int n);

int main()
{
  int i, n = 120;
  char *primes = prime_sieve(n);

  for (i=2; i <= n; i+=1) {
    if (primes[i] == 0) {
      printf("%d ", i);
    }
  }

  free(primes);
  return 0;
}

/*
 * http://rosettacode.org/wiki/Sieve_of_Eratosthenes#C
 *
 */
char * prime_sieve (int n) {
  int i,j,m;
  char *sieve;

  sieve = calloc (n+1, sizeof(char));
  if (sieve == NULL) exit(1); /* Die if the alloc fails */
  m = (int) sqrt((double) n);

  sieve[0] = 1;
  sieve[1] = 1;

  for (i=2; i <= m; i+=1) {
    if (sieve[i] == 0) {
      for (j = (i*i); j <= n; j+=i) {
        sieve[j] = 1;
      }
    }
  }

  return sieve;
}
