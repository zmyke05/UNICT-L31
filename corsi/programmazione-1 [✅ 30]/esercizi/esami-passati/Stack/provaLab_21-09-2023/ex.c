// --------------------------------------
// #INCLUDE
// --------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------
// #DEFINE
// --------------------------------------
#define MAX_LEN 30

// --------------------------------------
// STRUCT
// --------------------------------------
typedef struct
{
    char filename[256];
    int k;
} parameters;

typedef struct node
{
    char string[MAX_LEN];
    struct node *next;
} node;

// --------------------------------------
// PROTOTYPES
// --------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void pushWord(node **top, char *string);
char *popWord(node **top);
void builStack(node **top, parameters *pars);
void sortWord(parameters *pars, char *string);
void printStack(node *top);

// --------------------------------------
// MAIN
// --------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *top = NULL;
    
    builStack(&top, pars);
    printStack(top);

    free(pars);
    return 0;
}

// --------------------------------------
// FUNCTION
// --------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        error("The number of parameters must be 3 <program> <file.txt> <value>");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strncpy(pars->filename, argv[1], MAX_LEN - 1);
    pars->filename[MAX_LEN - 1] = '\0';

    pars->k = atoi(argv[2]);

    if (pars->k < 5 || pars->k > 15)
    {
        error("The value k must be in the range [5, 15]");
    }

    return pars;
}

void pushWord(node **top, char *string)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strncpy(newNode->string, string, MAX_LEN - 1);
    newNode->string[MAX_LEN - 1] = '\0';

    newNode->next = (*top);
    (*top) = newNode;
}

char *popWord(node **top)
{
    if (!(*top))
    {
        error("The stack is empty");
    }

    node *buffer = (*top);
    (*top) = buffer->next;

    char *string = malloc(MAX_LEN);
    if (!string)
    {
        error("Malloc error");
    }

    strcpy(string, buffer->string);

    free(buffer);
    return string;
}

void builStack(node **top, parameters *pars)
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
        pushWord(top, buffer);
    }
    fclose(fp);
}

void printStack(node *top)
{
    while (top)
    {
        char *string = popWord(&top);

        printf("%s\n", string);

        free(string);
    }
}