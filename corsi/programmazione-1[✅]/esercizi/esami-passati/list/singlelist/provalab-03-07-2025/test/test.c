/*
Nome: [TUO NOME]
Cognome: [TUO COGNOME]
Matricola: [TUO NUMERO DI MATRICOLA]
Università di Catania
Dipartimento di Matematica e Informatica
Corso di Studio in Informatica, A.A. 2024-2025
Prova di Laboratorio – 3 Luglio 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 30

typedef struct {
    char codiceEvento[MAX_LEN];
    char nomeLuogo[MAX_LEN];
    int capienzaMax;
} Record;

typedef struct node {
    Record data;
    struct node *next;
} Node;

typedef struct {
    char inputFile[MAX_LEN];
    char outputFile[MAX_LEN];
    int k;
} InputParams;

// ---------------------------------
// ReadInput
// ---------------------------------
InputParams ReadInput(int argc, char *argv[]) {
    InputParams params;
    if(argc != 4) {
        fprintf(stderr, "Errore: uso corretto: %s <inputFile> <outputFile> <k>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(strlen(argv[1]) >= MAX_LEN || strlen(argv[2]) >= MAX_LEN) {
        fprintf(stderr, "Errore: nome file troppo lungo.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(params.inputFile, argv[1]);
    strcpy(params.outputFile, argv[2]);
    params.k = atoi(argv[3]);
    return params;
}

// ---------------------------------
// insertRecord in ordine lessicografico
// ---------------------------------
Node* insertRecord(Node *head, Record r) {
    Node *newNode = malloc(sizeof(Node));
    if(!newNode) {
        fprintf(stderr, "Errore allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = r;
    newNode->next = NULL;

    if(head == NULL || strcmp(r.codiceEvento, head->data.codiceEvento) < 0) {
        newNode->next = head;
        return newNode;
    }

    Node *current = head;
    while(current->next != NULL && strcmp(current->next->data.codiceEvento, r.codiceEvento) < 0) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// ---------------------------------
// printList
// ---------------------------------
void printList(Node *head) {
    Node *current = head;
    while(current != NULL) {
        printf("%s %s %d\n", current->data.codiceEvento, current->data.nomeLuogo, current->data.capienzaMax);
        current = current->next;
    }
}

// ---------------------------------
// buildList (da file di testo)
// ---------------------------------
Node* buildList(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        fprintf(stderr, "Errore apertura file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Node *head = NULL;
    Record temp;
    while(fscanf(fp, "%30s %30s %d", temp.codiceEvento, temp.nomeLuogo, &temp.capienzaMax) == 3) {
        head = insertRecord(head, temp);
    }

    fclose(fp);
    return head;
}

// ---------------------------------
// elab: scrive nel file output.txt i record con capienzaMax <= k
// ---------------------------------
void elab(Node *head, const char *outputFile, int k) {
    FILE *fp = fopen(outputFile, "w");
    
    Node *cur = head;
    while (cur != NULL)
    {
        if (cur->data.capienzaMax <= k)
        {
            fprintf(fp, "%s, %s, %d", cur->data.codiceEvento, cur->data.nomeLuogo, cur->data.capienzaMax);
        }
        cur = cur->next;
    }
    fclose(fp);
}

// ---------------------------------
// main
// ---------------------------------
int main(int argc, char *argv[]) {
    InputParams params = ReadInput(argc, argv);

    Node *head = buildList(params.inputFile);

    printf("** PrintList() **\n");
    printList(head);

    elab(head, params.outputFile, params.k);

    Node *current = head;
    while(current != NULL) {
        Node *tmp = current;
        current = current->next;
        free(tmp);
    }

    return 0;
}
