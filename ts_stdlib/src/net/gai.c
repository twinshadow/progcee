#include <string.h>

#include "twinshadow/net.h"

/*
 * Return the addrinfo from the selected options
 */
struct addrinfo*
get_addr(const char *address,
	const char *port,
	const int family,
	const int socktype,
	const int flags,
	const int proto)
{
	struct addrinfo hint;
	struct addrinfo *adr;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = family;
	hint.ai_socktype = socktype;
	hint.ai_flags = flags;
	hint.ai_protocol = proto;

	if (getaddrinfo(address, port, &hint, &adr) != 0)
	{
		if (adr != NULL)
			freeaddrinfo(adr);
		return (NULL);
	}
	return (adr);
}
