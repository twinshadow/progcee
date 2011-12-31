#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
  int data;
  struct node_s *next;
} *Node;

Node malloc_node (int num)
{
  Node node = malloc (sizeof (struct node_s));
  node->data = num;
  node->next = NULL;
  return node;
}

void free_node (Node node)
{
  free (node);
}

/*--------------------------------------------------------------------------*/

int count_stack (Node node)
{
  int i = 0;

  while (node != NULL) {
    i+=1;
    node = node->next;
  }

  return i;
}

void free_stack (Node node)
{
  Node link;

  while (node != NULL) {
    link = node;
    node = node->next;
    free (link);
  }
}

void print_stack (Node node, char *sep)
{
  while (node != NULL) {
    printf ("%d%s", node->data, sep);
    node = node->next;
  }
}

/*--------------------------------------------------------------------------*/

typedef struct list_s{
  int count;
  struct node_s *head;
} *List;

List malloc_list (void)
{
  List list = malloc (sizeof (struct list_s));
  list->head = NULL;
  return list;
}

void free_list (List stack)
{
  if (stack->head != NULL) free_stack (stack->head);
  free_list (stack);
}

void push_list (List stack, int num)
{
  Node link = malloc_node (num);
  link->next = stack->head;
  stack->head = link;
}

int pop_list (List stack)
{
  Node link = stack->head;
  int  num = link->data;
  stack->head = link->next;

  free_node (link);
  return num;
}

