#include <stdio.h>

int main(void)
{
  int i = 1,
      limit = 1000,
      sum = 0;

  while (i < limit) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }

    i += 1;
  }

  printf("%i is the sum of all multiples of 3 or 5 under %i\n", sum, limit);
  return 0;
}
