#include <errno.h>
#include "twinshadow/string.h"
#include "twinshadow/twinshadow.h"

void
strnrot(int offset, char *str, size_t len)
{
	static char *lower = "abcdefghijklmnopqrstuvwxyz";
	static char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static char *digit = "0123456789";

	REDUCE_OFFSET(offset, len);
}
