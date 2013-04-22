#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#define UNLESS(X) if (!(X))
#define STREQ(X, Y) (!strcmp(X, Y))
#define SWAP(X, Y, Z) { Z = X; \
			X = Y; \
			Y = Z; }

typedef struct sortfuncs_t {
	char *name;
	void (*sortfun)();
} Sortfuncs;

int*
random_int_list(int count)
{
	int *buf;
	int iter;
	struct timeval time;

	if (count < 1)
		return NULL;

	buf = calloc(count, sizeof(int));
	if (buf == NULL)
		return NULL;

	gettimeofday(&time, NULL);
	srand((unsigned long)time.tv_usec);
	for (iter = 0; iter < count; iter++)
	{
		buf[iter] = rand() % 20;
	}

	return buf;
}

void
print_int_list(int count, int *list)
{
	int iter;
	for (iter = 0; iter < count; iter++)
	{
		printf("%02d ", list[iter]);
	}
	puts("");
}

int
issorted(int count, int *list)
{
	int iter;
	for (iter = 1; iter < count; iter++)
		if (list[iter] < list[iter - 1])
			return 0;
	return 1;
}

/*
   Sort Funcs
*/

void
bubble_sort(int count, int *list)
{
	int iter, sub;
	int swap, swapped;
	for (iter = 0; iter < count; iter++)
	{
		swapped = 0;
		for (sub = count - 1; sub > iter; sub--)
		{
			if (list[sub] < list[sub - 1])
			{
				SWAP(list[sub],
				     list[sub - 1],
				     swap);
				swapped = 1;
			}
		}
		UNLESS (swapped)
			break;
	}
}

void
insert_sort(int count, int *list)
{
	int iter, sub;
	int swap;
	for (iter = 1; iter < count; iter++)
		for (sub = iter; sub > 0 && list[sub] < list[sub - 1]; sub--)
			SWAP(list[sub],
			     list[sub - 1],
			     swap);
}

void
shell_sort(int count, int *list)
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
	int *testlist;
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


	int testlen = 10;
	testlist = random_int_list(testlen);
	printf("... Performing %s sort on the values.\n", func.name);
	print_int_list(testlen, testlist);
	func.sortfun(testlen, testlist);
	print_int_list(testlen, testlist);
	UNLESS (issorted(testlen, testlist))
		puts("FAILED");
	return(EXIT_SUCCESS);
}
