#include <ctype.h>
#include <string.h>

void
strstrip(char *str, const int count)
{
	int iter, rter;

	if (count < 1)
		return;

	for (iter = 0; iter < count && isspace(str[iter]); iter++);
	for (rter = count - 1; rter > iter && isspace(str[rter]); rter--);

	if (iter)
		memmove(str, &str[iter], rter);

	if (rter < count)
		str[(rter - iter) + 1] = '\0';
}
