#include <string.h>
#include <stdlib.h>
#include "twinshadow/macros.h"

void
memshift(int offset, void *str, const int count, size_t size)
{
	void *buf;
	size_t buflen;

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
		memcpy(buf, str, buflen);
		memmove(str, str + buflen, offset*size);
		memcpy((char*)str + (offset*size), buf, buflen);
	}
	else
	{
		memcpy(buf, str+buflen, offset*size);
		memmove(str+(offset*size), str, buflen);
		memcpy(str, buf, offset);
	}
}

void
strshift(int offset, char *str, const int count)
{
	memshift(offset, str, count, sizeof(char));
}
