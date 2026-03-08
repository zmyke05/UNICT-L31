//-------------------------------------------------
// Nome: [Tuo Nome]
// Cognome: [Tuo Cognome]
// Matricola: [Tua Matricola]
// Università di Catania - Corso di Informatica
// Prova di Laboratorio – 3 dicembre 2024
//-------------------------------------------------

//-------------------------------------------------
// LIBRARY
//-------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------
// DEFINE
//-------------------------------------------------
#define MAXLEN 31

//-------------------------------------------------
// STRUCT
//-------------------------------------------------
typedef struct parameters
{
    char filename[MAXLEN];
    unsigned x;
    unsigned y;
} parameters;

typedef struct
{
    char nome[MAXLEN];
    char cognome[MAXLEN];
    unsigned eta;
}record;

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
void buildList(node **head, parameters *pars, record data);
void printList(node *head);
void removeByAge(node **head, parameters *pars);
void freeList(node *head);

//-------------------------------------------------
// MAIN
//-------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *head = NULL;
    record data;

    buildList(&head, pars, data);

    printf("Lista ordinata completa:\n");
    printList(head);
    printf("\n");

    removeByAge(&head, pars);

    printf("Lista dopo la rimozione dei record con eta' in [%u, %u]:\n", pars->x, pars->y);
    printList(head);

    freeList(head);
    free(pars);
    return 0;
}

//-------------------------------------------------
// FUNCTION
//-------------------------------------------------

// -----------------
// error()
// -----------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

// -----------------
// isEmpty()
// -----------------
int isEmpty(node *head)
{
    return head == NULL;
}

// -----------------
// freeList()
// -----------------
void freeList(node *head)
{
    node *buffer;
    while (head)
    {
        buffer = head;
        head = head->next;
        free(buffer);
    }
}

// -----------------
// readInput()
// -----------------
parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
        error("Uso: <./file> <filename> <x> <y>");

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
        error("Allocazione dinamica errata");

    strcpy(pars->filename, argv[1]);
    pars->x = atoi(argv[2]);
    pars->y = atoi(argv[3]);

    if (pars->x > pars->y || pars->x < 10 || pars->y > 60)
    {
        free(pars);
        error("Valori x e y devono soddisfare 10 <= x <= y <= 60");
    }

    return pars;
}

// -----------------
// insertRecord()
// -----------------
void insertRecord(node **head, record data)
{
    node *newnode = malloc(sizeof(node));
    if (!newnode)
        error("Allocazione dinamica errata");

    newnode->data = data;
    newnode->next = NULL;

    if ((*head) == NULL)
    {
        (*head) = newnode; // lista vuota
        return;
    }

    node *cur = (*head);
    // inserimento in testa se cognome minore
    if (strcmp(data.cognome, cur->data.cognome) < 0)
    {
        newnode->next = (*head);
        (*head) = newnode;
        return;
    }

    // inserimento in mezzo o in coda
    while (cur->next && strcmp(cur->next->data.cognome, data.cognome) < 0)
    {
        cur = cur->next;
    }

    newnode->next = cur->next;
    cur->next = newnode;
}

// -----------------
// buildList()
// -----------------
void buildList(node **head, parameters *pars, record data)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
        error("Impossibile aprire il file");

    while (fscanf(fp, "%30s %30s %u", data.nome, data.cognome, &data.eta) == 3)
    {
        insertRecord(head, data);
    }

    fclose(fp);
}

// -----------------
// printList()
// -----------------
void printList(node *head)
{
    node *cur = head;
    while (cur)
    {
        printf("%s %s %u\n", cur->data.nome, cur->data.cognome, cur->data.eta);
        cur = cur->next;
    }
}

// -----------------
// removeByAge()
// -----------------
void removeByAge(node **head, parameters *pars)
{
    // rimozione testa
    while ((*head) && (*head)->data.eta >= pars->x && (*head)->data.eta <= pars->y)
    {
        node *buffer = (*head);
        (*head) = (*head)->next;
        free(buffer);
    }

    if (!(*head))
        return;

    node *cur = (*head);
    while (cur->next)
    {
        if (cur->next->data.eta >= pars->x && cur->next->data.eta <= pars->y)
        {
            node *buffer = cur->next;
            cur->next = cur->next->next;
            free(buffer);
        }
        else
        {
            cur = cur->next;
        }
    }
}