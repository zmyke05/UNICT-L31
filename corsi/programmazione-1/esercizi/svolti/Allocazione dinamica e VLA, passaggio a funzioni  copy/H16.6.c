#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool func(int **M, unsigned int n, unsigned int m, unsigned short k, unsigned short w);

int main()
{
    // inizio programma
    srand(time(NULL));
    unsigned int n, m;
    puts("");
    do
    {
        printf("Inserisci la dimensione della matrice n X m --> n: ");
        scanf("%d", &n);

        printf("Inserisci la dimensione della matrice n X m --> m: ");
        scanf("%d", &m);

        if (n > 100 || m > 100)
        {
            printf("Inserisci un valore < 100");
        }

    } while (n > 100 || m > 100);
    puts("");

    // Allocazione dinamica della matrice n x m
    int **M = malloc(sizeof(int *) * n);
    if (!M)
    {
        perror("malloc -> int **m = malloc(sizeof(int *) * n)");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        *(M + i) = malloc(sizeof(int) * m);
        if (!M[i])
        {
            perror("malloc -> *(m + i) = malloc(sizeof(int) * m)");
            return 1;
        }
    }

    // assegnazioni di valori da 0 a 1000
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            *(*(M + i) + j) = rand() % 50 + 1;
        }
    }

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            printf("\tmatrice[%hd][%hd]: %d", i, j, *(*(M + i) + j));
        }
        printf("\n");
    }
    puts("");

    // controllo colonne
    unsigned short k = 5;
    unsigned short w = 5;

    if (func(M, n, m, k, w))
        printf("OK: ci sono almeno %d colonne con sequenza >= %d\n", w, k);
    else
        printf("NO: non ci sono abbastanza colonne\n");

    // deallocazione della memoria
    for (unsigned int i = 0; i < n; i++)
    {
        free(M[i]);
    }
    free(M);

    // fine programma
    puts("");
    return 0;
}

bool func(int **M, unsigned int n, unsigned int m, unsigned short k, unsigned short w)
{
    int count;
    int colonna_valida = 0;

    for (unsigned int i = 1; i < n; i++)
    {
        count = 1;
        for (unsigned int j = 0; j < m; j++)
        {
            if (M[i][j] > M[i - 1][j])
            {
                count++;
                if (count >= k)
                {
                    colonna_valida++;
                    break;
                }
            }
            else
            {
                count = 1;
            }
        }

        if (colonna_valida >= w)
        {
            return true;
        }
    }
    return false;
}