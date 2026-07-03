// -----------------------------------------------
// #INCLUDE
// -----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------
// #DEFINE
// -----------------------------------------------
#define MAX_LEN 30

// -----------------------------------------------
// STRUCT
// -----------------------------------------------
typedef struct
{
    char filename[256];
    int k;
} parameters;

typedef struct node
{
    char string[MAX_LEN];
    struct node *next;
    struct node *prev;
} node;

// -----------------------------------------------
// PROTOTYPES
// -----------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void insertWord(node **head, char *string);
void builList(node **head, parameters *pars);
void printList(node *head);
void freeList(node **head);
void elab(node *head, parameters *pars, int *len);

// -----------------------------------------------
// MAIN
// -----------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *head = NULL;
    int len;

    builList(&head, pars);
    elab(head, pars, &len);
    printf("Numero di stringhe aventi lunghezza pari o maggiore di %d: %d\n\n", pars->k, len);
    printList(head);

    free(pars);
    freeList(&head);
    return 0;
}

// -----------------------------------------------
// FUNCTION
// -----------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        error("The number of parameters must be 3 <program> <file.txt> <k>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->filename, argv[1]);
    pars->k = atoi(argv[2]);

    if (pars->k < 7 || pars->k > 13)
    {
        error("The value k must be in the range [7, 13]");
    }

    return pars;
}

void insertWord(node **head, char *string)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strncpy(newNode->string, string, MAX_LEN - 1);
    newNode->string[MAX_LEN - 1] = '\0';
    newNode->next = NULL;
    newNode->prev = NULL;

    // head = NULL;
    if (!(*head))
    {
        (*head) = newNode;
        return;
    }

    node *cur = (*head);

    // inserimento in testa
    if (strcmp(string, cur->string) < 0)
    {
        newNode->next = cur;
        cur->prev = newNode;
        (*head) = newNode;
        return;
    }

    // inserimento in mezzo o in coda
    while (cur->next && strcmp(string, cur->next->string) > 0)
    {
        cur = cur->next;
    }

    newNode->next = cur->next;
    newNode->prev = cur;

    if (cur->next)
    {
        cur->next->prev = newNode;
    }
    cur->next = newNode;
}

void builList(node **head, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("Open file error");
    }

    char buffer[MAX_LEN];

    while (fgets(buffer, MAX_LEN, fp))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertWord(head, buffer);
    }
    fclose(fp);
}

void printList(node *head)
{
    node *cur = head;
    while (cur)
    {
        printf("%s\n", cur->string);
        cur = cur->next;
    }
}

void freeList(node **head)
{
    node *cur = (*head);

    while (cur)
    {
        node *buffer = cur;
        cur = cur->next;
        free(buffer);
    }
}

void elab(node *head, parameters *pars, int *len)
{
    *len = 0;
    while (head)
    {
        if (strlen(head->string) >= pars->k)
        {
            (*len)++;
        }
        head = head->next;
    }
}