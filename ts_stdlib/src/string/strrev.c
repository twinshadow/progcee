#include <string.h>
#include <errno.h>
#include "twinshadow/macros.h"

void
ts_strnrev(char *str, const size_t count)
{
	int i, half;
	char cptr;

	if (count < 1)
		return;

	half =  (count) / 2;

	for (i = 0; i <= half; i++)
	{
		if (str[i] == str[count - i])
			continue;
		SWAP(str[i], str[count - i], cptr);
	}
}

void
ts_strrev(char *str)
{
	if (str[0] == '\0')
		return;

	ts_strnrev(str, strlen(str) - 1);
}
