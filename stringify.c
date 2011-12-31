#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   A simple program showing off string tokenizing, AKA strtok
*/
int main(int argc, char **argv)
{
  if (argc != 3) return 2;

  int i = 0,
      wc;

  char *buffer = argv[2],
       *savedptr,
       *token,
       *word,
       *(wordlist[40]);

  token = strtok_r(buffer, argv[1], &savedptr);
  while (token != NULL)
  {
    wordlist[i] = strdup (token);
    i+=1;
    token = strtok_r (NULL, argv[1], &savedptr);
  }

  wc = i;
  i = 0;
  while (i < wc)
  {
    printf ("%s\n", wordlist[i]);
    i+=1;
  }

  return 0;
}
