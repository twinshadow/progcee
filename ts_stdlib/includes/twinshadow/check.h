#ifndef TWINSHADOW_CHECK_H
#define TWINSHADOW_CHECK_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#define new_ck_str(X, Y) char *X = calloc(sizeof(Y), sizeof(char)); \
			 ck_assert_ptr_ne(X, NULL); \
			 strcpy(X, Y);

#endif /* TWINSHADOW_CHECK_H */
