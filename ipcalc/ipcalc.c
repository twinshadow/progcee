#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include "ipcalc.h"

int
pton4or6(const char *addr)
{
	if(index(addr, ':') != NULL)
		return(AF_INET6);
	return(AF_INET);
};

static void
inaddr2buf(struct in_addr addr, unsigned char *buf)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		buf[i] = (unsigned char)((addr.s_addr >> (i * 8)) & 0xFF);
	}
	buf[i] = '\0';
}

int
in_subnet()
{

}

int
ipcalc_pton(int af, const char *foo, unsigned char *buf)
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

int
oaddr_ntop(struct oaddr_t *oa, char *str)
{
	if (inet_ntop(oa->af, oa->addr, str, INET6_ADDRSTRLEN) == NULL)
	{
		perror("oaddr_ntop");
		return(1);
	}

	return(0);
}

static void
oaddr_decr(struct oaddr_t *oa)
{
	int i;
	for(i = oa->len - 1; i >= 0; i--)
	{
		oa->addr[i]--;
		if(oa->addr[i] != 0)
			break;
	}
}

static void
oaddr_incr(struct oaddr_t *oa)
{
	int i;
	for(i = oa->len - 1; i >= 0; i--)
	{
		oa->addr[i]++;
		if(oa->addr[i] != 255)
			break;
	}
}

int
oaddr_new(struct oaddr_t *oa)
{
	struct oaddr_t *oax;
	oax = calloc(1, sizeof(struct oaddr_t));
	oax->addr = calloc(16, sizeof(unsigned char));
	oax->mask = calloc(16, sizeof(unsigned char));
	oa = oax;
	return(0);
}

int
oaddr_destroy(struct oaddr_t *oa)
{
	free(oa->addr);
	free(oa->mask);
	free(oa);
}

int
oaddr_from_str(const char *addr, struct oaddr_t *oa)
{
	int m, s;
	struct oaddr_t *oax;
	if(oaddr_new(oax))
		return(1);
	char *addrbuf;
	char *maskbuf;
	m = sscanf(addr,"%128[^/]/%16[^\n]", addrbuf, maskbuf);
	if(m == 1)
	{
		maskbuf = "32";
	}
	else if (m == 0)
	{
		return(1);
	}
	oax->af = pton4or6(addr);
	oax->len = (oax->af == AF_INET) ? 4 : 16;
	s = inet_pton(oax->af, addr, oax->addr);
	if (s <= 0)
	{
		if (s == 0)
			fprintf(stderr, "Not in presentation format\n");
		else
			perror("inet_pton");
		return(1);
	}
	oa = oax;
	return(0);
}
