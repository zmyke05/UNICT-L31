// NULL <--> [Prev | Data | Next] <--> [Prev | Data | Next] <--> [Prev | Data | Next] <--> NULL
#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node *next;
    struct node *prev;
}node;

void list_insert(node **head, int data)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode->data = data;
    newNode->next = newNode->prev = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
}

int main()
{

}