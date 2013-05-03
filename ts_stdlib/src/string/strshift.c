#include <string.h>
#include <stdlib.h>
#include "twinshadow/macros.h"

void
strshift(int offset, void *str, const int count, size_t size)
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
	
	if(is_string(str, count))
	{
		buf = malloc(buflen + 1);
		((char*)buf)[buflen + 1] = '\0';
	}
	else
		buf = malloc(buflen);
	
	if (buf == NULL)
		exit(EXIT_FAILURE);
	
	if (count - offset < buflen)
	{
		memcpy(buf, str, buflen);
		memmove(str, (char*)str + buflen, offset*size);
		memcpy((char*)str + (offset*size) , buf, buflen);
	}
	else
	{
		memcpy(buf, (char*)str+buflen, offset*size);
		memmove((char*)str+(offset*size), str, buflen);
		memcpy(str, buf, offset);
	}
}

int
is_string(void *a, size_t l)
{
  char *last = (char*)a + sizeof(char) * l;

  return (*last == '\0');
}
