#ifndef LIBIPCALC_H
#define LIBIPCALC_H

struct oaddr_t
{
	int length;
	int address_family;
	unsigned char *address;
	unsigned char *netmask;
};

enum
{
	OADDR_NULL,
	OADDR_TOOSMALL,
	OADDR_BADAF,
	OADDR_NOADDR,
	OADDR_NOMASK,
};

int in_subnet(struct oaddr_t *oa, struct oaddr_t *subnet);
int ipcalc_pton(int af, const char *str, struct oaddr_t *oa);
int oaddr_ntop(struct oaddr_t *oa, char *str);
void oaddr_decr(struct oaddr_t *oa);
void oaddr_incr(struct oaddr_t *oa);
struct oaddr_t *oaddr_new();
int oaddr_free(struct oaddr_t *oa);
struct oaddr_t *oaddr_from_str(const char *addr);
int oaddr_to_str(const char *addr, struct oaddr_t *oa);
int oaddr_isbad(struct oaddr_t *oa);
struct oaddr_t *oaddr_copy(struct oaddr_t *oa);

#endif /* LIBIPCALC_H */
