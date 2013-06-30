#include <errno.h>
#include "twinshadow/string.h"
#include "twinshadow/twinshadow.h"

void
ts_strnrot(int offset, char *str, size_t len)
{
	const char *ciphers[] = {
		"abcdefghijklmnopqrstuvwxyz",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"0123456789",
	};
	const size_t ciphers_len = LENGTH(ciphers);
	size_t cipher_strlen;
	size_t cipher_idx;
	char *chr_idx;
	size_t idx;


	for (idx = 0; idx < len; idx++)
	{
		for (cipher_idx = 0; cipher_idx < ciphers_len; cipher_idx++)
		{
			UNLESS ((chr_idx = strchr(ciphers[cipher_idx], str[idx])))
				continue;

			cipher_strlen = strlen(ciphers[cipher_idx]);
			REDUCE_OFFSET(offset, cipher_strlen);
			if (offset == 0 || offset == cipher_strlen)
				continue;

			str[idx] = (((chr_idx - ciphers[cipher_idx]) + offset
						< cipher_strlen)
					? *(chr_idx + offset)
					: *(ciphers[cipher_idx] +
						(((chr_idx - ciphers[cipher_idx]) + offset) - cipher_strlen)
					)
			);
		}
	}
}

void
ts_strrot(int offset, char *str)
{
	ts_strnrot(offset, str, strnlen(str, SIZE_MAX));
}
