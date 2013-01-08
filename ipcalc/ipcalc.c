#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int
pton4or6(const char *addr)
{
	if(index(addr, ':') != NULL)
		return(AF_INET6);
	return(AF_INET);
};

int _pton(int af, const char *foo, unsigned char *buf)
{
	int s = inet_pton(af, foo, buf);
	if (s <= 0)
	{
		if (s == 0)
			fprintf(stderr, "Not in presentation format: %s", foo);
		else
			perror("inet_pton");
		return(1);
	}

	return(0);
}

int _ntop(int af, unsigned char *buf, char *str)
{
	if (inet_ntop(af, buf, str, INET6_ADDRSTRLEN) == NULL)
	{
		perror("inet_ntop");
		return(1);
	}

	return(0);
}

static void
netaddr_decr(int af, unsigned char *buf)
{
	int i, len;

	if(af == AF_INET)
		len = 3;
	else
		len = 15;

	for(i = len; i >= 0; i--)
	{
		buf[i]--;
		if(buf[i] != 0)
			break;
	}
}

static void
netaddr_incr(int af, unsigned char *buf)
{
	int i, len;

	if(af == AF_INET)
		len = 3;
	else
		len = 15;

	for(i = len; i >= 0; i--)
	{
		buf[i]++;
		if(buf[i] != 255)
			break;
	}
}
