#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

LIST_HEAD(listhead, edge_t);

struct vertex_t {
	int data;
	struct listhead head;
};

struct vertex_t*
vertex_new(int data)
{
	struct vertex_t *buf;
	buf = calloc(1, sizeof(struct vertex_t));
	if (buf == NULL)
		return NULL;

	buf->data = data;
	LIST_INIT(&buf->head);
	return buf;
}

struct edge_t {
	struct vertex_t *vertex;
	LIST_ENTRY(edge_t) edges;
};

struct edge_t*
edge_new(struct vertex_t *vertex)
{
	struct edge_t *buf;
	buf = calloc(1, sizeof(struct edge_t));
	if (buf == NULL)
		return buf;

	buf->vertex = vertex;
	return buf;
}

void
print_graph(struct vertex_t *node)
{
	struct edge_t *np;

	printf("%d\n", node->data);
	for (np = node->head.lh_first; np != NULL; np = np->edges.le_next)
	{
		printf("%d\n", np->vertex->data);
	}
	puts("---");
}

void
vertex_connect(struct vertex_t *a, struct vertex_t *b)
{
	struct edge_t *buf;

	buf = edge_new(b);
	LIST_INSERT_HEAD(&a->head, buf, edges);
}

void
vertex_connect_pair(struct vertex_t *a, struct vertex_t *b)
{
	struct edge_t *buf;

	buf = edge_new(b);
	LIST_INSERT_HEAD(&a->head, buf, edges);

	buf = edge_new(a);
	LIST_INSERT_HEAD(&b->head, buf, edges);
}

int
main(int argc, char **argv)
{
	struct vertex_t *a, *b, *c;

	a = vertex_new(1);
	b = vertex_new(2);
	c = vertex_new(3);

	vertex_connect_pair(a, b);
	vertex_connect_pair(a, c);
	vertex_connect(b, c);
	print_graph(a);
	print_graph(b);
	print_graph(c);

	return (EXIT_SUCCESS);
}
