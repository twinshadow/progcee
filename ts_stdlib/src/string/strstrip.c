#include <ctype.h>
#include <string.h>

void
strstrip(char *str, int count)
{
	char *cptr;

	if (str == NULL || count < 1)
		return;

	for (cptr = str; cptr != &str[count - 1] && isspace(*cptr); cptr++);
	for (count -= 1; &str[count] != cptr && isspace(str[count]); count--);

	memmove(str, cptr, count);
	str[count] = '\0';
}
