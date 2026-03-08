#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double *func(int **A, int **B, unsigned short n, unsigned short m, unsigned short k);

int main()
{
    int **A, **B;
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

    // Allocazione dinamica di A (n righe X m colonne)
    A = malloc(sizeof(int *) * n);
    if (A == NULL)
    {
        perror("malloc");
        return 1;
    }

    for (unsigned short i = 0; i < n; i++)
    {
        A[i] = malloc(sizeof(int) * m);
        if (A[i] == NULL)
        {
            perror("malloc");
            return 1;
        }
    }

    // Allocazione dinamica di B (k righe X n colonne)
    B = malloc(sizeof(int *) * k);
    if (B == NULL)
    {
        perror("malloc");
        return 1;
    }
    for (unsigned short i = 0; i < k; i++)
    {
        *(B + i) = malloc(sizeof(int) * n);
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
            *(*(A + i) + j) = rand() % 10 + 1;
        }
    }

    // Inserimento valori di B
    for (unsigned short i = 0; i < k; i++)
    {
        for (unsigned short j = 0; j < n; j++)
        {
            *(*(B + i) + j) = rand() % 10 + 1;
        }
    }

    double *C = func(A, B, n, m, k);
    if (C)
    {
        for (int i = 0; i < n; i++)
        {
            printf("C[%d] = %.3f\n", i, C[i]);
        }
        free(C);
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
}

double *func(int **A, int **B, unsigned short n, unsigned short m, unsigned short k)
{
    double prodotto;
    double somma;

    double *C = malloc(sizeof(double) * n);
    // Quando uso mallo per riservare la memoria dinamica possono accadere due cose:
    // Allocazione riuscita --> malloc restituisce l'indirizzo del blocco di memoria appena riservato
    // Allocazione fallita --> se il sistema non riesce a riservare memoria (ad esempio perché la ram é esaurita) mallo restituisce NULL
    if (C == NULL)
    {
        perror("malloc"); // Stampa su stderr (dove vengono scritti i messaggi d'errore) leggibile dal sistema operativo preceduto dalla scritta malloc ex: malloc: Cannot allocate memory
        return NULL;
    }

    for (unsigned short i = 0; i < n; i++)
    {
        somma = 0.0;
        for (unsigned j = 0; j < m; j++)
        {
            somma += A[i][j];
        }

        prodotto = 1.0;
        for (unsigned short r = 0; r < k; r++)
        {
            prodotto  *= B[r][i];
        }

        *(C + i) = somma / prodotto;
    }

    return C;
}