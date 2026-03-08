#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void push(node **top, int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

void pop(node **top)
{
    node *buffer = *top;
    *top = buffer->next;
    free(buffer);
}

void print(node *top)
{
    node *current = top;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}
int main()
{
    node *top = NULL;
    push(&top, 30);
    push(&top, 21);
    push(&top, 43);
    push(&top, 64);
    push(&top, 12);
    push(&top, 23);

    print(top);

    pop(&top);

    print(top);

    free(top);
    return 0;
}