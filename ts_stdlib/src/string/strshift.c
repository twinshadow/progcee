#include <stdlib.h>
#include "twinshadow/string.h"
#include "twinshadow/twinshadow.h"

void
ts_memshift(int32_t offset, void *ptr, size_t len)
{
	void *buf;
	size_t buflen;

	if (len < 1)
		return;

	if (offset > len)
		offset %= MATCH_SIGNEDNESS(offset, len);

	if (offset < 0)
		offset = len - -offset;

	if (offset == 0 || len < 2 || len == offset)
		return;

	//buflen = SMALLEST_DIFFERENCE(len, offset);
	buflen = (len - offset);
	buf = malloc(buflen);

	if (buf == NULL)
		exit(EXIT_FAILURE);

	if (len - offset < buflen)
	{
		memcpy(buf, ptr, buflen);
		memmove(ptr, (ptr + buflen), offset);
		memcpy((ptr + offset), buf, buflen);
	}
	else
	{
		memcpy(buf, (ptr + buflen), offset);
		memmove((ptr + offset), ptr, buflen);
		memcpy(ptr, buf, offset);
	}

	free(buf);
}

void
ts_strshift(int32_t offset, char *str)
{
	ts_memshift(offset, str, strnlen(str, SIZE_MAX - 1));
}
