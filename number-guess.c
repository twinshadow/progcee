/*
 * number-guess
 * A number guessing game
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE (100)

int main(int argc, const char *argv[])
{
  int goes=0, guess, max = 100, target;
  char buffer[BUFFER_SIZE];

  srand((unsigned) time(NULL));

  printf("Welcome to the Number Guesser\n");
  printf("=============================\n\n");

  do {
    printf("I'm thinking of a number between 1 and %d...\n", max);
    target = rand() % (max + 1);

    do {
      printf("What number is it: ");
      fgets(buffer, BUFFER_SIZE - 1, stdin);

      while (!sscanf(buffer, "%d", &guess)) {
        printf("Enter a number this time: ");
        fgets(buffer, BUFFER_SIZE - 1, stdin);
      }

      if (guess < target) {
        printf("Too low... ");
      } 
      else if ( guess > target ) {
        printf("Too high... ");
      }

      goes+=1;
    } while (guess != target);

    printf("\nCorrect! %d is very correct.\n", target);

    if (goes == 1) {
      printf("Next time, try guessing more. I wrote this as an exception just for you, lucky person.\n\n");
    } else {
      printf("It only took %d attempts...\n\n", goes);
    }
    printf("Would you like to play again? ");
    fgets(buffer, BUFFER_SIZE - 1, stdin);
    printf("\n");

  } while ( buffer[0] == 'y' || buffer[0] == 'Y' );

  printf("Goodbye...\n");
  return 0;
}
