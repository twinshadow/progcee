#include <string.h>
#include <stdlib.h>
#include "twinshadow/macros.h"

void
strshift(int offset, char *str, const int count)
{
	char *buf;
	int buflen;

	if (count < 1)
		return;

	if (offset > count)
		offset %= MATCH_SIGNEDNESS(offset, count);

	if (offset < 0)
		offset = count - -offset;

	if (offset == 0 || count < 2 || count == offset)
		return;

	//buflen = SMALLEST_DIFFERENCE(count, offset);
	buflen = count - offset;
	buf = malloc((sizeof(char) * buflen) + 1);
	if (buf == NULL)
		exit(EXIT_FAILURE);
	buf[buflen + 1] = '\0';

	if (count - offset < buflen)
	{
		memcpy(buf, str, buflen);
		memmove(str, &str[buflen], offset);
		memcpy(&str[offset], buf, buflen);
	}
	else
	{
		memcpy(buf, &str[buflen], offset);
		memmove(&str[offset], str, buflen);
		memcpy(str, buf, offset);
	}
}
