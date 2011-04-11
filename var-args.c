#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int  sum        (int num, ...);
void print_args (const char *format, ...);

int main() {
  int a =  5,
      b =  7,
      c = 11,
      d = 13,
      e = 18,
      result;

  double db =  3.45;
  char   ch =  'x';
  const char *st1 = "Random string",
             *st2 = "Another random string";

  /* Doing stuff */
  result = sum(3, a, b, c);
  printf("%d + %d + %d = %d\n", a,b,c, result);

  result = sum(4, a,b,c,d);
  printf("%d + %d + %d + %d = %d\n", a,b,c,d, result);

  result = sum(5, a,b,c,d,e);
  printf("%d + %d + %d + %d + %d = %d\n", a,b,c,d,e, result);

  print_args("csds", ch, st1, db, st2);

  return 0;
}

int sum (int nArgs, ...) {
  int     result = 0;
  va_list argptr;

  va_start(argptr, nArgs);

  while (nArgs--){
    result += va_arg(argptr, int);
  }

  va_end(argptr);
  return result;
}

/*
  Outputs the type and contents of a variable number of arguments
  with different types. 'format' should be a string containing one
  character for each argument. For example, if 'format' points to
  the string "csds", it signifies that there are four arguments, and
  that:
    'c' : the first argument is a character
    's' : the second argument is a string
    'd' : the third argument is a double
    's' : the fourth argument is a string
  No other argument types other than the three above are supported
  by this function.
*/

void print_args(const char *format, ...) {
  int     n = 0;
  va_list argptr;

  va_start(argptr, format);

  while (format[n]) {
    switch (format[n]) {
      case 'c':
        printf("Argument %d is a char, and is set to: %c\n", n+1, va_arg(argptr, int)); break;
      case 's':
        printf("Argument %d is a string, and is set to %s\n", n+1, va_arg(argptr, char*)); break;
      case 'd':
        printf("Argument %d is a double, and is set to: %f\n", n+1, va_arg(argptr, double)); break;
      default:
        printf("Argument %d is an unrecognized format: %c", n+1, format[n]);break;
    }
    n+=1;
  }

  va_end(argptr);
}
