/*
 * linked-list2
 * An implementation of a doubly-linked list
 *
 * [Structures]
 * Node: int data, Node prev, Node next
 *
 * [Functions]
 * append: Node target, Node link : void
 * init: void : returns Node
 * prepend: Node target, Node link : void
 * walk_next: Node head : void
 * walk_prev: Node tail : void
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
  struct node *prev;
  struct node *next;
  int data;
} *Node;

void append (Node target, Node link) {
  if (NULL != target->next){
    link->next = target->next;
    link->next->prev = link;
  }
  target->next = link;
  link->prev = target;
}

void prepend (Node target, Node link) {
  if (NULL != target->prev) {
    link->prev = target->prev;
    link->prev->next = link;
  }
  target->prev = link;
  link->next = target;
}

Node init (int i) {
  Node link;

  link = malloc (sizeof (struct node));
  if (link == NULL) exit(1);

  link->data = i;
  return link;
}

void walk_next (Node head) {
  Node link;

  for(link = head; link != NULL; link = link->next) {
    printf("%d\n", link->data);
  }
}

void walk_prev (Node tail) {
  Node link;

  for(link = tail; link != NULL; link = link->prev) {
    printf("%d\n", link->data);
  }
}

int main() {
  Node uno,
       dos,
       tres,
       quatro,
       cinque;

  uno =    init(1);
  dos =    init(2);
  tres =   init(3);
  quatro = init(4);
  cinque = init(5);

  append (uno, cinque);
  append (uno, tres);
  prepend (tres, dos);
  prepend (cinque, quatro);

  walk_next(uno);
  walk_prev(cinque);

  free (uno);
  free (dos);
  free (tres);
  free (quatro);
  free (cinque);

  return 0;
}
