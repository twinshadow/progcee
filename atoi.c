#include <stdio.h>
#include <stdlib.h>

/*
 * This isn't treating the input as a long
 * Not sure why...
 */
int main(int argc, const char *argv[])
{
  int i;

  for (i=1; i < argc; i+=1) {
    printf ("atoi: %d, ", atoi(argv[i]));
    printf ("atol: %ld, ", atol(argv[i]));
    printf ("atoll: %lld\n", atoll(argv[i]));
  }

  return 0;
}
