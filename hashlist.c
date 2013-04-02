#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 256
#define HASHLIST_MAX 13

struct node {
	int data;
	struct node *next;
	struct node *prev;
};

struct node*
new_node(int data)
{
	struct node *buf;
	buf = calloc(1, sizeof(struct node));
	if (buf == NULL)
		return NULL;
	buf->data = data;
	return buf;
}

void
insert_node(struct node *tar, struct node *buf)
{
	if (buf == NULL || tar == NULL)
		return;

	buf->next = tar;
	if (tar->prev != NULL)
	{
		buf->prev = tar->prev;
		tar->prev->next = tar;
		tar->prev = buf;
	}
}

void
remove_node(struct node *buf)
{
	struct node *tmp;

	if (buf == NULL)
		return;

	tmp = buf;

	if (buf->next != NULL)
	{
		if (buf->prev != NULL)
			buf->prev->next = buf->next;
		else
			buf = buf->next;
	}

	free(tmp);
}

int
main(int argc, char **argv)
{
	int i, hash = -1, target;
	char buf[BUFSIZE];
	struct node **hashlist, *hashnode;

	hashlist = calloc(HASHLIST_MAX, sizeof(NULL));

	while (fgets(buf, BUFSIZE, stdin) != NULL)
	{
		if (buf[0] == '\n')
			continue;

		errno = 0;
		hash = strtol(buf, NULL, 10);
		if (errno)
			continue;

		target = hash % HASHLIST_MAX;
		hashnode = new_node(hash);
		if(hashlist[target] != NULL)
			insert_node(hashlist[target], hashnode);
		hashlist[target] = hashnode;
	}

	for (i = 0; i < HASHLIST_MAX; i++)
	{
		printf(" [% 4d]\t", i);
		hashnode = hashlist[i];
		while (hashnode != NULL)
		{
			printf("%d ", hashnode->data);
			if (hashnode->next == NULL)
				break;
			printf("-> ");
			hashnode = hashnode->next;
		}
		puts("");
	}

	return(EXIT_SUCCESS);
}
