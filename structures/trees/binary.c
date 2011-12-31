#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
 * Node stuff
*********************************************************************/

typedef struct node_s {
  int data;
  struct node_s *lt;
  struct node_s *gt;
} *Node;

void free_node (Node link) {
  if (link->lt != NULL) {
    free_node (link->lt);
  }

  if (link->gt != NULL) {
    free_node (link->gt);
  }

  data = NULL
  link = NULL
  /*free (link);*/
}

Node init_node (int num) {
  Node branch;

  branch = malloc (sizeof (struct node_s));
  if (NULL == branch) exit (2);

  branch->data = num;
  branch->lt = NULL;
  branch->gt = NULL;

  return branch;
}

void node_insert (Node base, int num) {
  Node branch, append;

  append = NULL;
  branch = init_node (num);

  if (base->data > num) {
    append = base->lt;
    base->lt = branch;
  }
  else {
    append = base->gt;
    base->gt = branch;
  }

  if (branch->data > num) {
    branch->gt = append;
  }
  else {
    branch->lt = append;
  }
}

static int node_lookup (Node base, int target) {
  Node branch;

  branch = base;

  while (branch != NULL) {
    if (target == branch->data) {
      return 1;
    }
    else {
      if (target < branch->data) {
        branch = branch->lt;
        continue;
      }
      else {
        branch = branch->gt;
        continue;
      }
    }
  }

  return 0;
}

void node_print (Node link) {
  printf ("%d ", link->data);
}

void print_inorder (Node link) {
  if (link->lt != NULL) {
    print_inorder (link->lt);
  }

  node_print (link);

  if (link->gt != NULL) {
    print_inorder (link->gt);
  }
}

void print_postorder (Node link) {
  if (link->lt != NULL) {
    print_postorder (link->lt);
  }

  if (link->gt != NULL) {
    print_postorder (link->gt);
  }

  node_print (link);
}

void print_preorder (Node link) {
  node_print (link);

  if (link->lt != NULL) {
    print_preorder (link->lt);
  }

  if (link->gt != NULL) {
    print_preorder (link->gt);
  }
}

/*********************************************************************
 * Tree stuff
*********************************************************************/

typedef struct tree_s {
  struct node_s *root;
} *Tree;

/*  */
void free_tree (Tree stack) {
  if (stack->root != NULL) free_node (stack->root);
  free (stack);
}

/* Make a new tree */
Tree init_tree () {
  Tree stack;

  stack = malloc (sizeof (struct tree_s));
  if (stack == NULL) exit (2);

  stack->root = NULL;

  return stack;
}

/*  */
void tree_insert (Tree stack, int num) {
  if (stack->root == NULL) {
    stack->root = init_node (num);
  }
  else {
    node_insert (stack->root, num);
  }
}

Tree init_tree_stdin () {
  Tree stack;
  char string[255];
  int  data;

  stack = init_tree ();

  while (fgets (string, 255, stdin) != NULL) {
    data = atoi (string);
    if (data != 0) tree_insert (stack, data);
  }

  return stack;
}

void tree_print () {

}

/*********************************************************************
 * Main stuff
*********************************************************************/

int main(void)
{
  Tree primes = init_tree_stdin();
  return 0;
}
