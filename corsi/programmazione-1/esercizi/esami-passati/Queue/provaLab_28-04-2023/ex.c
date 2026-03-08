// --------------------------------------------
// #INCLUDE
// --------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------
// #DEFINE
// --------------------------------------------
#define MAX_LEN 30

// --------------------------------------------
// STRUCT
// --------------------------------------------
typedef struct
{
    char filename[256];
    char a;
    char b;
} parameters;

typedef struct node
{
    char string[MAX_LEN];
    struct node *next;
} node;

typedef struct
{
    node *head;
    node *tail;
} queue;

// --------------------------------------------
// PROTOTYPES
// --------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void enqueue(queue *q, char *string);
char *deQueue(queue *q);
void buildQueue(queue *q, parameters *pars);
void elab(char *string, parameters *pars);
void printQueue(queue *q, parameters *pars);

// --------------------------------------------
// MAIN
// --------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    queue *q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;

    buildQueue(q, pars);
    printQueue(q, pars);

    free(pars);
    free(q);
    return 0;
}

// --------------------------------------------
// FUNCTION
// --------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        error("The number of parameters must be 4 <program> <file.txt> <a> <b>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->filename, argv[1]);
    pars->a = argv[2][0];
    pars->b = argv[3][0];

    if (pars->a > pars->b)
    {
        error("The character a and b must be a <= b");
    }

    return pars;
}

void enqueue(queue *q, char *string)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strncpy(newNode->string, string, MAX_LEN - 1);
    newNode->string[MAX_LEN - 1] = '\0';
    newNode->next = NULL;

    if (q->tail)
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;

    if (!q->head)
    {
        q->head = newNode;
    }
}

char *deQueue(queue *q)
{
    if (!q->head)
    {
        error("The queue is empty");
    }

    node *buffer = q->head;
    char *string = malloc(MAX_LEN);
    if (!string)
    {
        error("Malloc error");
    }

    strcpy(string, buffer->string);

    q->head = q->head->next;

    if (!q->head)
    {
        q->tail = NULL;
    }

    free(buffer);

    return string;
}

void buildQueue(queue *q, parameters *pars)
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
        enqueue(q, buffer);
    }
    fclose(fp);
}

void elab(char *string, parameters *pars)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] > pars->a && string[i] < pars->b)
        {
            string[i] = '0';
        }
    }
}

void printQueue(queue *q, parameters *pars)
{
    while (q->head)
    {
        char *string = deQueue(q);
        elab(string, pars);
        printf("%s\n", string);
        free(string);
    }
}