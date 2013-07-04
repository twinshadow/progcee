#ifndef TWINSHADOW_MACROS_H
#define TWINSHADOW_MACROS_H

#include <stdlib.h>

#define MATCH_SIGNEDNESS(X, Y) ((X > 0) ? ((Y > 0) ? Y : -Y) : ((Y < 0) ? Y : -Y))
#define POSITIVE(X) ((X > 0) ? X : -X)
#define NEGATIVE(X) ((X < 0) ? X : -X)
#define LARGEST_DIFFERENCE(X, Y) ((X - Y > Y) ? X - Y : Y)
#define SMALLEST_DIFFERENCE(X, Y) ((X - Y < Y) ? X - Y : Y)

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#define UNLESS(X) if (!(X))
#define STREQ(X, Y) (!strcmp(X, Y))
#define SWAP(X, Y, Z) { Z = X; \
			X = Y; \
			Y = Z; }
#define ROTATE_RIGHT(W, X, Y, Z) { SWAP(W, X, Z); \
				   SWAP(X, Y, Z); \
				   SWAP(Y, W, Z); }
#define ROTATE_LEFT(W, X, Y, Z) ROTATE_RIGHT(X, Y, W, Z);

#define REPEAT(__idx, __comp) \
	for (__idx = 0; __idx < __comp; __idx++)

/* This takes ridiculous offset amounts and reduces them to the actual amount
 * needed to rotate the appropriate amount. It then converts negative values
 * into their positive equivalents, for simplicity.
*/
#define REDUCE_OFFSET(__offset, __len)	{			\
	if (__offset > __len)					\
		__offset %= MATCH_SIGNEDNESS(__offset, __len);	\
	if (__offset < 0)					\
		__offset = __len - -__offset;			\
}

#define ts_free(__ptr) {free(__ptr); __ptr=NULL;}

#endif /* TWINSHADOW_MACROS_H */
