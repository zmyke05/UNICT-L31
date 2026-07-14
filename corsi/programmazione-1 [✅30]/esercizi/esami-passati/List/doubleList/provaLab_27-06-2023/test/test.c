// -----------------------------------------------------
// #INCLUDE <.h>
// -----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------
// #DEFINE
// -----------------------------------------------------
#define MAX_LEN 30

// -----------------------------------------------------
// STRUCT
// -----------------------------------------------------
typedef struct
{
    char filename[MAX_LEN];
    float F;
} parameters;

typedef struct node
{
    char P[MAX_LEN];
    float V;
    struct node *next;
    struct node *prev;
} node;

// -----------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void insertRecord(node **head, float V, const char *string);
void buildList(node **head, parameters *pars);
void printList(node *head);
void freeList(node *head);
void elab(node *head, parameters *pars);

// -----------------------------------------------------
// FUNCTION
// -----------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        error("The number of parameters must be 3 <program> <file.txt> <float>");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strncpy(pars->filename, argv[1], MAX_LEN - 1); // argv avrá esattamente MAX_LEN caratteri senza copiare '\0' il terminatore, Perció senza il - 1, nella riga sottostante perderei l'ultimo carattere della stringa
    pars->filename[MAX_LEN - 1] = '\0';

    pars->F = atof(argv[2]);

    if (pars->F < 1.0 || pars->F > 20.0)
    {
        error("The float number must be in the range [1,0, 20.0]");
    }

    return pars;
}

// Inserisce un node ordinato per parola
void insertRecord(node **head, float V, const char *string)
{
    node *newNode = malloc(sizeof(node));
    if (!newNode)
        error("Malloc error");

    newNode->V = V;
    strncpy(newNode->P, string, MAX_LEN - 1);
    newNode->P[MAX_LEN - 1] = '\0';
    newNode->prev = newNode->next = NULL;

    // Lista vuota
    if (!*head)
    {
        *head = newNode;
        return;
    }

    node *curr = *head;

    // Inserimento in testa
    if (strcmp(string, curr->P) < 0)
    {
        newNode->next = curr;
        curr->prev = newNode;
        *head = newNode;
        return;
    }

    // Trova posizione
    while (curr->next && strcmp(string, curr->next->P) > 0)
        curr = curr->next;

    // Inserimento in mezzo o coda
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next)
        curr->next->prev = newNode;
    curr->next = newNode;
}

// Legge il file e inserisce tutti i node
void buildList(node **head, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
        error("File open error");

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp) != NULL)
    {
        // Leggi numero
        float V = strtof(buffer, NULL);

        // Leggi parola
        if (!fgets(buffer, MAX_LEN, fp))
            break;                            // controllo EOF
        buffer[strcspn(buffer, "\n")] = '\0'; // rimuove newline

        insertRecord(head, V, buffer);
    }

    fclose(fp);
}

// Stampa lista
void printList(node *head)
{
    while (head)
    {
        printf("%s %g\n", head->P, head->V);
        head = head->next;
    }
}

// Conta node con V >= F
void elab(node *head, parameters *pars)
{
    int count = 0;
    while (head)
    {
        if (head->V >= pars->F)
            count++;
        head = head->next;
    }
    printf("Numero di node con V >= %g: %d\n", pars->F, count);
}

// Libera lista
void freeList(node *head)
{
    while (head)
    {
        node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

// -----------------------------------------------------
// MAIN
// -----------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *head = NULL;

    buildList(&head, pars);
    printList(head);
    puts("");
    elab(head, pars);

    freeList(head);
    free(pars);
    return 0;
}