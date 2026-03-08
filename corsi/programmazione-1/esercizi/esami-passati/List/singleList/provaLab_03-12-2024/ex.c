// ----------------------------------------------------------------------------
// #INCLUDE <.h>
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------------------------------
// #DEFINE
// ----------------------------------------------------------------------------
#define MAX_LEN 30

// ----------------------------------------------------------------------------
// STRUCT
// ----------------------------------------------------------------------------
typedef struct
{
    char filename[256];
    int x;
    int y;
} parameters;

typedef struct
{
    char nome[MAX_LEN];
    char cognome[MAX_LEN];
    int eta;
} record;

typedef struct node
{
    record data;
    struct node *next;
} node;

// ----------------------------------------------------------------------------
// PROTOTYPES
// ----------------------------------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void insertRecord(node **head, record data);
void buildList(node **head, parameters *pars);
void printList(node *head);


// ----------------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *head = NULL;

    buildList(&head, pars);
    printList(head);
    
    free(pars);
    return 0;
}

// ----------------------------------------------------------------------------
// FUNCTION
// ----------------------------------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        error("The number of parameters must be 4 <program> <input.txt> <x> <y>");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error (line 57)");
    }

    strcpy(pars->filename, argv[1]);
    pars->x = atoi(argv[2]);
    pars->y = atoi(argv[3]);

    if (pars->x > pars->y || pars->x < 10 || pars->x > 60 || pars->y < 10 || pars->y > 60)
    {
        error("The values x and y must be x < y in the range [10, 60]");
    }

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

    // se la testa é vuota
    if (!(*head))
    {
        (*head) = newNode;
        return;
    }
    
    node *cur = (*head);
    // inserimento in testa
    if (strcmp(data.cognome, cur->data.cognome) < 0)
    {
        newNode->next = (*head);
        (*head) = newNode;
        return;
    }
    
    // inserimento in mezzo o in coda
    while (cur->next && strcmp(cur->next->data.cognome, data.cognome) < 0)
    {
        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;
}

void buildList(node **head, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("Open file error");
    }

    record data;

    while (fscanf(fp, "%30s %30s %d", data.nome, data.cognome, &data.eta) == 3)
    {
        insertRecord(head, data);
    }
    fclose(fp);
}

void printList(node *head)
{
    while (head)
    {
        printf("%s %s %d\n", head->data.nome, head->data.cognome, head->data.eta);
        head = head->next;
    }
}