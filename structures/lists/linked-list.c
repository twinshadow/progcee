/*
 * linked-list
 * An implementation of a singly-linked list
 *
 * [Structures]
 * List
 * Node 
 *
 * [Functions]
 * append : Node target, Node link : void
 * init : void : returns Node
 * walk_next : Node head : void
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
  struct node_s *next;
  int data;
} *Node;

Node init (int num) {
  Node link;

  link = malloc (sizeof (struct node_s));
  if (NULL == link) exit (1);

  link->data = num;
  link->next = NULL;

  return link;
}

/********************************************************************
 * Node Functions
********************************************************************/

void insert_after (Node head, int num) {
  Node link;

  link = init (num);
  if (NULL != head->next) link->next = head->next;

  head->next = link;
}

Node unshift (Node head, int num) {
  Node link;

  link = init (num);
  link->next = head;

  return link;
}

void free_node (Node head, int num) {
  Node link, prev;

  link = head;
  prev = NULL;

  while (link != NULL) {
    if (link->data == num) {
      prev->next = link->next;
      free (link);
    }
    prev = link;
    link = link->next;
  }
}

void free_stack (Node head) {
  Node hold, link;

  link = head;

  while (link != NULL) {
    hold = link;
    link = link->next;

    free (hold);
  }
}

Node lookup (Node head, int num) {
  Node link;

  link = head;

  while (link != NULL) {
    if (link->data == num) {
      return link;
    }
    link = link->next;
  }

  return NULL;
}

Node reverse (Node head) {
  Node link, hold, stack;

  link = head;
  stack = NULL;

  while (link != NULL) {
    hold = link;
    link = link->next;
    hold->next = stack;
    stack = link;
  }

  return stack;
}


Node sort2 (Node head) {
  Node hold, link, prev, shift, stack;

  link = head;
  stack = NULL;

  while (link != NULL) {
    link = link->next;
    hold = link;
    prev = NULL;

    for (shift = stack; shift != NULL; shift = shift->next) {
      if (hold->data > shift->data) {
        hold->next = shift;
        prev->next = hold;
        break;
      }

      prev = shift;
    }

    if (shift == NULL) {
      hold->next = NULL;
      prev->next = hold;
    }
  }

  return stack;
}


void sort (Node head) {
  Node comp, jump, link, shift, sorted;

  link = head;
  sorted = NULL;

  while (link != NULL) {
    shift = link;
    link = link->next;

    if (NULL == sorted || shift->data < sorted->data) {
      shift->next = sorted;
      sorted = shift;
      continue;
    }

    for (comp = sorted; NULL != comp; comp = comp->next) {
      jump = comp->next;
      if (shift->data > comp->data && shift->data < jump->data) {
        shift->next = comp->next;
        comp->next = shift;
        break;
      }
    }
  }

  head = sorted;
}

void walk_next (Node head) {
  Node link;

  printf ("========================================\n");
  for (link = head; link != NULL; link = link->next) {
    printf ("%d\n", link->data);
  }
  printf ("\n");
}

/*********************************************************************
 * Main
*********************************************************************/

int main(void) {
  Node primes;

  primes = init(2);

  insert_after (primes, 3);
  insert_after (primes, 5);
  insert_after (primes, 7); 

  walk_next (primes);

  primes = reverse (primes);

  walk_next (primes);

  free_stack (primes);

  return 0;
}
