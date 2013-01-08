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

int ipr_pton(int af, const char *foo, unsigned char *buf)
{
	int s;
	s = inet_pton(af, foo, buf);
	if (s <= 0)
	{
		if (s == 0)
			fprintf(stderr, "Not in presentation format");
		else
			perror("inet_pton");
		return(1);
	}

	return(0);
}

int ipr_ntop(int af, unsigned char *buf, char *str)
{
	if (inet_ntop(af, buf, str, INET6_ADDRSTRLEN) == NULL)
	{
		perror("inet_ntop");
		return(1);
	}

	return(0);
}

int
netaddr_incr(int af, unsigned char *buf)
{
	int i, len;
	if(af == AF_INET)
		len = 3;
	else
		len = 15;
	for(i = len; i >= 0; i--)
	{
		if(buf[i] == 255)
		{
			buf[i]++;
		}
		else
		{
			buf[i]++;
			break;
		}
	}
	return(0);
}

int
main(int argc, char **argv)
{
	char *myp = calloc(sizeof(char), 80);
	int i, len;
	unsigned char *ipr;
	int af = pton4or6(argv[1]);
	if(af == AF_INET)
	{
		ipr = malloc(sizeof(struct in_addr));
		len = 4;
	}
	else
	{
		ipr = malloc(sizeof(struct in6_addr));
		len = 16;
	}

	ipr_pton(af, argv[1], ipr);
	/*
	for(i = 0; i < len; i++)
	{
		printf("%d\n", ipr[i]);
	}
	*/

	for(i = 0; i < 8000; i++)
	{
		netaddr_incr(af, ipr);
		ipr_ntop(af, ipr, myp);
		printf("%s\n", myp);
	}

	return(0);
}
