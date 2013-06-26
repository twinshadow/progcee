#include "twinshadow/string.h"

char*
ts_strrtok_r(char *str, const char delim, char *lastptr)
{
	char *cptr;
	if ((cptr = strrchr(str, delim)) != NULL)
	{
		*cptr = '\0';
		lastptr = ++cptr;
	}
	else if (lastptr == str)
	{
		lastptr = NULL;
	}
	else
	{
		lastptr = str;
	}

	return lastptr;
}

char*
ts_strrtok(char *str, const char delim)
{
	static char *lastptr;
	return ts_strrtok_r(str, delim, lastptr);
}
