#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char yak[255];
  while (fgets (yak, 255, stdin) != NULL) {
    if (yak[0] == '\0') break;
    printf("%s", yak);
  }
  return 0;
}
