#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* * Studente: Nome Cognome
 * Matricola: 1234567
 */

// 1. Struttura per i parametri (Punto A & 1)
typedef struct
{
    char inputFile[256];
    char outputFile[256];
    int n;
    int m;
}parameters;

// Prototipi delle funzioni
parameters *readInput(int argc, char *argv[]);
double ***allocMatrix(int rows, int cols);
double ***readMatrix(parameters *pars);
void printMatrix(double ***mat, int rows, int cols, const char *label);
double ***transposeMatrix(double ***mat, int n, int m);
void sortColMatrix(double ***mat, int rows, int cols);
void writeMatrix(double ***mat, int rows, int cols, char *filename);
void freeMatrix(double ***mat, int rows, int cols);

int main(int argc, char *argv[])
{
    // A. Leggi parametri
    parameters *pars = readInput(argc, argv);

    // B. Leggi matrice originale (double ***)
    double ***M = readMatrix(pars);

    // C. Produci e stampa la trasposta
    double ***Mt = transposeMatrix(M, pars->n, pars->m);
    printMatrix(Mt, pars->m, pars->n, "** Mt **");

    // D. Ordina le colonne della trasposta e stampa
    sortColMatrix(Mt, pars->m, pars->n);
    printMatrix(Mt, pars->m, pars->n, "** M-sorted **");

    // E. Salva su file
    writeMatrix(Mt, pars->m, pars->n, pars->outputFile);

    // Pulizia
    freeMatrix(M, pars->n, pars->m);
    freeMatrix(Mt, pars->m, pars->n);

    return 0;
}

// --- Implementazione Funzioni ---

parameters *readInput(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Errore argomenti. Uso: %s <input> <n> <m> <output>\n", argv[0]);
        exit(1);
    }

    parameters *pars = malloc(sizeof(parameters));

    strcpy(pars->inputFile, argv[1]);
    pars->n = atoi(argv[2]);
    pars->m = atoi(argv[3]);
    strcpy(pars->outputFile, argv[4]);

    if (pars->n <= 0 || pars->m <= 0)
    {
        fprintf(stderr, "n ed m devono essere positivi.\n");
        exit(1);
    }
    return pars;
}

// 2. Allocazione matrice di puntatori (Punto 2)
double ***allocMatrix(int rows, int cols)
{
    // Allocazione array di righe (puntatori a puntatori di double)
    double ***mat = (double ***)malloc(rows * sizeof(double **));
    for (int i = 0; i < rows; i++)
    {
        // Allocazione array di puntatori a double (le colonne)
        mat[i] = (double **)malloc(cols * sizeof(double *));
        for (int j = 0; j < cols; j++)
        {
            // Allocazione dello spazio per il singolo numero
            mat[i][j] = (double *)malloc(sizeof(double));
        }
    }
    return mat;
}

// 3. Lettura da file (Punto 3)
double ***readMatrix(parameters *pars)
{
    FILE *f = fopen(pars->inputFile, "r");
    if (!f)
    {
        perror("Errore file");
        exit(1);
    }

    double ***mat = allocMatrix(pars->n, pars->m);
    for (int i = 0; i < pars->n; i++)
    {
        for (int j = 0; j < pars->m; j++)
        {
            // Leggiamo il valore e lo salviamo nell'area puntata da mat[i][j]
            if (fscanf(f, "%lf", mat[i][j]) != 1)
            {
                fprintf(stderr, "Errore formato dati\n");
                exit(1);
            }
        }
    }
    fclose(f);

    // Stampa richiesta dal punto 3
    printMatrix(mat, pars->n, pars->m, "** M **");
    return mat;
}

// 4. Stampa matrice (Punto 4)
void printMatrix(double ***mat, int rows, int cols, const char *label)
{
    printf("%s\n", label);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Dereferenziazione per accedere al valore double
            printf("%7.2f ", *mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 5. Trasposizione (Punto 5)
double ***transposeMatrix(double ***mat, int n, int m)
{
    double ***tMat = allocMatrix(m, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Copiamo il valore (non il puntatore, per avere una copia reale)
            *tMat[j][i] = *mat[i][j];
        }
    }
    return tMat;
}

// 6. Insertion Sort sulle colonne (Punto 6)
void sortColMatrix(double ***mat, int rows, int cols)
{
    for (int j = 0; j < cols; j++)
    {
        for (int i = 1; i < rows; i++)
        {
            // Salviamo il puntatore della "cella" corrente
            double *tempPtr = mat[i][j];
            double val = *tempPtr; // Valore da confrontare
            int k = i - 1;

            while (k >= 0 && *mat[k][j] > val)
            {
                // Spostiamo i puntatori
                mat[k + 1][j] = mat[k][j];
                k--;
            }
            mat[k + 1][j] = tempPtr;
        }
    }
}

// 7. Scrittura su file (Punto 7)
void writeMatrix(double ***mat, int rows, int cols, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        exit(1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(f, "%7.2f ", *mat[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

// Funzione per liberare la memoria tripla
void freeMatrix(double ***mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            free(mat[i][j]); // Libera il double
        }
        free(mat[i]); // Libera la riga di puntatori
    }
    free(mat); // Libera l'array di righe
}