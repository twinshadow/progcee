#include <stdio.h>

int main(void)
{
  printf("char:\t\t%d\n", sizeof(char));
  printf("signed char:\t\t%d\n", sizeof(signed char));
  printf("unsigned char:\t\t%d\n", sizeof(unsigned char));
  printf("short int:\t%d\n", sizeof(short int));
  printf("int:\t\t%d\n", sizeof(int));
  printf("long int:\t%d\n", sizeof(long int));
  printf("long long int:\t%d\n", sizeof(long long int));
  printf("float:\t\t%d\n", sizeof(float));
  printf("double:\t\t%d\n", sizeof(double));
  printf("long double:\t%d\n", sizeof(long double));
  return 0;
}
