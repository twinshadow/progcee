#include <stdio.h>
#include <ctype.h>
#include "twinshadow/string.h"

void
ts_strnstrip(char *str, size_t len)
{
	char *cptr;

	if (str == NULL || str[0] == '\0' || len < 1)
		return;

	len -= 1;
	for (cptr = str; cptr != &str[len] && isspace(*cptr); cptr++, len--);
	for (; &cptr[len] != cptr && isspace(cptr[len]); len--);

	len += 1;
	memmove(str, cptr, len);
	str[len] = '\0';
}

void
ts_strstrip(char *str)
{
	ts_strnstrip(str, strnlen(str, SIZE_MAX - 1));
}
