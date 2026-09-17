// Criterio FIFO (first in, first out)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct queue
{
    node *tail;
    node *head;
} queue;

int isEmpty(struct queue *q)
{
    return (q->head == NULL);
}

void init_queue(queue *q)
{
    q->tail = NULL;
    q->head = NULL;
}

bool enqueue(queue *q, int value)
{
    // create a new node
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        perror("Malloc Error");
        exit(1);
    }

    
    newNode->value = value;
    newNode->next = NULL;

    // if there is a tail, connect that tail to this new node.
    if (q->tail != NULL)
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;

    // make sure the head makes sense.
    if (q->head == NULL)
    {
        q->head = newNode;
    }

    return true;
}

int dequeue(queue *q)
{
    // check to see if the queue is empty
    if (q->head == NULL)
    {
        perror("The queue is empty");
        exit(1);
    }

    // save the head of the queue
    node *tmp = q->head;
    int result;

    // save the result we're going to return
    result = tmp->value;

    // take it off
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(tmp);
    return result;
}

int main(int argc, char *argv[])
{
    queue *q = malloc(sizeof(queue));

    init_queue(q);

    enqueue(q, 56);
    enqueue(q, 59);
    enqueue(q, 86);
    enqueue(q, 34);

    dequeue(q);

    node *current = q->head;
    while (current != NULL)
    {
        printf("%d\n", current->value);
        current = current->next;
    }
    free(q);
}