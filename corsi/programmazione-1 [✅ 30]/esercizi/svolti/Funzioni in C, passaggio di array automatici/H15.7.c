#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int inserisciArray(int A[], int B[], int n);
int main()
{
    int N;
    int A[500], B[500];
    srand(time(0));

    do
    {
        printf("\nInserisci la dimensione dei due array: ");
        scanf("%d", &N);

        if (N < 0)
        {
            printf("\nInserisci un valore > 0");
        }

    } while (N < 0);

    // Inserimento numeri Casuali
    for (int i = 0; i < N; i++)
    {
        A[i] = rand() % 500 + 1;
        B[i] = rand() % 500 + 1;
    }

    printf("\nStampa: %d", inserisciArray(A, B, N));
    printf("\n");
}

int inserisciArray(int A[], int B[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        double rapporto;
        if (B[i] != 0)
        {
            rapporto = (double)A[i] / B[i];

            if (rapporto < 1)
            {
                int min = 100;
                int max = 200;
                B[i] = A[i];
                A[i] = rand() / RAND_MAX * (max - min) + min;
            }

            if (rapporto > 1)
            {
                A[i] = B[i];
                B[i] = rand() % 100 + 1;
            }

            if (rapporto == 1)
            {
                B[i] = A[i];
                A[i] = 0;
                count++;
            }
        }
    }

    return count;
}