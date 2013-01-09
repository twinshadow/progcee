#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

struct oaddr
{
	int len;
	int af;
	unsigned char *buf;
};

int
pton4or6(const char *addr)
{
	if(index(addr, ':') != NULL)
		return(AF_INET6);
	return(AF_INET);
};

int ipr_pton(const char *foo, struct oaddr *oa)
{
	int s;
	oa->af = pton4or6(foo);
	oa->len = (oa->af == AF_INET) ? 4 : 16;
	s = inet_pton(oa->af, foo, oa->buf);
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

int ipr_ntop(struct oaddr *oa, char *str)
{
	if (inet_ntop(oa->af, oa->buf, str, INET6_ADDRSTRLEN) == NULL)
	{
		perror("inet_ntop");
		return(1);
	}

	return(0);
}

int
netaddr_incr(struct oaddr *oa)
{
	int i;
	for(i = oa->len - 1; i >= 0; i--)
	{
		if(oa->buf[i] == 255)
		{
			oa->buf[i]++;
		}
		else
		{
			oa->buf[i]++;
			break;
		}
	}
	return(0);
}

int
main(int argc, char **argv)
{
	char *myp = calloc(sizeof(char), 80);
	int i;
	struct oaddr *ipr = calloc(sizeof(struct oaddr), 1);
	ipr->buf = calloc(16, sizeof(unsigned char));

	if(ipr_pton(argv[1], ipr))
	{
		fprintf(stderr, "Whups, pton failed.\n");
		return(1);
	}
	for(i = 0; i < ipr->len; i++)
	{
		printf("%d\n", ipr->buf[i]);
	}

	for(i = 0; i < 10; i++)
	{
		netaddr_incr(ipr);
		ipr_ntop(ipr, myp);
		printf("%s\n", myp);
	}

	return(0);
}
