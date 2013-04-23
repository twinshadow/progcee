#include <string.h>
#include "twinshadow/macros.h"

void
revstr(char *str, const int count)
{
	int i, half;
	char cptr;

	if (count < 1)
		return;

	half =  (count - 1) / 2;

	for (i = 0; i <= half; i++)
		SWAP(str[i], str[count - i - 1], cptr);
}
