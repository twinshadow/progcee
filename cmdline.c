/* 
 * cmdline ...
 * Prints the arguments entered on the command-line
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  int i;

  for(i=0; i < argc; i+=1) {
    printf("Command line argument %d is %s\n", (i+1), argv[i]);
  }

  return 0;
}
