#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipi
double *func(int **A, int **B, unsigned int k, unsigned int n);
int **mallocArray(unsigned int a, unsigned int b);
void insertArray(int **A, unsigned int a, unsigned int b);
void outputArray(int **A, unsigned int a, unsigned int b);
void freeArray(int **A, unsigned int a);

int main()
{
    srand(time(0));
    unsigned int k, n;
    int **A, **B;

    puts("");
    do
    {
        printf("Inserisci la dimensione per le matrici A[k][n] - B[n][k] -> k: ");
        scanf("%d", &k);

        printf("Inserisci la dimensione per le matrici A[k][n] - B[n][k] -> n: ");
        scanf("%d", &n);

        if (k > 100 || n > 100)
        {
            printf("Inserisci un valore < 100\n");
        }

    } while (k > 100 || n > 100);
    puts("");

    // Allocazione dinamica A[k][n] e B[n][k]
    A = mallocArray(k, n);
    B = mallocArray(n, k);

    // Inserimento A[k][n] e B[n][k]
    insertArray(A, k, n);
    insertArray(B, n, k);

    // Stampa di A[k][n] e B[n][k]
    printf("Matrice A[n][k]\n");
    outputArray(A, k, n);
    puts("");
    printf("Matrice B[n][k]\n");
    outputArray(B, n, k);

    puts("");
    double *result = func(A, B, k, n);
    if (!result)
    {
        perror("malloc[50]");
        return 1;
    }
    for (unsigned int i = 0; i < k; i++)
    {
        printf("riga %u: %.2f\n", i, result[i]);
    }

    free(result);
    
    // Deallocazione
    freeArray(A, k);
    freeArray(B, n);
}

double *func(int **A, int **B, unsigned int k, unsigned int n)
{
    double *array = calloc(k, sizeof(double));

    for (unsigned int i = 0; i < k; i++)
    {
        double somma = 0;
        int min = min = B[0][i];
        double media = 1;
        for (unsigned int j = 0; j < n; j++)
        {
            if (B[j][i] < min) // MAI METTERE J + 1 perché il ciclo arriva a n-1 quindi poi tenta di accere ad una locazione inesistente
            {
                min = B[j][i];
            }

            somma += A[i][j];
        }
        media = somma / n;
        array[i] = media - min;
    }
    return array;
}

int **mallocArray(unsigned int a, unsigned int b)
{
    int **A = malloc(sizeof(int *) * a);
    if (!A)
    {
        perror("malloc[53]");
    }

    for (unsigned int i = 0; i < a; i++)
    {
        A[i] = malloc(sizeof(int) * b);
        if (!A[i])
        {
            perror("malloc[59]");
        }
    }
    return A;
}

void insertArray(int **A, unsigned int a, unsigned int b)
{
    for (unsigned i = 0; i < a; i++)
    {
        for (unsigned j = 0; j < b; j++)
        {
            *(*(A + i) + j) = rand() % 100 + 1;
        }
    }
}

void outputArray(int **A, unsigned int a, unsigned int b)
{
    for (unsigned int i = 0; i < a; i++)
    {
        for (unsigned int j = 0; j < b; j++)
        {
            printf("\tmatrice[%hd][%hd]: %d", i, j, *(*(A + i) + j));
        }
        printf("\n");
    }
}

void freeArray(int **A, unsigned int a)
{
    for (unsigned int i = 0; i < a; i++)
    {
        free(A[i]);
    }
    free(A);
}