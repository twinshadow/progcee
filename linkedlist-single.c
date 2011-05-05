#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
 * Node stuff
*********************************************************************/

typedef struct node_s {
  int data;
  struct node_s *next;
} *Node;

/* Calls free() on the node and all attached nodes */
void free_node (Node link) {
  Node shift;

  while (link != NULL) {
    shift = link;
    link = link->next;
    free (shift);
  }
}

/* Allocates a new Node */
Node init_node (int num) {
  Node link;

  link = malloc (sizeof (struct node_s));
  if (link == NULL) exit (1);

  link->data = num;
  link->next = NULL;
  return link;
}

void append_node (Node head, Node link) {
  link->next = head->next;
  head->next = link;
}

void remove_node (Node head) {
  Node link;

  link = head->next;
  head->next = link->next;
  link->next = NULL;
  free_node (link);
}

/*********************************************************************
 * List stuff
*********************************************************************/

typedef struct list_s {
  struct node_s *head;
} *List;

void free_list (List stack) {
  if (stack->head != NULL) free_node (stack->head);
  free (stack);
}

/* Allocates a new List */
List init_list () {
  List stack;

  stack = malloc (sizeof (struct list_s));
  if (stack == NULL) exit (1);

  stack->head = NULL;
  return stack;
}

/* Prepends the List with a new value */
void unshift (List stack, int num) {
  Node link;

  link = init_node (num);
  link->next = stack->head;
  stack->head = link;
}

/* Returns the value from the top of the list */
int shift (List stack) {
  Node link;
  int  num;

  link = stack->head;
  stack->head = link->next;
  num = link->data;

  free_node (link);
  return num;
}

int count_list (List stack) {
  Node link;
  int num;

  num = 0;

  for (link = stack->head; link != NULL; link = link->next) {
    num+=1;
  }

  return num;
}

/* print the values of the List */
void print_list (List stack) {
  Node link;

  printf ("===============================\n");
  for (link = stack->head; link != NULL; link = link->next) {
    printf ("%d\n", link->data);
  }
  printf ("\n");
}

void reverse_list (List stack) {
  Node heap, hold, link;

  link = stack->head;
  heap = NULL;

  while (link != NULL) {
    hold = link;
    link = link->next;
    hold->next = heap;
    heap = hold;
  }

  stack->head = heap;
}

void sort_list (List stack) {
  Node heap, hold, link, sift_prev, sift_link;

  link = stack->head;
  heap = NULL;

  while (link != NULL) {
    hold = link;
    link = link->next;
    sift_link = heap;
    sift_prev = NULL;

    /* 
     * Weirdness abound.
     * Run this if the heap is empty; the first run always runs;
     * If sift_link OR sift_prev are not NULL, it means we're at the TAIL or the HEAD of the stack
     */
    while (heap == NULL || (sift_link != NULL || sift_prev != NULL)) {
      /* 
       * The first part makes sense, big number goes before little number.
       * Second part is laziness. sift_link should only be NULL when...
       * a) The heap is empty
       * b) The end-of-heap is reached
       */
      if (sift_link == NULL || hold->data > sift_link->data) {
        hold->next = sift_link;

        if (sift_prev == NULL) heap = hold;
        else sift_prev->next = hold;
        break;
      }

      sift_prev = sift_link;
      sift_link = sift_link->next;
    }
  }

  stack->head = heap;
}

List init_list_stdin () {
  List stack;
  char string[255];
  int  data;

  stack = init_list();

  while (fgets (string, 254, stdin) != NULL) {
    data = atoi (string);
    if (data != 0) unshift (stack, data);
  }

  return stack;
}

/*********************************************************************
 * Main stuff
*********************************************************************/

int main(void)
{
  List primes;

  primes = init_list_stdin ();

  free_list (primes);
  return 0;
}
