#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DIM 100

// =======================
// Prototipi funzioni
// =======================
int inserisci_dimensione(char *nome, int max);
double *func(int **A, double **B, int n, int m, int k);

// ==============================================
// Main
// ==============================================
int main()
{
    puts("");
    srand(time(0));
    int n, m, k;
    // =======================
    // Richiesta dimensione
    // =======================
    n = inserisci_dimensione("A[n][m] & B[k][n] -> n: ", MAX_DIM);
    m = inserisci_dimensione("A[n][m] -> m: ", MAX_DIM);
    k = inserisci_dimensione("B[k][n] -> k: ", MAX_DIM);

    // =======================
    // Allocazione dinamica
    // =======================
    int **A = malloc((size_t)n * sizeof(int *));
    int *A_data = malloc((size_t)n * m * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        A[i] = &A_data[i * m];
    }

    double **B = malloc((size_t)k * sizeof(double *));
    double *B_data = malloc((size_t)k * n * sizeof(double));

    for (int i = 0; i < k; i++)
    {
        B[i] = &B_data[i * n];
    }

    // =======================
    // Inserimento
    // =======================
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            A[i][j] = rand() % 20;
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = (double)rand() / RAND_MAX * 20.0;
        }
    }

    // =======================
    // Stampa
    // =======================
    puts("");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\tA[%d][%d]: %d", i, j, A[i][j]);
        }
        puts("");
    }

    puts("");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\tB[%d][%d]: %.2lf", i, j, B[i][j]);
        }
        puts("");
    }

    // =======================
    // Obiettivo esercizio
    // =======================
    puts("");
    double *C = func(A, B, n, m, k);

    for (int i = 0; i < n; i++)
    {
        printf("\nC[%d]: %.2lf", i, C[i]);
    }

    // =======================
    // Deallocazione
    // =======================
    free(A_data);
    free(A);
    free(B_data);
    free(B);
    free(C);

    // =======================
    // Fine programma
    // =======================
    puts("");
    return 0;
}
// ==============================================
// Funzioni
// ==============================================

// =======================
// Obiettivo esercizio
// =======================
double *func(int **A, double **B, int n, int m, int k)
{
    double *C = malloc((size_t)n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        double sommaA = 0;
        double sommaB = 0;
        for (int j = 0; j < m; j++)
        {
            sommaA += A[i][j];
        }

        for (int l = 0; l < k; l++)
        {
            sommaB += B[l][i];
        }

        C[i] = ((sommaA/m) + (sommaB/k)) / 2.0;
    }

    return C;
}

// =======================
// Richiesta dimensione
// =======================
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