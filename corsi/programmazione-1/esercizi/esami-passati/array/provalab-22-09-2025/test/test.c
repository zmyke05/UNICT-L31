// ----------------------------------------------------------
// #INCLUDE
// ----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------------
// #DEFINE
// ----------------------------------------------------------
#define MAX_LEN 21
#define MAX_RECORD 200

// ----------------------------------------------------------
// STRUCT
// ----------------------------------------------------------
typedef struct
{
    char filename[256];
    int k;
} parameters;

typedef struct
{
    char key[MAX_LEN];
    int length;
} record;

// ----------------------------------------------------------
// PROTOTYPES
// ----------------------------------------------------------
void error(char *msg);
parameters *readInput(int argc, char *argv[]);
void buildArray(record **array, parameters *pars);
void filter(record **array);
void createSet(record **array);
void printArray(record **array, parameters *pars, int mode);
record **allocArray();
void freeArray(record **array);

// ----------------------------------------------------------
// MAIN
// ----------------------------------------------------------
int main(int argc, char *argv[])
{
    parameters *pars = readInput(argc, argv);
    record **array = allocArray();

    buildArray(array, pars);
    filter(array);
    createSet(array);

    printf("Elements with length>=1: \n");
    printArray(array, pars, 0);
    puts("");
    printf("Elements with length>=%d: \n", pars->k);
    printArray(array, pars, 1);

    free(pars);
    freeArray(array);
    return 0;
}

// ----------------------------------------------------------
// FUNCTION
// ----------------------------------------------------------
void error(char *msg)
{
    fprintf(stderr, "[ERROR] %s\n", msg);
    exit(1);
}

parameters *readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        error("The number of parameters must be 3 <program> <file.txt> <k>");
    }

    parameters *pars = malloc(sizeof(parameters));
    if (!pars)
    {
        error("Malloc error");
    }

    strcpy(pars->filename, argv[1]);
    pars->k = atoi(argv[2]);

    if (pars->k < 5 || pars->k > 10)
    {
        error("The value k must be in the range [5, 10]");
    }

    return pars;
}

void buildArray(record **array, parameters *pars)
{
    FILE *fp = fopen(pars->filename, "r");
    if (!fp)
    {
        error("File open error");
    }

    char buffer[MAX_LEN];
    int i = 0;

    while (fscanf(fp, "%20s", buffer) == 1 && i < MAX_RECORD) // restituisce 1 se legge correttamente la stringa, EOF a fine file
    {
        strcpy(array[i]->key, buffer);
        array[i]->length = strlen(buffer);
        i++;
    }
    fclose(fp);
}

void filter(record **array)
{
    char buffer[MAX_LEN];
    for (int i = 0; i < MAX_RECORD && array[i]->length != -1; i++)
    {
        int k = 0;
        for (int j = 0; array[i]->key[j] != '\0'; j++) // questo for scorre la stringa
        {
            char c = array[i]->key[j];
            if (c != ',' && c != ';' && c != ':' && c != '.')
            {
                buffer[k++] = c;
            }
        }
        buffer[k] = '\0';
        strcpy(array[i]->key, buffer);
        array[i]->length = strlen(buffer);
    }
}

void createSet(record **array)
{
    for (int i = 0; i < MAX_RECORD && array[i]->length != -1; i++)
    {
        for (int j = i + 1; j < MAX_RECORD && array[j]->length != -1; j++) // i + 1 perché deve confrontare la stringa[i] con tutte le stringhe successive a i
        {
            if (strcmp(array[i]->key, array[j]->key) == 0) // confronta se le due stringhe sono uguali
            {
                array[j]->length = -1;
            }
        }
    }
}

void printArray(record **array, parameters *pars, int mode)
{
    int count = 1;
    for (int i = 0; i < MAX_RECORD; i++)
    {
        if (array[i]->length > 0)
        {
            if (mode == 0 || array[i]->length >= pars->k)
            {
                printf("printArray(min=%d) [%d] [word: %s] [length: %d]\n", pars->k, count, array[i]->key, array[i]->length);
                count++;
            }
        }
    }
}

record **allocArray()
{
    record **array = malloc(MAX_RECORD * sizeof(record *));
    for (int i = 0; i < MAX_RECORD; i++)
    {
        array[i] = malloc(sizeof(record));
        array[i]->length = -1; // inizializzo la lunghezza a -1 per dire che l'array é vuoto
    }
    return array;
}

void freeArray(record **array)
{
    for (int i = 0; i < MAX_RECORD; i++)
    {
        free(array[i]);
    }
    free(array);
}