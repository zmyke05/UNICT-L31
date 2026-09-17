/*
 Nome: Mario
 Cognome: Rossi
 Matricola: 123456
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REC 20

/* ===== STRUTTURE ===== */
typedef struct {
    char codice[31];
    char nome[31];
    char cognome[31];
    int eta;
} Record;

typedef struct {
    char inputFile[256];
    char outputFile[256];
} Params;

/* ===== PROTOTIPI ===== */
Params ReadInput(int argc, char *argv[]);
Record *buildArray(const char *filename, int max, int *n);
void printRecord(Record *array, int n);
void sortArray(Record *array, int n);
void elab(const char *filename, Record *array, int n);

/* ===== MAIN ===== */
int main(int argc, char *argv[]) {

    Params p;
    Record *array;
    int n;

    p = ReadInput(argc, argv);

    array = buildArray(p.inputFile, MAX_REC, &n);

    printf("** PrintArray() **\n");
    printRecord(array, n);

    sortArray(array, n);

    printf("\n** PrintArray() (after sorting)**\n");
    printRecord(array, n);

    elab(p.outputFile, array, n);

    free(array);
    return 0;
}

/* ===== FUNZIONI ===== */

Params ReadInput(int argc, char *argv[]) {
    Params p;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <input.bin> <output.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(p.inputFile, argv[1], 255);
    strncpy(p.outputFile, argv[2], 255);

    return p;
}

/* Allocazione dell’array NELL’HEAP */
Record *buildArray(const char *filename, int max, int *n) {

    FILE *fp;
    Record *array;

    array = malloc(max * sizeof(Record));
    if (array == NULL) {
        fprintf(stderr, "Errore allocazione memoria\n");
        exit(EXIT_FAILURE);
    }

    /* record non usati: eta = 0 */
    for (int i = 0; i < max; i++)
        array[i].eta = 0;

    fp = fopen(filename, "rb");
    if (!fp) {
        perror("Errore apertura file binario");
        free(array);
        exit(EXIT_FAILURE);
    }

    *n = 0;
    while (*n < max && fread(&array[*n], sizeof(Record), 1, fp) == 1) {
        (*n)++;
    }

    fclose(fp);
    return array;
}

void printRecord(Record *array, int n) {
    for (int i = 0; i < n; i++) {
        if (array[i].eta > 0) {
            printf("%s %s %s %d\n", array[i].codice,array[i].nome, array[i].cognome, array[i].eta);
        }
    }
}

void sortArray(Record *array, int n) {
    Record key;
    int i, j;

    for (i = 1; i < n; i++) {
        key = array[i];
        j = i - 1;

        while (j >= 0 && strcmp(array[j].cognome, key.cognome) > 0) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void elab(const char *filename, Record *array, int n) {

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Errore apertura file output");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (array[i].eta > 0 &&
           (array[i].codice[0] == 'X' || array[i].codice[0] == 'Z')) {

            fprintf(fp, "%s %s %s %d\n", array[i].codice, array[i].nome, array[i].cognome, array[i].eta);
        }
    }

    fclose(fp);
}
