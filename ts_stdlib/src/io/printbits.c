#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define PRINTBITS(X)				\
void						\
printbits_X(X *obj)				\
{						\
	int i;					\
	for (i = sizeof(X) * 8; i > -1; i--)	\
		printf("%d", !!((obj >> i) & 1));\
	puts("");				\
}
