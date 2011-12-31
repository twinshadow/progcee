#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
        int data;
        struct node_s next;
} *Node;

/************************************************/

Node new_node (NULL)
{
        Node node = NULL;
        node = malloc(sizeof(struct node_s));
        if (node == NULL)
                exit ENOMEM;
        return node;
}

void free_list (Node head)
{
        Node node = head;
        Node next = NULL;
        while (node != NULL)
        {
                node = node->next;
                free
}

int count_list (Node head)
{
        Node node = head;
        int count = 0;
        while (node != NULL)
        {
                count += 1;
                node = node->next;
        }
        return count;
}


