#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int inserisci_dimensione(char *nome, int max);
int func(double **A, int *B, int n, int k);

int main(int argc)
{
    puts("");
    srand(time(0));
    const int max = 100;
    int n, k;

    // ===========================================
    // Scanf()
    // ===========================================
    n = inserisci_dimensione("A[n][k] -> n: ", max);
    k = inserisci_dimensione("A[n][k] -> n: ", max);

    // ===========================================
    // Malloc()
    // ===========================================
    // --- A[n][k] ---
    double **A = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(sizeof(double) * k);
    }

    // --- B[n] ---
    int *B = (int *)malloc(sizeof(int) * n);

    // ===========================================
    // Rand()
    // ===========================================
    // --- A[n][k] ---
    for (int i = 0; i < n; i++)
    {
        int min = 0.0;
        int max = 50.0;
        for (int j = 0; j < k; j++)
        {
            A[i][j] = ((double)rand() / RAND_MAX) * (max - min) + min;
        }
    }

    // --- B[n] ---
    for (int i = 0; i < n; i++)
    {
        B[i] = rand() % 50 + 1;
    }

    // ===========================================
    // Printf()
    // ===========================================
    puts("");
    // --- A[n][k] ---
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("\tA[%d][%d]: %.2lf", i, j, A[i][j]);
        }
        puts("");
    }

    puts("");
    // --- B[n] ---
    for (int i = 0; i < n; i++)
    {
        printf("\tB[%d]: %d", i, B[i]);
    }

    // ===========================================
    // Free()
    // ===========================================
    // --- A[n][k] ---
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
    }-f
    free(A);
    
    // --- B[n] ---
    free(B);

    puts("");
    return 0;
}

// ===========================================
// Function(){}
// ===========================================
int func(double **A, int *B, int n, int k)
{
    for (int j = 0; j < k; j++)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (A[i][j] == B[i])
            {
                count++;
            }
        }
    }
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
}