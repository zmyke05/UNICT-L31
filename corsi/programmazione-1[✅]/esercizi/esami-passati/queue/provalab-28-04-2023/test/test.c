// --------------------------------------------------------
// #INCLUDE <.h>
// --------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --------------------------------------------------------
// #DEFINE
// --------------------------------------------------------
#define MAX_LEN 30

// --------------------------------------------------------
// STRUCT
// --------------------------------------------------------
typedef struct parameters
{
    char filename[MAX_LEN];
    char a;
    char b;
} parameters;

typedef struct node
{
    char string[MAX_LEN];
    struct node *next;
} node;

typedef struct queue
{
    node *head;
    node *tail;
} queue;

// --------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------
void error(char *msg);
void initQueue(queue *q);
int isEmpty(queue *q);
parameters *readInput(int argc, char *argv[]);
bool enqueue(queue *q, char *string);
char *deQueue(queue *q, char *string);
void buildQueue(queue *q, parameters *pars);
void elab(parameters *parms, char *string);

// --------------------------------------------------------
// FUNCTION
// --------------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

void initQueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

int isEmpty(queue *q)
{
    return q->head == NULL;
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        error("The number of paramaters is 4");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->filename, argv[1]);
    pars->a = argv[2][0];
    pars->b = argv[3][0];

    if (pars->a > pars->b)
    {
        error("Must be a <= b");
    }
    return pars;
}

bool enqueue(queue *q, char *string)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strcpy(newNode->string, string);
    newNode->next = NULL;

    if (q->tail != NULL)
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;

    if (isEmpty(q))
    {
        q->head = newNode;
    }
    return true;
}

char *deQueue(queue *q, char *string)
{
    if (isEmpty(q))
    {
        error("The queue is empty");
    }

    if (string == NULL)
    {
        error("Null buffer passed to deQueue function");
    }

    node *buffer = q->head;

    strcpy(string, buffer->string);

    q->head = q->head->next;

    if (isEmpty(q))
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
        error("File doesn't open");
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        enqueue(q, buffer);
    }
    fclose(fp);
}

void elab(parameters *parms, char *string)
{
    // scorro tutti i caratteri della stringa
    for (int i = 0; string[i] != '\0'; i++)
    {
        // controllo se il carattere é nell'intervallo tra [a, b]
        if (string[i] >= parms->a && string[i] <= parms->b)
        {
            // se il carattere rientra nell'intervallo, lo sostituisco con '0'
            string[i] = '0';
        }
    }
}

void printQueue(queue *q, parameters *pars) {
    char buffer[MAX_LEN];

    while (deQueue(q, buffer)) {
        elab(pars, buffer);
        printf("%s\n", buffer);
    }
}


// --------------------------------------------------------
// MAIN
// --------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    queue *q = (queue *) malloc(sizeof(queue));
    if (!q)
    {
        error("Malloc error");
    }
    initQueue(q);

    buildQueue(q, pars);
    printQueue(q, pars);

    free(pars);
    free(q);
}
