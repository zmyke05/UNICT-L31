#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int inserisciArray(int A[], int B[], int n);

int main(void)
{
    int N;
    int A[500], B[500];
    srand(time(NULL));

    do
    {
        printf("\nInserisci la dimensione dei due array: ");
        scanf("%d", &N);
        if (N <= 0)
            printf("\nInserisci un valore > 0");
    } while (N <= 0);

    for (int i = 0; i < N; i++)
    {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    printf("\nStampa: %d\n", inserisciArray(A, B, N));
    return 0;
}

int inserisciArray(int A[], int B[], int n)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (B[i] == 0)
            continue; // evita divisione per 0

        double rapporto = (double)A[i] / B[i];

        if (rapporto < 1)
        {
            B[i] = A[i];
            A[i] = rand() % (200 - 100 + 1) + 100; // [100,200]
        }
        else if (rapporto > 1)
        {
            A[i] = B[i];
            B[i] = rand() % 100 + 1; // [1,100]
        }
        else // rapporto == 1
        {
            B[i] = A[i];
            B[i] = rand() % 100 + 1;
            A[i] = 0;
            count++;
        }
    }

    return count;
}
