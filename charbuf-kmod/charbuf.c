#include <linux/kobject.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include "charbuf.h"

/*
 * charbuf set
 */
static ssize_t charbuf_attr_show(struct kobject *kobj,
			     struct attribute *attr,
			     char *buf)
{
	struct charbuf_attribute *attribute;
	struct charbuf_obj *charbuf;

	attribute = to_charbuf_attr(attr);
	charbuf = to_charbuf_obj(kobj);

	if (!attribute->show)
		return -EIO;

	return attribute->show(charbuf, attribute, buf);
}

static ssize_t charbuf_attr_store(struct kobject *kobj,
			      struct attribute *attr,
			      const char *buf, size_t len)
{
	struct charbuf_attribute *attribute;
	struct charbuf_obj *charbuf;

	attribute = to_charbuf_attr(attr);
	charbuf = to_charbuf_obj(kobj);

	if (!attribute->store)
		return -EIO;

	return attribute->store(charbuf, attribute, buf, len);
}

static void charbuf_release(struct kobject *kobj)
{
	struct charbuf_obj *charbuf;

	charbuf = to_charbuf_obj(kobj);
	kfree(charbuf);
}

static const struct sysfs_ops charbuf_sysfs_ops = {
	.show = charbuf_attr_show,
	.store = charbuf_attr_store,
};

/*
 * buffer attribute
 */
static ssize_t buffer_show(struct charbuf_obj *charbuf_obj, struct charbuf_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%s", charbuf_obj->buffer);
}

static ssize_t buffer_store(struct charbuf_obj *charbuf_obj, struct charbuf_attribute *attr,
			 const char *buf, size_t count)
{
	kfree(charbuf_obj->buffer);
	charbuf_obj->buffer = kzalloc(count, GFP_KERNEL);
	if (charbuf_obj->buffer == NULL)
		return 0;
	memcpy(charbuf_obj->buffer, buf, count);
	return count;
}

static struct charbuf_attribute buffer_attribute =
	__ATTR(buffer, 0666, buffer_show, buffer_store);


/*
 * bool attributes
 */
static ssize_t b_show(struct charbuf_obj *charbuf_obj, struct charbuf_attribute *attr,
		      char *buf)
{
	if (strcmp(attr->attr.name, "rot13") == 0)
		return sprintf(buf, "%d\n", charbuf_obj->rot13);
	else if (strcmp(attr->attr.name, "reverse") == 0)
		return sprintf(buf, "%d\n", charbuf_obj->reverse);
	return 0;
}

static ssize_t b_store(struct charbuf_obj *charbuf_obj, struct charbuf_attribute *attr,
		       const char *buf, size_t count)
{
	int i, j, var, len;
	sscanf(buf, "%du", &var);
	if (strcmp(attr->attr.name, "clear") == 0)
	{
		kfree(charbuf_obj->buffer);
		charbuf_obj->buffer = kzalloc(1, GFP_KERNEL);
		if (charbuf_obj->buffer == NULL)
			return 1;
	}
	else if (strcmp(attr->attr.name, "rot13") == 0)
	{
		len = strlen(charbuf_obj->buffer) - 1;
		for(i = 0; i < len; i++)
		{
			if(charbuf_obj->buffer[i] >= 'a' && charbuf_obj->buffer[i] <= 'z')
			{
				charbuf_obj->buffer[i] += 13;
				if(charbuf_obj->buffer[i] > 'z')
					charbuf_obj->buffer[i] -= 26;
			}
			else if(charbuf_obj->buffer[i] >= 'A' && charbuf_obj->buffer[i] <= 'Z')
			{
				charbuf_obj->buffer[i] += 13;
				if(charbuf_obj->buffer[i] > 'Z')
					charbuf_obj->buffer[i] -= 26;
			}
		}
	}
	else if (strcmp(attr->attr.name, "reverse") == 0)
	{
		// XXX: this should ignore newlines!
		len = strlen(charbuf_obj->buffer) - 1;
		var = len / 2;
		for(i = 0; i < var; i++)
		{
			j = len - i;
			charbuf_obj->buffer[j] = charbuf_obj->buffer[i] ^ charbuf_obj->buffer[j];
			charbuf_obj->buffer[i] = charbuf_obj->buffer[i] ^ charbuf_obj->buffer[j];
			charbuf_obj->buffer[j] = charbuf_obj->buffer[i] ^ charbuf_obj->buffer[j];
		}
	}
	return count;
}

static struct charbuf_attribute clear_attribute =
	__ATTR(clear, 0666, b_show, b_store);
static struct charbuf_attribute rot13_attribute =
	__ATTR(rot13, 0666, b_show, b_store);
static struct charbuf_attribute reverse_attribute =
	__ATTR(reverse, 0666, b_show, b_store);

/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
static struct attribute *charbuf_default_attrs[] = {
	&buffer_attribute.attr,
	&clear_attribute.attr,
	&rot13_attribute.attr,
	&reverse_attribute.attr,
	NULL, /* need to NULL terminate the list of attributes */
};

static struct kobj_type charbuf_ktype = {
	.sysfs_ops = &charbuf_sysfs_ops,
	.release = charbuf_release,
	.default_attrs = charbuf_default_attrs,
};

static struct kset *charbuf_kset;
static struct charbuf_obj *charbuf_obj;

static struct charbuf_obj *create_charbuf_obj(const char *name)
{
	struct charbuf_obj *charbuf;
	int retval;

	charbuf = kzalloc(sizeof(*charbuf), GFP_KERNEL);
	if (!charbuf)
		return NULL;

	charbuf->kobj.kset = charbuf_kset;

	retval = kobject_init_and_add(&charbuf->kobj, &charbuf_ktype, NULL, "%s", name);
	if (retval)
	{
		kobject_put(&charbuf->kobj);
		return NULL;
	}

	charbuf->buffer = kzalloc(1, GFP_KERNEL);
	if(charbuf->buffer == NULL)
	{
		kobject_put(&charbuf->kobj);
		return NULL;
	}

	kobject_uevent(&charbuf->kobj, KOBJ_ADD);

	return charbuf;
}

static void destroy_charbuf_obj(struct charbuf_obj *charbuf)
{
	kobject_put(&charbuf->kobj);
}

/*
 * module codez
 */
static int __init charbuf_init(void)
{
	charbuf_kset = kset_create_and_add("kset_charbuf", NULL, kernel_kobj);
	if (!charbuf_kset)
		return -ENOMEM;

	charbuf_obj = create_charbuf_obj("charbuf");
	if (!charbuf_obj)
		return -EINVAL;

	return 0;
}

static void __exit charbuf_exit(void)
{
	destroy_charbuf_obj(charbuf_obj);
	kset_unregister(charbuf_kset);
}

module_init(charbuf_init);
module_exit(charbuf_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anthony Cornehl <accornehl@gmail.com>");

