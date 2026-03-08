// ---------------------------------------------------
// #INCLUDE <.h>
// ---------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------
// ##DEFINE
// ---------------------------------------------------
#define MAX_LEN 30

// ---------------------------------------------------
// STRUCT
// ---------------------------------------------------
typedef struct parameters
{
    char filename[MAX_LEN];
    int k;
} parameters;

typedef struct node
{
    char string[MAX_LEN];
    struct node *next;
    struct node *prev;
} node;

// ---------------------------------------------------
// PROTOTYPES
// ---------------------------------------------------
void error(char *msg);
int isEmpty(node *head);
parameters *readInput(int argc, char *argv[]);
void insertWord(node **head, char *string);
void buildList(node **head, parameters *pars);
void printList(node *head);
void elab(node *head, int k);

// ---------------------------------------------------
// MAIN
// ---------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    node *head = NULL;

    buildList(&head, pars);
    printList(head);
    elab(head, pars->k);
    

    free(pars);

    return 0;
}

// ---------------------------------------------------
// FUNCTION
// ---------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

int isEmpty(node *head)
{
    return head == NULL;
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        error("The number of parameters is 3");
    }

    parameters *pars = (parameters *)malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strncpy(pars->filename, argv[1], MAX_LEN - 1);
    pars->filename[MAX_LEN - 1] = '\0';

    pars->k = atoi(argv[2]);

    if (pars->k < 7 || pars->k > 13)
    {
        error("The value k must be understood [7, 13]");
    }
    return pars;
}

void insertWord(node **head, char *string)
{
    // Alloco memoria per il nuovo nodo della lista
    node *newNode = malloc(sizeof(node));
    if (!newNode)
        error("Malloc error"); // Se malloc fallisce, termino il programma

    // Copio la stringa nel campo string del nodo
    // Uso strncpy per evitare overflow
    strncpy(newNode->string, string, MAX_LEN - 1);

    // Mi assicuro che la stringa sia terminata con '\0'
    newNode->string[MAX_LEN - 1] = '\0';

    // Inizializzo i puntatori del nuovo nodo
    // Per ora non è collegato a nessuno
    newNode->prev = NULL;
    newNode->next = NULL;

    /* =======================
       CASO 1: LISTA VUOTA
       ======================= */

    // Se la lista è vuota (*head == NULL)
    if (isEmpty(*head)) {

        // Il nuovo nodo diventa il primo (e unico) nodo della lista
        *head = newNode;

        // Non devo fare altro: prev e next sono già NULL
        return;
    }

    // Puntatore di appoggio per scorrere la lista
    node *cur = *head;

    /* =======================
       CASO 2: INSERIMENTO IN TESTA
       ======================= */

    // Confronto la nuova stringa con quella del primo nodo
    // strcmp < 0 significa: newNode->string viene prima in ordine alfabetico
    if (strcmp(string, cur->string) < 0) {

        // Il nuovo nodo punta al vecchio primo nodo
        newNode->next = cur;

        // Il vecchio primo nodo ora ha un predecessore
        cur->prev = newNode;

        // Aggiorno la testa della lista
        *head = newNode;

        return;
    }

    /* =======================
       CASO 3: INSERIMENTO IN MEZZO O IN CODA
       ======================= */

    // Scorro la lista finché:
    // - esiste un nodo successivo
    // - e la nuova stringa è "maggiore" della stringa del nodo successivo
    while (cur->next != NULL && strcmp(string, cur->next->string) > 0) {

        // Avanzo di un nodo
        cur = cur->next;
    }

    /*
       A questo punto:
       - cur è il nodo DOPO il quale devo inserire newNode
       - cur->next può essere:
         - NULL  -> inserimento in coda
         - NON NULL -> inserimento in mezzo
    */

    // Il next del nuovo nodo diventa il nodo successivo a cur
    newNode->next = cur->next;

    // Il prev del nuovo nodo diventa cur
    newNode->prev = cur;

    // Se NON siamo in coda (cioè cur->next esiste)
    if (cur->next != NULL) {

        // Il nodo che prima seguiva cur
        // ora ha come predecessore newNode
        cur->next->prev = newNode;
    }

    // Infine collego cur al nuovo nodo
    cur->next = newNode;
}


void buildList(node **head, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("File open error");
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertWord(head, buffer);
    }
    fclose(fp);
}

void printList(node *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->string);
        head = head->next;
    }
}

void elab(node *head, int k)
{
    int count = 0;

    while (head != NULL) {
        if (strlen(head->string) >= k)
            count++;
        head = head->next;
    }

    printf("Numero di stringhe aventi lunghezza pari o maggiore di %d: %d\n",
           k, count);
}
