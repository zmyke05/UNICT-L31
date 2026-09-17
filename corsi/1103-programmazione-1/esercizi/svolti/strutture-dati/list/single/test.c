// HEAD --> [Data | Next] --> [Data | Next] --> [Data | Next] --> NULL

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next; 
}node;

void error(char *msg)
{
    fprintf(stderr, "[ERRORE] %s\n", msg);
    exit(1);
}

void list_insert(node **head, int newData)
{
    // Alloco in memoria il nuovo nodo e preparo i suoi campi
    node *newNode = (node*)malloc(sizeof(node));    
    if (!newNode)
    {
        error("Allocazione di memoria fallita.");
    }

    newNode->data = newData;
    newNode->next = (*head);

    // cambio la testa della nodea
    (*head) = newNode;
}

void list_delete(node **head, int key)
{
    node *buffer = *head;
    node *prev = NULL;

    if (buffer != NULL && buffer->data == key)
    {
        *head = buffer->next;
        free(buffer);
        return;
    }


    while (buffer != NULL && buffer->data != key)
    {
        prev = buffer;
        buffer = buffer->next;
    }

    if (buffer == NULL)
    {
        return;
    }

    prev->next = buffer->next;
    free(buffer);
}

void printList(node *p)
{
    printf("\n");

    while (p != NULL)
    {
        printf("|%d| -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}
int main()
{
    node *head = NULL;

    list_insert(&head, 50);
    list_insert(&head, 53);
    list_insert(&head, 58);

    printList(head);
    list_insert(&head, 67);
    printList(head);

    list_delete(&head, 67);
    printList(head);
}