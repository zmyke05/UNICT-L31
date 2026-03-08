#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DIM

// ========================
// Prototipi
// ========================
int inserisci_dim(char *nome, int max);

int main()
{
    int n, k;
    k = inserisci_dim("A[k][n][n] -> k: ", MAX_DIM);
    n = inserisci_dim("A[k][n][n] -> n: ", MAX_DIM);

    
}

// ========================
// Funzioni
// ========================
int inserisci_dim(char *nome, int max)
{
    int v;
    do
    {
        printf("Inserisci la dimensione di %s", nome);
        if (scanf("%d", v) != 1)
        {
            while (getchar() != '\n')
            {
                v = max + 1;
            }
        }

    } while (v < 1 || v > max);
    return v;
}