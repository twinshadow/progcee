#include <errno.h>
#include <stdlib.h>
#include "twinshadow/string.h"
#include "twinshadow/twinshadow.h"

void
ts_memshift(int offset, void *ptr, size_t len)
{
	void *buf;
	int buflen;

	if (len < 2)
		return;

	/* This takes ridiculous offset amounts and reduces them to the actual
	 * amount needed to rotate the appropriate amount. Then, it converts
	 * negative values into their positive equivalents, for simplicity.
	*/
	if (offset > len)
		offset %= MATCH_SIGNEDNESS(offset, len);
	if (offset < 0)
		offset = len - -offset;

	/* Eliminate conditions that would result in no changes */
	if (offset == 0 || len == offset)
		return;

	buflen = (offset < len - offset) ? offset : len - offset;
	buf = malloc(buflen);
	if (buf == NULL)
	{
		errno = ENOMEM;
		return;
	}

	if (buflen < offset)
	{
		memmove(buf, ptr, buflen);
		memmove(ptr, ptr + buflen, len - buflen);
		memmove(ptr + (len - buflen), buf, buflen);
	}
	else
	{
		memmove(buf, ptr + (len - offset), offset);
		memmove(ptr + offset, ptr, len - offset);
		memmove(ptr, buf, offset);
	}
}

void
ts_strshift(int offset, char *str)
{
	ts_memshift(offset, str, strnlen(str, SIZE_MAX - 1));
}
