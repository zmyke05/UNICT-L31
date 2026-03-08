// --------------------------------------------------
// #INCLUDE
// --------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------
// #DEFINE
// --------------------------------------------------
#define MAX_LEN 200

// --------------------------------------------------
// STRUCT
// --------------------------------------------------
typedef struct
{
    char IN[256];
    char OUT[256];
    unsigned n;
    unsigned m;
} parameters;

typedef struct node
{
    int length;
    char string[MAX_LEN];
    struct node *next;
} node;

// --------------------------------------------------
// PROTOTYPES
// --------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
int countWords(char *string);
void push(node **top, char *string, int length);
node *pop(node **top);
void buildStack(node **top, parameters *pars);
void printStack(node *top);
void clearStack(node *top, parameters *pars);

// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *top = NULL;

    buildStack(&top, pars);
    clearStack(top, pars);

    free(pars);
    return 0;
}

// --------------------------------------------------
// FUNCTION
// --------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 5)
    {
        error("The number of parameters must be 5 <program> <input.txt> <output.txt> <n> <m>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->IN, argv[1]);
    strcpy(pars->OUT, argv[2]);

    pars->n = atoi(argv[3]);
    pars->m = atoi(argv[4]);

    if (pars->n > pars->m)
    {
        error("The values n and m must be n < m");
    }

    return pars;
}

int countWords(char *string)
{
    int W = 0;
    int flag = 0;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (flag == 0 && string[i] != ' ')
        {
            W++;
            flag = 1;
        }
        else if (string[i] == ' ')
        {
            flag = 0;
        }
    }
    return W;
}

void push(node **top, char *string, int length)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strncpy(newNode->string, string, MAX_LEN - 1);
    newNode->string[MAX_LEN - 1] = '\0';

    newNode->length = length;

    newNode->next = (*top);
    (*top) = newNode;
}

node *pop(node **top)
{
    if (!(*top))
    {
        error("pop(): The stack is empty");
    }

    node *buffer = (*top);
    (*top) = (*top)->next;
    buffer->next = NULL;

    return buffer;
}

void buildStack(node **top, parameters *pars)
{
    FILE *fp = fopen(pars->IN, "r");
    if (!fp)
    {
        error("Open file error");
    }

    char buffer[MAX_LEN];
    int L, W;

    while (fgets(buffer, MAX_LEN, fp))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        L = strlen(buffer);
        W = countWords(buffer);

        if (W >= pars->n && W <= pars->m)
            push(top, buffer, L);
    }
    fclose(fp);
}

void printStack(node *top)
{
    if (!top)
    {
        error("printStack(): The stack is empty");
    }
    int W = countWords(top->string);
    printf("%d ## %d ## %s\n", top->length, W, top->string);
}

void elabStrVowels(char *string)
{
    char vowels[] = "aeiouAEIOU";

    for (int i = 0; string[i] != '\0'; i++)
    {
        for (int j = 0; vowels[j] != '\0'; j++)
        {
            if (string[i] == vowels[j])
            {
                string[i] = 'X';
            }
        }
    }
}

void clearStack(node *top, parameters *pars)
{
    FILE *fp = fopen(pars->OUT, "w");
    if (!fp)
    {
        error("Cannot write into output file");
    }
    

    node *cur;
    while (top)
    {
        cur = pop(&top);

        printStack(cur);

        elabStrVowels(cur->string);
        
        fprintf(fp, "%s\n", cur->string);

        free(cur);
    }
    fclose(fp);
}