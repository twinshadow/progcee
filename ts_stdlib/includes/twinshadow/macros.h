#ifndef TWINSHADOW_MACROS_H
#define TWINSHADOW_MACROS_H

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#define UNLESS(X) if (!(X))
#define STREQ(X, Y) (!strcmp(X, Y))
#define SWAP(X, Y, Z) { Z = X; \
			X = Y; \
			Y = Z; }
#define DEBUG(X) if(_DEBUG) printf

#endif /* TWINSHADOW_MACROS_H */
