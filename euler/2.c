#include <stdio.h>

int main(void)
{
  unsigned long int i = 1,
                    prev = 0,
                    hold = 0,
                    limit = 4000000,
                    sum = 0;

  while (i < limit) {
    if ((i & 1) == 0) {
      sum += i;
    }

    hold = i + prev;
    prev = i;
    i = hold;
  }

  printf("%ld is the sum of all even fibonacci numbers under %ld\n", sum, limit);
  return 0;
}
