#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_DIM 100

int inserisci_dimensione(char *nome, int max);
bool func(int **A, int n, int m, short k, short w);

int main()
{
    puts("");
    srand(time(0));
    int n, m;
    //========================
    // Dimensione
    //========================
    n = inserisci_dimensione("A[n][m] -> n: ", MAX_DIM);
    m = inserisci_dimensione("A[n][m] -> m: ", MAX_DIM);

    //========================
    // Allocazione dinamica
    //========================
    int **A = malloc((size_t)n * sizeof(int *));
    int *A_data = malloc((size_t)n * m * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        A[i] = &A_data[i * m];
    }

    //========================
    // Inserimento
    //========================
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            A[i][j] = rand() % 15;
        }
    }

    //========================
    // Stampa
    //========================
    puts("");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\tA[%d][%d]: (%d)", i, j, A[i][j]);
        }
        puts("");
    }

    //========================
    // Obiettivo esercizio
    //========================
    puts("");
    bool result = func(A, n, m, 2, 1);
    if (result)
    {
        printf("Condizione soddisfatta");
    }
    else
    {
        printf("Condizione non soddisfatta");
    }

    //========================
    // Deallocazione
    //========================
    free(A_data);
    free(A);

    puts("");
    return 0;
}

//========================================================================
// FUNZIONI
//========================================================================

//========================
// Obiettivo esercizio
//========================
bool func(int **A, int n, int m, short w, short k)
{
    int match_col = 0;
    for (int j = 0; j < m; j++)
    {
        int count_int = 1;
        int max_len = 1;
        for (int i = 1; i < n; i++)
        {
            if (A[i - 1][j] < A[i][j])
            {
                count_int++;
                if (count_int > max_len)
                {
                    max_len = count_int;
                }
            } else {
                count_int = 1;
            }
        }
        if (count_int > k)
        {
            match_col++;
        }
    }
    if (match_col >= w)
    {
        return true;
    }
    return false;
}

//========================
// Dimensione
//========================
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