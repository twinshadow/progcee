#ifndef TWINSHADOW_VEC_H
#define TWINSHADOW_VEC_H
/* A structure wrapper around the existing array type to provide some
 * operational-safety */

#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Twinshadow vector meta-typing */
#define TS_VEC_HEAD(__name, __type)		\
	struct __name {				\
		size_t sentinal;		\
		size_t cursor;			\
		__type *vec;			\
	}

/* iterators */
#define TS_VEC_FOREACH(__var, __head)				\
	for (__var = &__head->vec[1];				\
		__var != &__head->vec[__head->sentinal];	\
		__var++)

#define TS_VEC_RFOREACH(__var, __head)				\
	for (__var = &__head->vec[__head->sentinal - 1];	\
		__var != __head->vec;				\
		__var--)

/* Memory functions */
#define TS_VEC_NEW(__name, __type)				\
	struct __name *						\
	__name##_new(size_t count){				\
		struct __name *ptr;				\
		if ((count + 2) * sizeof(__type) > SIZE_MAX) {   \
			errno = EACCES;				\
			return NULL;				\
		}						\
		count += 2;					\
		ptr = calloc(1, sizeof(struct __name));		\
		if (ptr == NULL) {				\
			errno = ENOMEM;				\
			return NULL;				\
		}						\
		ptr->vec = calloc(count, sizeof(__type));	\
		if (ptr->vec == NULL) {				\
			free(ptr);				\
			errno = ENOMEM;				\
			return NULL;				\
		}						\
		ptr->sentinal = count - 1;			\
		ptr->cursor = 1;				\
		return ptr;					\
	}

#define TS_VEC_FREE(__name)					\
	void							\
	__name##_free(struct __name *ptr){			\
		free(ptr->vec);					\
		free(ptr);					\
		ptr = NULL;					\
	}

#define TS_VEC_RESIZE(__name, __type)					\
	struct __name *							\
	__name##_resize(struct __name *ptr, size_t count){		\
		size_t old_sentinal;					\
		if (count >= SIZE_MAX					\
		    || count + 2 < count				\
		    || (count + 2) * sizeof(__type) > SIZE_MAX		\
		    || (count + 2) * sizeof(__type)			\
		        < count * sizeof(__type)) {			\
			errno = EACCES;					\
			return NULL;					\
		}							\
		count += 2;						\
		if (ptr == NULL) {					\
			errno = EACCES;					\
			return NULL;					\
		}							\
		ptr->vec = realloc(ptr->vec, count * sizeof(__type));	\
		if (ptr->vec == NULL) {					\
			errno = ENOMEM;					\
			return NULL;					\
		}							\
		old_sentinal = ptr->sentinal;				\
		ptr->sentinal = count - 1;				\
		if (old_sentinal < ptr->sentinal) {			\
			memset(&ptr->vec[old_sentinal + 1],		\
			    '\0', (ptr->sentinal - old_sentinal)	\
			    * sizeof(__type));				\
		}							\
		if (ptr->cursor >= ptr->sentinal) {			\
			ptr->cursor = ptr->sentinal - 1;		\
		}							\
		return ptr;						\
	}

#endif /* TWINSHADOW_VEC_H */
