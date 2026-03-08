#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_DIM 100

int inserisci_dimensione(char *nome, int max);
int func(double **A, int *B, int n, int k);

int main()
{
    puts("");
    srand(time(0));
    int n, k;
    n = inserisci_dimensione("A[n][k] & B[n] -> n: ", MAX_DIM);
    k = inserisci_dimensione("A[n][k] -> K: ", MAX_DIM);

    // ====================
    // Allocazione Dinamica
    // ====================
    double **A = malloc((size_t)n * sizeof(double *));
    double *A_data = malloc((size_t)n * k * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        A[i] = &A_data[i * k];
    }

    int *B = malloc((size_t)n * sizeof(int));

    // ====================
    // Inserimento
    // ====================
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A[i][j] = (double)rand() / RAND_MAX * 10;
        }
    }

    for (int i = 0; i < n; i++)
    {
        B[i] = rand() % 10;
    }

    // ====================
    // Stampa
    // ====================
    puts("");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("\nA[%d][%d]: (%.2lf)", i, j, round(A[i][j]));
        }
        puts("");
    }

    puts("");
    for (int i = 0; i < n; i++)
    {
        printf("\nB[%d]: (%d)", i, B[i]);
    }

    // ====================
    // Obiettivo esercizio
    // ====================
    puts("");
    int result = func(A, B, n, k);
    if (result == -1)
    {
        printf("\nNessuna corrispondenza");
    } else {
        printf("\nMassima corrispondenza nella colonna: [%d]", result);
    }
    

    // ====================
    // Deallocazione
    // ====================
    free(A_data);
    free(A);
    free(B);

    puts("");
    return 0;
}

// ====================
// Funzioni
// ====================
int func(double **A, int *B, int n, int k)
{
    int max = 0;
    int indice = -1;
    for (int j = 0; j < k; j++)
    {
        int match = 0;
        for (int i = 0; i < n; i++)
        {
            if (round(A[i][j]) == B[i])
            {
                match++;
            } 
        }
        if (match > max)
        {
            max = match;
            indice = j;
        }
    }
    return indice;
}

int inserisci_dimensione(char *nome, int max)
{
    int v;
    do
    {
        printf("Dimensione di %s", nome);
        if (scanf("%d", &v) != 1)
        {
            while (getchar() != '\n')
            {
                v = max + 1;
            }
        }

    } while (v < 1 || v > max);

    return v;
}