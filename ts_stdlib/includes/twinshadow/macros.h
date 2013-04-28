#ifndef TWINSHADOW_MACROS_H
#define TWINSHADOW_MACROS_H

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
#define DEBUG(X) if(_DEBUG) printf

#endif /* TWINSHADOW_MACROS_H */
