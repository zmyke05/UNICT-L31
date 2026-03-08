// --------------------------------------------------
// #INCLUDE
// --------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------
// #DEFINE
// --------------------------------------------------
#define MAX_LEN 30

// --------------------------------------------------
// STRUCT
// --------------------------------------------------
typedef struct
{
    char filename[256];
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

// --------------------------------------------------
// PROTOTYPES
// --------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void enqueueWord(queue *q, char *string);
char *dequeueWord(queue *q);
void buildqueue(queue *q, parameters *pars);
char **buildStringArray(queue *q, int *count);
void printQueue(queue *q);

// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    queue *q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;

    buildqueue(q, pars);

    int count;
    char **array = buildStringArray(q, &count);
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", array[i]);
    }

    free(q);
    return 0;
}

// --------------------------------------------------
// FUNCTION
// --------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 2)
    {
        error("The number of parameters must be 2 <program> <file.txt>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->filename, argv[1]);

    return pars;
}

void enqueueWord(queue *q, char *string)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strcpy(newNode->string, string);
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

char *dequeueWord(queue *q)
{
    if (!q->head)
    {
        error("The queue is empty");
    }

    node *buffer = q->head;
    q->head = buffer->next;

    char *string = malloc(MAX_LEN);
    if (!string)
    {
        error("Malloc error");
    }

    if (q->head == NULL)
        q->tail = NULL;
    
    strcpy(string, buffer->string);
    free(buffer);
    return string;
}

void buildqueue(queue *q, parameters *pars)
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
        enqueueWord(q, buffer);
    }
    fclose(fp);
}

char **buildStringArray(queue *q, int *size)
{
    int count = 0;
    node *cur = q->head;
    while (cur)
    {
        count++;
        cur = cur->next;
    }

    *size = count;

    char **array = malloc(sizeof(char *) * count);
    for (int i = 0; i < count; i++)
    {
        char *string = dequeueWord(q);
        /* strcpy(array[i], string); */
        array[i] = string;
    }
    return array;
}