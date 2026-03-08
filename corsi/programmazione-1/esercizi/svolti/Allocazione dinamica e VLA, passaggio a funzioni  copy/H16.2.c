#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 20

// una matrice di string S[n][m], una array di caratteri C che contiene per ipotesi elementi distinti

// Prototipo
bool func(char ***S, char *C, float w, unsigned int n, unsigned m);

int main()
{
    srand(time(0));
    char ***S;
    char *C = "abcdeiou";
    unsigned int n, m;
    float soglia = 70.0f; // 70%

    puts("");
    do
    {
        printf("Inserici la dimensione di S[n][m] -> n: ");
        scanf("%d", &n);

        printf("Inserici la dimensione di S[n][m] -> m: ");
        scanf("%d", &m);

        if (n > 100 || m > 100)
        {
            printf("\nInserisci un valore < 100");
        }

    } while (n > 100 || m > 100);

    // Allocazione dinamica
    S = malloc(sizeof(char **) * n); // alloco le righe
    if (!S)
    {
        perror("malloc");
        return 1;
    }
    for (unsigned int i = 0; i < n; i++)
    {
        S[i] = malloc(sizeof(char *) * m); // alloco le colonne
        if (!S[i])
        {
            perror("malloc");
            return 1;
        }
        for (unsigned int j = 0; j < m; j++)
        {
            S[i][j] = malloc(sizeof(char) * MAX_LEN); // alloco la singola stringa
            if (!S[i][j])
            {
                perror("malloc");
                return 1;
            }
        }
    }

    // Inserimento
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
            printf("\nmatrice[%d][%d]: %s", i, j, S[i][j]);
        }
        printf("\n\n");
    }
    puts("");

    bool risultato = func(S, C, soglia, n, m);
    if (risultato)
    {
        printf("La condizione é soddisfatta");
    }
    else
    {
        printf("La condizione non é soddisfatta");
    }

    // Deallocazione dalla memoria
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            free(S[i][j]);
        }
        free(S[i]);
    }
    free(S);

    puts("");
    return 0;
}

bool func(char ***S, char *C, float w, unsigned int n, unsigned m)
{
    // --- check righe ---
    for (unsigned int i = 0; i < n; i++)
    {
        int total = 0, match = 0;
        for (unsigned int j = 0; j < m; j++)
        {
            for (unsigned int k = 0; S[i][j][k] != '\0'; k++)
            {
                total++;
                if (strchr(C, S[i][j][k]))
                    match++;
            }
        }
        if (total > 0 && ((float)match / total) * 100.0f > w)
            return true;
    }

    // --- check colonne ---
    for (unsigned int j = 0; j < m; j++)
    {
        int total = 0, match = 0;
        for (unsigned int i = 0; i < n; i++)
        {
            for (unsigned int k = 0; S[i][j][k] != '\0'; k++)
            {
                total++;
                if (strchr(C, S[i][j][k]))
                    match++;
            }
        }
        if (total > 0 && ((float)match / total) * 100.0f > w)
            return true;
    }

    return false;
}



