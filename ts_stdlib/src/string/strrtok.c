#include "twinshadow/string.h"
#include <stdio.h>

char*
ts_strrtok_r(char *str, const char delim, char **saveptr)
{
	char *cptr;
	cptr = strrchr(str, delim);

	if (cptr)
		*saveptr = cptr;
	else
	{
		if (*saveptr == NULL)
			return NULL;
		*saveptr = NULL;
		return str;
	}

	*cptr++ = '\0';
	return cptr;
}

char*
ts_strrtok(char *str, const char delim)
{
	static char *lastptr = NULL;
	return ts_strrtok_r(str, delim, &lastptr);
}
