// ------------------------------------------------
// #INCLUDE
// ------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------------
// #DEFINE
// ------------------------------------------------
#define MAX_LEN 31
// ------------------------------------------------
// STRUCT
// ------------------------------------------------
typedef struct
{
    char IN[256];
} parameters;


typedef struct
{
    char codiceEvento[MAX_LEN];
    char nomeLuogo[MAX_LEN];
    int capienzaMax;
} record;


typedef struct node
{
    record data;
    struct node *next;
} node;

// ------------------------------------------------
// PROTOTYPES
// ------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void insertRecord(node **head, record data);
void printList(node *head);
node *buildList(node *head, parameters *pars);
void freeList(node **head);

// ------------------------------------------------
// MAIN
// ------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *head = NULL;
    head = buildList(head, pars);
    printList(head);

    /* printf("%lu\n", sizeof(record)); */
    freeList(&head);
    free(pars);
    return 0;
}

// ------------------------------------------------
// FUNCTION
// ------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 2)
    {
        error("The number of parameters must be 2 <program> <input.bin>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->IN, argv[1]);

    return pars;
}

void insertRecord(node **head, record data)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    newNode->data = data;
    newNode->next = NULL;

    // se la testa non esiste
    if (!(*head))
    {
        (*head) = newNode;
        return;
    }
    
    node *cur = (*head);

    // inserimento in testa
    if (strcmp(data.codiceEvento, cur->data.codiceEvento) < 0)
    {
        newNode->next = (*head);
        (*head) = newNode;
        return;
    }


    // scorro la lista
    while (cur->next && strcmp(data.codiceEvento, cur->next->data.codiceEvento) > 0)
    {
        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;
}

void printList(node *head)
{
    node *cur = head;
    while (cur)
    {
        printf("%s %s %d\n", cur->data.codiceEvento, cur->data.nomeLuogo, cur->data.capienzaMax);
        cur = cur->next;
    }
}

node *buildList(node *head, parameters *pars)
{
    FILE *fp = fopen(pars->IN, "rb");
    if (!fp)
        error("Open file error");

    record data;

    while (fread(&data, sizeof(record), 1, fp) == 1)
    {
        insertRecord(&head, data);
    }
    fclose(fp);
    return head;
}

void freeList(node **head)
{
    while ((*head))
    {
        node *buffer = (*head);
        (*head) = buffer->next;
        free(buffer);
    }
}