#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_DIM 100

// ========================
// Prototipi delle funzioni
// ========================
int inserisci_dimensione(char *nome, int max);
bool func(int ***A, int n, int k, double w);

int main()
{
    srand(time(0));
    int n, k;
    puts("");
    k = inserisci_dimensione("A[k][n][n] -> k: ", MAX_DIM);
    n = inserisci_dimensione("A[k][n][n] -> n: ", MAX_DIM);

    // ========================
    // Alloazione dinamica
    // ========================
    int ***A = malloc((size_t)k * sizeof(int **));
    int **A_ptrs = malloc((size_t)k * n * sizeof(int *));
    int *A_data = malloc((size_t)k * n * n * sizeof(int));

    for (int i = 0; i < k; i++)
    {
        A[i] = A_ptrs + i * n;
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = A_data + (i * n * n + j * n);
        }
    }

    // ========================
    // Inserimento
    // ========================
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int l = 0; l < n; l++)
            {
                A[i][j][l] = rand() % 10 + 1;
            }
        }
    }

    // ========================
    // Stampa
    // ========================
    puts("");
    for (int i = 0; i < k; i++)
    {
        puts("");
        printf("\tPiano [%d]", i);
        puts("");

        for (int j = 0; j < n; j++)
        {
            for (int l = 0; l < n; l++)
            {
                printf("\tA[%d][%d][%d]: %d", i, j, l, A[i][j][l]);
            }
            puts("");
        }
    }

    // ========================
    // Obiettivo esercizio
    // ========================
    puts("");
    bool result = func(A, n, k, 2.4);
    if (result)
    {
        printf("La condizione é soddisfatta");
    }
    else
    {
        printf("La condizione non é soddisfatta");
    }

    // ========================
    // Deallocazione
    // ========================
    free(A_data);
    free(A_ptrs);
    free(A);

    puts("");
    return 0;
}

// ================================================
// Funzione dimensione
// ================================================
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

// ================================================
// Funzione obiettivo esercizio
// ================================================
bool func(int ***A, int n, int k, double w)
{
    for (int i = 0; i < k; i++)
    {
        int min = A[i][0][0];
        int max = A[i][0][0];
        for (int j = 0; j < n; j++)
        {
            if (A[i][j][j] < min)
            {
                min = A[i][j][j];
            }

            if (A[i][j][j] > max)
            {
                max = A[i][j][j];
            }
        }
        double media = (min + max) / 2.0;
        if (media <= w)
        {
            return true;
        }
    }
    return false;
}