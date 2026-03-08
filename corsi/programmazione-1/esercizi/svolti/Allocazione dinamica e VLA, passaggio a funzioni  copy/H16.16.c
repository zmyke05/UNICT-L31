#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int func(double **A, double *B, unsigned int k, unsigned int n);
double **mallocArray(unsigned int a, unsigned int b);
void insertArray(double **A, unsigned int a, unsigned int b);
void outputArray(double **A, unsigned int a, unsigned int b);
void freeArray(double **A, unsigned int a);

int main()
{
    srand(time(0));
    double **A, *B;
    unsigned k, n;

    puts("");
    do
    {
        printf("Inserisci la dimensione A[n][k] - B[n] -> n: ");
        scanf("%d", &n);

        printf("Inserisci la dimensione A[n][k] - B[n] -> k: ");
        scanf("%d", &k);

        if (k > 100 || n > 100)
        {
            printf("Inserisci un valore < 100\n");
        }

    } while (k > 100 || n > 100);
    puts("");

    // Allocazione A[n][k] e B[n]
    A = mallocArray(n, k);
    B = malloc(sizeof(double) * n);
    if (!B)
    {
        perror("malloc[36]");
    }

    // Inserimento A[n][k] e B[n]
    insertArray(A, n, k);
    for (unsigned int i = 0; i < n; i++)
    {
        *(B + i) = ((double)rand() / RAND_MAX) * 1000;
    }

    // Output
    printf("A[n][k]\n");
    outputArray(A, n, k);
    puts("");
    printf("B[n]");
    for (unsigned int i = 0; i < n; i++)
    {
        printf("\narray[%hd]: %.1lf", i, B[i]);
    }
    puts("");

    puts("");
    //result
    int result = func(A, B, k, n);
    printf("Indice: %d", result);

    // Deallocazione
    freeArray(A, n);
    free(B);

    puts("");
}

int func(double **A, double *B, unsigned int k, unsigned int n)
{
    int maxCount = 0;
    int indice = -1; // serve come valore che se nessuna colonna ha un match tornerá -1
    for (unsigned int j = 0; j < k; j++)
    {
        int count = 0;
        for (unsigned int i = 0; i < n; i++)
        {
            if (round(A[i][j]) == round(B[i]))
            {
                count++;
            }
        }

        if (count > maxCount)
        {
            maxCount = count;
            indice = j;
        } 
    }

    return indice;
}

double **mallocArray(unsigned int a, unsigned int b)
{
    double **A = malloc(sizeof(double *) * a);
    if (!A)
    {
        perror("malloc[53]");
    }

    for (unsigned int i = 0; i < a; i++)
    {
        A[i] = malloc(sizeof(double) * b);
        if (!A[i])
        {
            perror("malloc[59]");
        }
    }
    return A;
}

void insertArray(double **A, unsigned int a, unsigned int b)
{
    for (unsigned i = 0; i < a; i++)
    {
        for (unsigned j = 0; j < b; j++)
        {
            *(*(A + i) + j) = ((double)rand() / RAND_MAX) * 1000;
        }
    }
}

void outputArray(double **A, unsigned int a, unsigned int b)
{
    for (unsigned int i = 0; i < a; i++)
    {
        for (unsigned int j = 0; j < b; j++)
        {
            printf("\tmatrice[%hd][%hd]: %.1lf", i, j, *(*(A + i) + j));
        }
        printf("\n");
    }
}

void freeArray(double **A, unsigned int a)
{
    for (unsigned int i = 0; i < a; i++)
    {
        free(A[i]);
    }
    free(A);
}