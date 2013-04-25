#define PRINTBITS(X)					\
void							\
printbits_X(X *obj)					\
{							\
	int i;						\
	for (i = sizeof(X) * 8; i > -1; i--)		\
		printf("%d", !!((obj >> i) & 1));	\
	puts("");					\
}

#define PRINTBITS_STRUCT(X)				\
void							\
printbits_X(struct X *obj)				\
{							\
	int i;						\
	for (i = sizeof(struct X) * 8; i > -1; i--)	\
		printf("%d", !!((obj >> i) & 1));	\
	puts("");					\
}
