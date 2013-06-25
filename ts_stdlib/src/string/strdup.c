#include <stdlib.h>
#include <string.h>

char *
ts_strndup(const char *src, size_t len)
{
	char *buf;
	if (src == NULL)
		return (NULL);

	buf = calloc(len, sizeof(char));
	if (buf == NULL)
		return (NULL);

	memcpy(buf, src, len);
	return (buf);
}

char *
ts_strdup(const char *src)
{
	return (ts_strndup(src, strlen(src) + 1));
}
