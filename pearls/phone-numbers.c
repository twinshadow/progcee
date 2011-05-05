#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

char *filepath[] = "phone-list.txt"
char *number[8];
gzFile numlist;

numlist = gzopen (filepath, 'r')

while (gzgets (numlist, number, 8) != NULL) {
}
