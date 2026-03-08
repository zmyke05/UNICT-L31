// -------------------------------------------
// #INCLUDE
// -------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------
// STRUCT
// -------------------------------------------
typedef struct
{
    char filename[256];
} parameters;

typedef struct node
{
    char *string;
    struct node *next;
} node;

// -------------------------------------------
// PROTOTYPES
// -------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void push(node **top, char *string);
void pop(node **top);
void buildStack(node **top, parameters *pars);
void countString(char *s, int *countC, int *countW);
void printStack(node *top);

// -------------------------------------------
// MAIN
// -------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);

    node *stack = NULL;
    char *string = "ciao come stai";
    int c, w;
    countString(string, &c, &w);
    printf("%d %d\n", c, w);

    /* buildStack(&stack, pars);
    printStack(stack); */

    /* while (stack)
        pop(&stack); */

    free(pars);
    return 0;
}

// -------------------------------------------
// FUNCTION
// -------------------------------------------
void countString(char *s, int *countC, int *countW)
{
    *countC = 0;
    *countW = 0;
    int inWord = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        (*countC)++;

        if (s[i] != ' ' && inWord == 0)
        {
            inWord = 1;
            (*countW)++;
        }
        else if (s[i] == ' ')
        {
            inWord = 0;
        }
    }
}

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 2)
        error("Usage: ./programma <file>");

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
        error("malloc");

    strcpy(pars->filename, argv[1]);
    return pars;
}

void push(node **top, char *string)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
        error("malloc");

    strcpy(newNode->string, string);
    newNode->next = *top;
    *top = newNode;
}

void pop(node **top)
{
    if (*top == NULL)
        return;

    node *tmp = *top;
    *top = (*top)->next;
    free(tmp->string);
    free(tmp);
}

void buildStack(node **top, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
        error("fopen");

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp))
    {
        buffer[strcspn(buffer, "\n")] = 0; // rimuove '\n'
        push(top, buffer);
    }

    fclose(fp);
}

void printStack(node *top)
{
    while (top)
    {
        int c, w;
        countString(top->string, &c, &w);
        printf("[caratteri: %d | parole: %d] %s\n", c, w, top->string);
        top = top->next;
    }
}
