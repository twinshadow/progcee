#ifndef CHARBUF_H
#define CHARBUF_H
#include <linux/kobject.h>

struct charbuf_obj
{
	struct kobject kobj;
	char *buffer;
	int clear;
	int rot13;
	int reverse;
};
#define to_charbuf_obj(x) container_of(x, struct charbuf_obj, kobj)

struct charbuf_attribute
{
	struct attribute attr;
	ssize_t (*show)(struct charbuf_obj *charbuf, struct charbuf_attribute *attr, char *buf);
	ssize_t (*store)(struct charbuf_obj *charbuf, struct charbuf_attribute *attr, const char *buf, size_t count);
};
#define to_charbuf_attr(x) container_of(x, struct charbuf_attribute, attr)

#endif /* CHARBUF_H */
