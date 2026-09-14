#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *func(int **A, double **B, unsigned short n, unsigned short m, unsigned short k);

int main()
{
    int **A;
    double **B;
    unsigned short n, m, k;

    srand(time(0));

    // Inserimento delle dimensioni
    printf("\nInsersci la dimensioni delle matrici: n != m != k");
    do
    {
        puts("");
        printf("Insersci la dimnesione di n: ");
        scanf("%hd", &n);
        printf("Insersci la dimnesione di m: ");
        scanf("%hd", &m);
        printf("Insersci la dimnesione di k: ");
        scanf("%hd", &k);
        if (n > 100 && m > 100 && k > 100)
        {
            puts("error dimensione > 100");
        }

    } while (n > 100 && m > 100 && k > 100);

    // Allocazione dinamica di A (n righe per m colonne)
    A = malloc(sizeof(int *) * n);
    if (A == NULL)
    {
        perror("malloc");
        return 1;
    }
    for (unsigned short i = 0; i < n; i++)
    // deve essere < n poiché se m > n, il ciloc va oltre l'array A (comportamento indefinito/crash)
    // se m < n alcune righe non verranno allocate (errori se proveró a usarle)
    {
        *(A + i) = malloc(sizeof(int) * m);
        if (A[i] == NULL)
        {
            perror("malloc");
            return 1;
        }
    }

    // Allocazione dinamica di B (k righe per n colonne)
    B = malloc(sizeof(double *) * k);
    if (B == NULL)
    {
        perror("malloc");
        return 1;
    }
    for (unsigned short i = 0; i < k; i++)
    {
        B[i] = malloc(sizeof(double) * n);
        if (B[i] == NULL)
        {
            perror("malloc");
            return 1;
        }
    }

    // Inserimento valori di A
    for (unsigned short i = 0; i < n; i++)
    {
        for (unsigned short j = 0; j < m; j++)
        {
            A[i][j] = rand() % 20 + 1;
        }
    }

    // Inserimento valori di B
    for (unsigned short i = 0; i < k; i++)
    {
        double min = 0.0,  max = 20.0;

        for (unsigned short j = 0; j < n; j++)
        {
            *(*(B + i) + j) = ((double)rand() / RAND_MAX) * (max - min) + min;
        }
    }

    // Stampa A
    puts("");
    for (unsigned short i = 0; i < n; i++)
    {
        for (unsigned short j = 0; j < m; j++)
        {
            printf("\tarray[%hd][%hd]: %d", i, j, A[i][j]);
        }
        puts("");
    }

    // Stampa B
    puts("");
    for (unsigned short i = 0; i < k; i++)
    {
        for (unsigned short j = 0; j < n; j++)
        {
            printf("\tarray[%hd][%hd]: %.2lf", i, j, B[i][j]);
        }
        puts("");
    }

    int *v = func(A, B, n, m, k);
    if (v)
    {
        for (unsigned short i = 0; i < n; i++)
        {
            printf("\nv[%hd]: %d", i, v[i]);
        }
        free(v);
    }

    for (unsigned short i = 0; i < n; i++)
    {
        free(A[i]);
    }
    free(A);

    for (unsigned short i = 0; i < k; i++)
    {
        free(B[i]);
    }
    free(B);

   puts("");
}

int *func(int **A, double **B, unsigned short n, unsigned short m, unsigned short k)
{
    double mediaA, mediaB;
    double sommaA, sommaB;
    int *v = malloc(sizeof(int) * n);
    if (v == NULL)
        return NULL;

    for (unsigned short i = 0; i < n; i++)
        v[i] = 0;

    for (unsigned short i = 0; i < n; i++)
    {
        sommaA = 0.0;
        for (unsigned short j = 0; j < m; j++)
        {
            sommaA += A[i][j];
        }

        sommaB = 0.0;
        for (unsigned short r = 0; r < k; r++)
        {
            sommaB += B[r][i];
        }

        mediaA = sommaA / m;
        mediaB = sommaB / k;

        if ((int)mediaA == (int)mediaB)
        {
            v[i] = (int)mediaA;
        }
    }
    
    return v;
}