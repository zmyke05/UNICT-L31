#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LEN 20

bool func(char ***S, int n, int m, unsigned short k, unsigned short w);

int main()
{
    srand(time(0));
    unsigned int n, m;
    char ***S;
    short w, k;

    puts("");
    do
    {
        printf("Inserisci la dimensione di S[n][m] --> n: ");
        scanf("%d", &n);

        printf("Inserisci la dimensione di S[n][m] --> n: ");
        scanf("%d", &m);

        if (n > 100 || m > 100)
        {
            printf("\nInserisci un valore < 100");
        }

    } while (n > 100 || m > 100);

    // Allocamento dinamico
    S = malloc(sizeof(char **) * (n + 1));
    if (!S)
    {
        perror("malloc");
        return 1;
    }

    for (unsigned int i = 0; i < n; i++)
    {
        S[i] = malloc(sizeof(char *) * (m + 1));
        if (!S[i])
        {
            perror("malloc");
            return 1;
        }
        for (unsigned int j = 0; j < m; j++)
        {
            S[i][j] = malloc(sizeof(char) * (MAX_LEN + 1));
            if (!S[i][j])
            {
                perror("malloc");
                return 1;
            }
        }
    }

    // Inserimento Stringhe
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            int len = 1 + rand() % (MAX_LEN - 1);
            for (unsigned int k = 0; k < len; k++)
            {
                S[i][j][k] = 'a' + rand() % 26;
            }
            S[i][j][len] = '\0';
        }
    }

    // Stampa
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            printf("\nmatrice[%d][%d] : %s", i, j, S[i][j]);
        }
        puts("");
    }


    // ---- Obiettivo ----
    puts("");
    bool result = func(S, n, m, 10, 2);
    if(result)
    {
        printf("Ci sono almeno w stringhe di lunghezza minore di k");
    } else
    {
        printf("Non ci sono almeno w stringhe di lunghezza minore di k");
    }
    

    // Deallocazione
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
            free(S[i][j]);
        free(S[i]);
    }
    free(S);

    puts("");
    return 0;
}

bool func(char ***S, int n, int m, unsigned short k, unsigned short w)
{
    bool riga = false;
    bool colonna = false;

    // --- check righe ---
    for (size_t i = 0; i < n; i++)
    {
        int count = 0;
        for (size_t j = 0; j < m; j++)
        {
            if (strlen(S[i][j]) < k)
            {
                count++;
            }
        }

        if (count >= w)
        {
            bool riga = true;
        }
    }

    // --- check colonne ---
    for (size_t i = 0; i < m; i++)
    {
        int count = 0;
        for (size_t j = 0; j < n; j++)
        {
            if (strlen(S[i][j]) < k)
            {
                count++;
            }
        }

        if (count >= w)
        {
            bool colonna = true;
        }
    }

    return riga && colonna;
}