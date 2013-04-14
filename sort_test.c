#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#define UNLESS(X) if (!(X))
#define STREQ(X, Y) (!strcmp(X, Y))
#define SWAP(X, Y, Z)  \
		Z = X; \
		X = Y; \
		Y = Z;

typedef struct list_t {
	int *array;
	int count;
} List;

typedef struct sortfuncs_t {
	char *name;
	void (*sortfun)();
} Sortfuncs;

List*
random_int_list(int count)
{
	List *buf;
	int iter;
	struct timeval time;

	if (count < 1)
		return NULL;

	buf = calloc(1, sizeof(struct list_t));
	if (buf == NULL)
		return NULL;

	buf->array = calloc(count, sizeof(int));
	if (buf->array == NULL)
	{
		free(buf);
		return NULL;
	}

	gettimeofday(&time, NULL);
	srand((unsigned long)time.tv_usec);
	for (iter = 0; iter < count; iter++)
	{
		buf->array[iter] = rand() % 20;
	}

	buf->count = count;

	return buf;
}

void
print_int_list(List *list)
{
	int iter;
	for (iter = 0; iter < list->count; iter++)
	{
		printf("%02d ", list->array[iter]);
	}
	puts("");
}

int
issorted(List *list)
{
	int iter;
	for (iter = 1; iter < list->count; iter++)
		if (list->array[iter] < list->array[iter - 1])
			return 0;
	return 1;
}

/*
   Sort Funcs
*/

void
bubble_sort(List *list)
{
	int iter, sub;
	int swap, swapped;
	for (iter = 0; iter < list->count; iter++)
	{
		swapped = 0;
		for (sub = list->count - 1; sub > iter; sub--)
		{
			if (list->array[sub] < list->array[sub - 1])
			{
				SWAP(list->array[sub],
				     list->array[sub - 1],
				     swap);
				swapped = 1;
			}
		}
		UNLESS (swapped)
			break;
	}
}

void
insert_sort(List *list)
{
	int iter, sub;
	int swap;
	for (iter = 1; iter < list->count; iter++)
		for (sub = iter; sub > 0 && list->array[sub] < list->array[sub - 1]; sub--)
		{
			SWAP(list->array[sub],
			     list->array[sub - 1],
			     swap);
		}
}

void
shell_sort(List *list)
{
	int iter, subiter, gapiter;
	int swap;
	static int gaplist[] = {701, 301, 132, 57, 23, 10, 4, 1};
	int gapnum;

	for (gapiter = 0; gapiter < 8; gapiter++)
	{
		gapnum = gaplist[gapiter];
		for (iter = gapnum; iter < list->count; iter++)
			for (subiter = iter; subiter >= gapnum; subiter -= gapnum)
				if (list->array[subiter] < list->array[subiter - gapnum])
				{
					SWAP(list->array[subiter], list->array[subiter - gapnum], swap);
				}
	}
}

/*
   Main
*/

int
main(int argc, char **argv)
{
	int iter;
	List *testlist;
	Sortfuncs func;
	Sortfuncs funcs[] = {
		{"bubble", bubble_sort},
		{"insert", insert_sort},
		{"shell", shell_sort},
		{NULL, NULL}
	};

	if (argc > 1)
	{
		for (iter = 0; funcs[iter].name != NULL; iter++)
		{
			if (STREQ(argv[1], funcs[iter].name))
			{
				func = funcs[iter];
				break;
			}
		}
	}
	else
		func = funcs[0];


	testlist = random_int_list(9);
	printf("... Performing %s sort on the values.\n", func.name);
	print_int_list(testlist);
	func.sortfun(testlist);
	print_int_list(testlist);
	UNLESS (issorted(testlist))
		puts("FAILED");
	return(EXIT_SUCCESS);
}
