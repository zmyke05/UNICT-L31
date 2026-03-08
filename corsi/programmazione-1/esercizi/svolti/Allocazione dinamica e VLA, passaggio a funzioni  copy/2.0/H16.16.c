#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int inserisci_dimensione(char *nome, int max);
int func(double **A, int *B, int n, int k);

int main()
{
    puts("");
    srand(time(0));
    const int max = 100;
    int n, k;
    n = inserisci_dimensione("A[n][k] && B[n] -> n: ", max);
    k = inserisci_dimensione("A[n][k] -> k: ", max);

    double **A = malloc((size_t)n * sizeof(double *));
    double *A_data = malloc((size_t)n * k * sizeof(double));

    if (!A || !A_data)
    {
        perror("malloc");
    }

    for (int i = 0; i < n; i++)
    {
        A[i] = A_data + i * k;
    }

    int *B = malloc((size_t)n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A[i][j] = rand() / RAND_MAX * 50;
        }
    }

    for (int i = 0; i < n; i++)
    {

        B[i] = rand() % 50 + 1;
    }

    puts("");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("\tA[%d][%d]: %d", i, j, A[i][j]);
        }
        puts("");
    }

    puts("");
    for (int i = 0; i < n; i++)
    {

        printf("\tB[%d]: %d");
    }

    free(A_data);
    free(A);
    free(B);
    puts("");
    return 0;
}

int func(int **A, int *B, int n, int k)
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
        if (scanf("%d", v) != 1)
        {
            while (getchar() != '\n')
            {
                v = max + 1;
            }
        }

    } while (v < 1 || v > max);
}