#ifndef TWINSHADOW_HASH_H
#define TWINSHADOW_HASH_H

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "twinshadow/vec.h"

TS_VEC_HEAD(ts_tabmap, struct ts_table_item_s *);

typedef uint16_t ts_table_key_t;

struct ts_table_item_s {
	struct ts_table_item_s *next;
	ts_table_key_t hash;
	void *ptr;
};

struct ts_table_s {
	ts_table_key_t (*hash)(void *ptr, size_t len);
	struct ts_tabmap *table;
	size_t logsize;
	size_t count;
	size_t len;
};

/* Memory */
struct ts_table_item_s * ts_table_item_new(void *ptr, size_t len, struct ts_table_s *table);
struct ts_table_s * ts_table_new(size_t logsize);
void ts_table_free(struct ts_table_s *table);
void ts_table_init(struct ts_table_s *table);
void ts_table_resize(struct ts_table_s *table);

/* Manipulation */
struct ts_table_item_s ** ts_table_lookup(void *ptr, size_t len, struct ts_table_s *table);
struct ts_table_item_s * ts_table_fetch(void *ptr, size_t len, struct ts_table_s *table);
struct ts_table_item_s * ts_table_add(void *ptr, size_t len, struct ts_table_s *table);
void ts_table_rem(void *ptr, size_t len, struct ts_table_s *table);

#endif /* TWINSHADOW_HASH_H */
