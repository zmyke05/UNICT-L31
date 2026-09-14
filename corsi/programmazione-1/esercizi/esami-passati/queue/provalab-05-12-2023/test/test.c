// --------------------------------------------------------------------
// #INCLUDE <.h>
// --------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --------------------------------------------------------------------
// #DEFINE
// --------------------------------------------------------------------
#define MAX_LEN 30

// --------------------------------------------------------------------
// STRUCT
// --------------------------------------------------------------------
typedef struct parameters
{
    char filename[MAX_LEN];
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

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------
void error(char *msg);
int isEmpty(queue *q);
parameters *readInput(int argc, char *argv[]);
bool enqueueWord(queue *q, char *string);
char *dequeueWord(queue *q);
void buildQueue(queue *q, parameters *pars);
char **buildStringArray(queue *q, int *size);
void sortArray(char **array, int size);
void printArray(char **array, int size);

// --------------------------------------------------------------------
// FUNCTION
// --------------------------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

int isEmpty(queue *q)
{
    return q->head == NULL;
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 2)
    {
        error("The number of parameters is 3");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc erorr");
    }

    strcpy(pars->filename, argv[1]);

    return pars;
}

void init_queue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

bool enqueueWord(queue *q, char *string)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strncpy(newNode->string, string, MAX_LEN);
    newNode->string[MAX_LEN - 1] = '\0';
    newNode->next = NULL;

    if (isEmpty(q))
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
    }

    return true;
}

char *dequeueWord(queue *q)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    node *buffer = q->head;

    char *result = malloc(MAX_LEN);
    if (!result)
        return NULL;

    strncpy(result, buffer->string, MAX_LEN);
    result[MAX_LEN - 1] = '\0';

    q->head = buffer->next;
    if (q->head == NULL)
        q->tail = NULL;

    free(buffer);
    return result;
}

void buildQueue(queue *q, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("The file doesn't open");
    }

    char buffer[MAX_LEN];

    while (fgets(buffer, MAX_LEN, fp) != NULL)
    {
        // rimuove il newline finale se presente
        buffer[strcspn(buffer, "\n")] = '\0';

        enqueueWord(q, buffer);
    }
    fclose(fp);
}

char **buildStringArray(queue *q, int *size)
{
    // count of element
    int count = 0;
    node *buffer = q->head;

    while (buffer != NULL)
    {
        count++;
        buffer = buffer->next;
    }

    *size = count;

    // allocate the array
    char **array = (char **)malloc(sizeof(char *) * count);
    if (!array)
    {
        error("Malloc error");
    }

    for (int i = 0; i < count; i++)
    {
        array[i] = dequeueWord(q);
    }
    return array;
}

// ------------------
// sortArray()
// ------------------
void sortArray(char **array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (strcmp(array[j], array[j + 1]) > 0) // se array[j] > array[j+1]
            {
                char *buffer = array[j];
                array[j] = array[j + 1];
                array[j + 1] = buffer;
            }
        }
    }
}

void printArray(char **array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%s\n", array[i]);
}

// --------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    queue *q = (queue *)malloc(sizeof(queue));
    if (!q)
    {
        error("Malloc error");
    }
    init_queue(q);

    buildQueue(q, pars);

    int size;
    char **array = buildStringArray(q, &size);

    printArray(array, size);
    puts("");

    sortArray(array, size);

    printf("\nArray ordinato:\n");
    printArray(array, size);

    // libera memoria
    for (int i = 0; i < size; i++)
        free(array[i]);
    free(array);
    free(q);
    free(pars);

    return 0;
}