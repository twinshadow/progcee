#include <string.h>
#include <stdlib.h>

void
strshift(int offset, char *str, const int count)
{
	char *buf;

	if (offset > count)
		offset %= count;

	if (offset == 0 || count < 2 || count == offset)
		return;

	buf = malloc(sizeof(char) * count);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	memcpy(buf, str, (count - offset));
	memmove(str, &str[count - offset], offset);
	memcpy(&str[offset], buf, (count - offset));
}
