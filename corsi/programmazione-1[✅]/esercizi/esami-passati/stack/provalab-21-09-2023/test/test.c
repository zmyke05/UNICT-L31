// ------------------------------------------------------------------
// #INCLUDE <.h>
// ------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// ------------------------------------------------------------------
// #DEFINE
// ------------------------------------------------------------------
#define MAX_LEN 30

// ------------------------------------------------------------------
// STRUCT
// ------------------------------------------------------------------
typedef struct parameters
{
    char filename[MAX_LEN];
    int k;
} parameters;

typedef struct node
{
    char string[MAX_LEN];
    struct node *next;
} node;

// ------------------------------------------------------------------
// PROTOTYPES
// ------------------------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void pushWord(node **top, char *string);
void popWord(node **top);
void buildStack(node **top, parameters *pars);
/* char *sortWord(parameters *pars, char *string); */
void sortWords(char *string);
void printStack(node **top, parameters *pars);

// ------------------------------------------------------------------
// FUNCTION
// ------------------------------------------------------------------
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
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        error("Malloc error");
    }

    strncpy(newNode->string, string, MAX_LEN - 1);
    newNode->string[MAX_LEN - 1] = '\0';

    newNode->next = *top;
    *top = newNode;
}

void popWord(node **top)
{
    if (*top == NULL)
    {
        error("Stack is empty");
    }

    node *buffer = *top;
    *top = buffer->next;
    free(buffer);
}

void buildStack(node **top, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("Open file error");
    }

    char buffer[MAX_LEN];

    while (fgets(buffer, MAX_LEN, fp) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        pushWord(top, buffer);
    }
    fclose(fp);
}

char *sortWord(parameters *pars, char *string)
{
    int len = strlen(string);

    if (len >= pars->k)
    {

        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < len - 1 - i; j++)
            {
                printf("%c > %c\n", string[j], string[j + 1]);
                if (string[j] > string[j + 1])
                {
                    printf("tmp = %c\n", string[j]);
                    char tmp = string[j];
                    printf("string[j] = %c\n", string[j + 1]);
                    string[j] = string[j + 1];
                    printf("string[j + 1] = %c\n", tmp);
                    string[j + 1] = tmp;
                }
            }
            puts("");
        }
    }

    return string;
}

void sortWords(char *string)
{
    int len = strlen(string);

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            printf("%c > %c\n", string[j], string[j + 1]);
            if (tolower(string[j]) > tolower(string[j + 1]))
            {
                printf("tmp = %c\n", string[j]);
                char tmp = string[j];
                printf("string[j] = %c\n", string[j + 1]);
                string[j] = string[j + 1];
                printf("string[j + 1] = %c\n", tmp);
                string[j + 1] = tmp;
            }
        }
        puts("");
    }
}

void printStack(node **top, parameters *pars)
{
    while (*top != NULL)
    {
        char temp[31];
        strcpy(temp, (*top)->string);

        // rimuove il nodo dallo stack
        popWord(top);

        // ordina i caratteri se necessario
        /* sortWord(pars, temp); */

        // stampa la stringa
        printf("%s\n", temp);
    }
}

// ------------------------------------------------------------------
// MAIN
// ------------------------------------------------------------------
int main(int argc, char *argv[])
{
    /* parameters *pars = readInput(argc, argv);
    node *top = NULL; */

    /* buildStack(&top, pars);
    printStack(&top, pars); */
    char string[] = "Mceehil";
    sortWords(string);

    puts("");
    printf("%s\n", string);
    

    /* free(pars); */
    return 0;
}