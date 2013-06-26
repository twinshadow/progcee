#include <ctype.h>
#include "twinshadow/string.h"

void
ts_strnstrip(char *str, size_t len)
{
	char *cptr;

	if (str == NULL || len < 1)
		return;

	for (cptr = str; cptr != &str[len - 1] && isspace(*cptr); cptr++);
	for (len -= 1; &str[len] != cptr && isspace(str[len]); len--);

	memmove(str, cptr, len);
	str[len] = '\0';
}

void
ts_strstrip(char *str)
{
	ts_strnstrip(str, strnlen(str, SIZE_MAX - 1));
}
