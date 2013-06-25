#include <string.h>
#include <stdlib.h>
#include "twinshadow/macros.h"

void
memshift(const int32_t __offset, void *ptr, const size_t count, size_t size)
{
	void *buf;
	size_t buflen;
	int32_t offset = __offset;

	if (count < 1)
		return;

	if (offset > count)
		offset %= MATCH_SIGNEDNESS(offset, count);

	if (offset < 0)
		offset = count - -offset;

	if (offset == 0 || count < 2 || count == offset)
		return;

	//buflen = SMALLEST_DIFFERENCE(count, offset);
	buflen = (count - offset) * size;
	buf = malloc(buflen);

	if (buf == NULL)
		exit(EXIT_FAILURE);

	if (count - offset < buflen)
	{
		memcpy(buf, ptr, buflen);
		memmove(ptr, (ptr + buflen), (offset * size));
		memcpy((ptr + (offset * size)), buf, buflen);
	}
	else
	{
		memcpy(buf, (ptr + buflen), (offset * size));
		memmove((ptr + (offset * size)), ptr, buflen);
		memcpy(ptr, buf, offset);
	}
}

void
strshift(const int64_t offset, char *str, const size_t count)
{
	memshift(offset, str, count, sizeof(char));
}
