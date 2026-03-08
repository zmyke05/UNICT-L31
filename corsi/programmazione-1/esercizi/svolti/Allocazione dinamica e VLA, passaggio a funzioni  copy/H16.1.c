#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LEN 100

bool func(char ***M, unsigned int n, unsigned int m);

int main()
{
    srand(time(0));
    char ***M; // Per poter avere una matrice di stringhe devo avere un triplo puntator. Perché?
    // Per allocare dinamicamente devo:
    // Allocare le righe, le colonne e la singola stringa
    unsigned int n, m;

    puts("");
    do
    {
        printf("Inserisci la dimensione di M[n][m] -> n: ");
        scanf("%d", &n);

        printf("Inserisci la dimensione di M[n][m] -> m: ");
        scanf("%d", &m);

        if (n > 100 || m > 100)
        {
            printf("\nInserisci un valore < 100");
        }

    } while (n > 100 || m > 100);
    puts("");

    // Allocazione M[n][m]
    M = malloc(sizeof(char **) * n + 1);
    if (!M)
    {
        perror("malloc");
    }
    for (unsigned int i = 0; i < n; i++)
    {
        M[i] = malloc(sizeof(char *) * m + 1);
        if (!M[i])
        {
            perror("malloc");
        }
        for (unsigned int j = 0; j < m; j++)
        {
            M[i][j] = malloc(sizeof(char) * MAX_LEN); // alloco la singola stringa
                if (!M[i][j])
            {
                perror("malloc");
                return 1;
            }
        }
    }

    // Inserimento stringhe
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            printf("matrice[%d][%d]: ", i, j);
            scanf("%s", M[i][j]);

            if (strcmp(M[i][j], "fine") == 0)
            {
                break;
            }
        }
    }
    puts("");

    // Stampa
    printf("M[n][m]\n");
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            printf("\tmatrice[%d][%d]: %s", i, j, M[i][j]);
        }
        printf("\n");
    }

    // Deallocazione
    for (unsigned int i = 0; i < n; i++)
    {
        free(M[i]);
    }
    free(M);
}

bool func(char ***M, unsigned int n, unsigned int m)
{
    char c;
    for ( unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
             for (int k = 0; M[j][k] != '\0'; k++) 
        }
        
    }
    
}