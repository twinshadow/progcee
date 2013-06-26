#include <errno.h>
#include "twinshadow/string.h"
#include "twinshadow/twinshadow.h"

void
ts_strnrev(char *str, const size_t len)
{
	int i, half;
	char cptr;

	if (len < 1)
		return;

	half =  (len) / 2;

	for (i = 0; i <= half; i++)
	{
		if (str[i] == str[len - i])
			continue;
		SWAP(str[i], str[len - i], cptr);
	}
}

void
ts_strrev(char *str)
{
	if (str[0] == '\0')
		return;

	ts_strnrev(str, strnlen(str, SIZE_MAX - 1) - 1);
}
