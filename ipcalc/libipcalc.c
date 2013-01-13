#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "libipcalc.h"

#define BYTE_MAX 0xFF
#define BYTE_MIN 0x0
#define INET_BYTE_LEN 4
#define INET6_BYTE_LEN 16

#define _4or6(addr) ((strchr(addr, ':') == NULL) ? AF_INET : AF_INET6)
#define oaddr_length(oaz) ((oaz->address_family == AF_INET) ? INET_BYTE_LEN : INET6_BYTE_LEN)

int
in_network(struct oaddr_t *oa, struct oaddr_t *subnet)
{
	if(oaddr_isbad(oa) || oaddr_isbad(subnet))
		return -1;

	int i;
	for(i = subnet->length - 1; i >= 0; i--)
	{
		if(subnet->netmask[i] == '\0')
			continue;

		if(oa->address[i] >= (subnet->netmask[i] & subnet->address[i]) &&
		   oa->address[i] <= (subnet->address[i] | ((~subnet->netmask[i]) & BYTE_MAX)))
			continue;
		else
			return(0);
	}
	return(1);
}

/*
 * Given an address with a network mask, make a new oaddr object for the
 * broadcast address
 */
struct oaddr_t*
oaddr_broadcast(struct oaddr_t *oa)
{
	if(oaddr_isbad(oa))
		return NULL;

	int i;
	struct oaddr_t *bcast;

	bcast = oaddr_copy(oa);
	if(bcast == NULL)
		return NULL;

	for(i = oa->length - 1; i >= 0; i--)
		   bcast->address[i] = (oa->address[i] | ((~oa->netmask[i]) & BYTE_MAX));
	memset(bcast->netmask, BYTE_MAX, bcast->length);

	return bcast;
}

int
ipcalc_pton(int af, const char *str, struct oaddr_t *oa)
{
	if(str == NULL)
		return -1;

	if(oaddr_isbad(oa))
		return -1;

	int s = inet_pton(oa->address_family, str, oa->address);
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
	if(str == NULL)
		return -1;

	if(oaddr_isbad(oa))
		return -1;

	if (inet_ntop(oa->address_family, oa->address, str, INET6_ADDRSTRLEN) == NULL)
	{
		perror("oaddr_ntop");
		return(1);
	}

	return(0);
}

void
oaddr_decr(struct oaddr_t *oa)
{
	if(oaddr_isbad(oa))
		return;

	int i;
	for(i = oa->length - 1; i >= 0; i--)
	{
		oa->address[i]--;
		if(oa->address[i] != BYTE_MIN)
			break;
	}
}

void
oaddr_incr(struct oaddr_t *oa)
{
	if(oaddr_isbad(oa))
		return;

	int i;
	for(i = oa->length - 1; i >= 0; i--)
	{
		oa->address[i]++;
		if(oa->address[i] != BYTE_MAX)
			break;
	}
}

struct oaddr_t *
oaddr_new()
{
	struct oaddr_t *oax;

	oax = calloc(1, sizeof(struct oaddr_t));
	if(oax == NULL)
		return NULL;

	oax->address = calloc(16, sizeof(unsigned char));
	oax->netmask = calloc(16, sizeof(unsigned char));
	memset(oax->address, BYTE_MIN, 16);
	memset(oax->netmask, BYTE_MIN, 16);

	return oax;
}

struct oaddr_t *
oaddr_copy(struct oaddr_t *oa)
{
	if(oaddr_isbad(oa))
		return NULL;

	struct oaddr_t *oax;
	memcpy(oax, oa, sizeof(struct oaddr_t));
	memcpy(oax->address, oa->address, oa->length);
	memcpy(oax->netmask, oa->netmask, oa->length);

	return oax;
}

int
oaddr_free(struct oaddr_t *oa)
{
	if(oa == NULL)
		return 0;

	free(oa->address);
	free(oa->netmask);
	free(oa);

	return(0);
}

// XXX: I forgot enums
int
oaddr_isbad(struct oaddr_t *oa)
{
	if(oa == NULL)
		return OADDR_NULL;
	if(oa->length < 4)
		return OADDR_TOOSMALL;
	if(oa->address_family != AF_INET6 || oa->address_family != AF_INET)
		return OADDR_BADAF;
	if(oa->address == NULL)
		return OADDR_NOADDR;
	if(oa->netmask == NULL)
		return OADDR_NOMASK;

	return 0;
}

struct oaddr_t *
oaddr_from_str(const char *addr)
{
	if(addr == NULL)
		return NULL;
	if(strlen(addr) > 128)
		return NULL;

	char *addrbuf;
	char *maskbuf = NULL;
	char *m;
	int i, s = 0;
	int div, mod;
	struct oaddr_t *oax;

	oax = oaddr_new();
	if(oax == NULL)
		return NULL;

	addrbuf = calloc(128, sizeof(char));
	strcpy(addrbuf, addr);
	/* CIDR notation */
	if((m = strchr(addrbuf, '/')) != NULL)
	{
		strtok(addrbuf, "/");
		maskbuf = strtok(NULL, "/");
	}

	oax->address_family = _4or6(addr);
	oax->length = oaddr_length(oax);

	if(maskbuf != NULL)
	{
		/* TODO: handle dotted-decimal mask */
		/* decimal CIDR notation */
		errno = 0;
		i = strtol(maskbuf, NULL, 10);
		if(errno != 0)
			perror("oaddr_from_str maskbuf");
		div = i / 8;
		mod = i % 8;
		for(i = 0; i < oax->length; i++)
		{
			if(i < div)
				oax->netmask[i] = BYTE_MAX;
			else if(i == div)
			{
				if(mod)
					oax->netmask[i] = pow(2, mod);
				break;
			}
		}
	}
	else
	{
		memset(oax->netmask, BYTE_MAX, oax->length);
	}

	s = inet_pton(oax->address_family, addrbuf, oax->address);
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

	if (inet_ntop(oa->address_family, oa->address, addrbuf, INET6_ADDRSTRLEN) == NULL)
	{
		perror("oaddr_ntop");
		return(1);
	}

	if(maskbuf == NULL)
		return(1);

	for(i = 0; i < oa->length; i++)
	{
	}

	return(0);
}
