#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "libipcalc.h"

#define BYTE_MAX 0xFF
#define BYTE_MIN 0x0
#define INET_BYTE_LEN 4
#define INET6_BYTE_LEN 16

int
_pton4or6(const char *addr)
{
	if(strchr(addr, ':') != NULL)
		return(AF_INET6);
	return(AF_INET);
};

bool
in_subnet(struct oaddr_t *oa, struct oaddr_t *subnet)
{
	int i;
	for(i = subnet->len - 1; i >= 0; i--)
	{
		if(subnet->mask[i] == '\0')
			continue;

		if(oa->addr[i] >= (subnet->mask[i] & subnet->addr[i]) &&
		   oa->addr[i] <= (subnet->addr[i] | ((~subnet->mask[i]) & BYTE_MAX)))
			continue;
		else
			return(false);
	}
	return(true);
}

int
ipcalc_pton(int af, const char *str, struct oaddr_t *oa)
{
	int s = inet_pton(oa->af, str, oa->addr);
	if (s <= 0)
	{
		if (s == 0)
			fprintf(stderr, "Not in presentation format: %s", str);
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

void
oaddr_decr(struct oaddr_t *oa)
{
	int i;
	for(i = oa->len - 1; i >= 0; i--)
	{
		oa->addr[i]--;
		if(oa->addr[i] != BYTE_MIN)
			break;
	}
}

void
oaddr_incr(struct oaddr_t *oa)
{
	int i;
	for(i = oa->len - 1; i >= 0; i--)
	{
		oa->addr[i]++;
		if(oa->addr[i] != BYTE_MAX)
			break;
	}
}

struct oaddr_t *
oaddr_new()
{
	struct oaddr_t *oax;
	oax = calloc(1, sizeof(struct oaddr_t));
	oax->addr = calloc(16, sizeof(unsigned char));
	oax->mask = calloc(16, sizeof(unsigned char));
	memset(oax->addr, BYTE_MIN, 16);
	memset(oax->mask, BYTE_MIN, 16);
	return oax;
}

int
oaddr_free(struct oaddr_t *oa)
{
	free(oa->addr);
	free(oa->mask);
	free(oa);
	return(0);
}

struct oaddr_t *
oaddr_from_str(const char *addr)
{
	char *addrbuf;
	char *maskbuf = NULL;
	char *m;
	int i, s = 0;
	int div, mod;
	struct oaddr_t *oax = oaddr_new();

	addrbuf = calloc(128, sizeof(char));
	strcpy(addrbuf, addr);
	/* CIDR notation */
	if((m = strchr(addrbuf, '/')) != NULL)
	{
		strtok(addrbuf, "/");
		maskbuf = strtok(NULL, "/");
	}

	oax->af = _pton4or6(addr);
	oax->len = (oax->af == AF_INET) ? INET_BYTE_LEN : INET6_BYTE_LEN;

	if(maskbuf != NULL)
	{
		/* TODO: test for dotted-decimal mask */
		/* decimal */
		errno = 0;
		i = strtol(maskbuf, NULL, 10);
		if(errno != 0)
			perror("oaddr_from_str maskbuf");
		div = i / 8;
		mod = i % 8;
		for(i = 0; i < oax->len; i++)
		{
			if(i < div)
				oax->mask[i] = BYTE_MAX;
			else if(i == div)
			{
				if(mod)
					oax->mask[i] = pow(2, mod);
				break;
			}
		}
	}
	else
	{
		memset(oax->mask, BYTE_MAX, oax->len);
	}

	s = inet_pton(oax->af, addrbuf, oax->addr);
	free(addrbuf);

	if (s <= 0)
	{
		if (s == 0)
			fprintf(stderr, "Not in presentation format\n");
		else
			perror("inet_pton");
		return(NULL);
	}
	return(oax);
}

int
oaddr_to_str(const char *addr, struct oaddr_t *oa)
{
	int i;
	char addrbuf[INET6_ADDRSTRLEN];
	char maskbuf[33];

	if (inet_ntop(oa->af, oa->addr, addrbuf, INET6_ADDRSTRLEN) == NULL)
	{
		perror("oaddr_ntop");
		return(1);
	}

	if(maskbuf == NULL)
		return(1);

	for(i = 0; i < oa->len; i++)
	{
	}

	return(0);
}
