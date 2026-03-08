#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 20

bool func(char ***A, int n, int m, char *S);

int main()
{
    srand(time(0));
    int n, m;
    char ***A, **S;

    puts("");
    do
    {
        printf("Inserisci la dimensione di S[n][m] --> n: ");
        scanf("%d", &n);

        printf("Inserisci la dimensione di S[n][m] --> m: ");
        scanf("%d", &m);

    } while (n > 100 || m > 100);

    // Allocazione dinamica
    S = malloc(sizeof(*S) * n);
    if (!S)
    {
        perror("malloc");
    }

    for (int i = 0; i < n; i++)
    {
        S[i] = malloc(sizeof(**S) * (MAX_LEN + 1));
        if (!S[i])
        {
            perror("malloc");
        }
    }

    A = malloc(sizeof(*A) * n);
    if (!A)
    {
        perror("malloc");
    }
    for (int i = 0; i < n; i++)
    {
        A[i] = malloc(sizeof(**A) * m);
        if (!A[i])
        {
            perror("malloc");
        }
        for (int j = 0; j < m; j++)
        {
            A[i][j] = malloc(sizeof(***A) * (MAX_LEN + 1)); // +1 per il terminatore '\0'
            if (!A[i][j])
            {
                perror("malloc");
            }
        }
    }

    // Inserimento
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int len = 1 + rand() % (MAX_LEN - 1);
            for (int k = 0; k < len; k++)
            {
                A[i][j][k] = 'a' + rand() % 26;
            }
            A[i][j][len] = '\0';
        }
    }

    for (int i = 0; i < n; i++)
    {
        int len = 1 + rand() % (MAX_LEN - 1);
        for (int j = 0; j < len; j++)
        {
            S[i][j] = 'a' + rand() % 26;
        }
        S[i][len] = '\0';
    }

    // Stampa
    printf("\nA[n][m]");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\nmatrice[%d][%d]: %s", i, j, A[i][j]);
        }
        puts("");
    }

    printf("\n\nS[n]");
    for (int i = 0; i < n; i++)
    {
        printf("\narray[%d]: %s", i, S[i]);
    }

    // Obiettivo
    bool result = func(A, n, m, S);
    if (result)
    {
        printf("Condizione Soddisfatta");
    }
    else
    {
        printf("Condizione NON Soddisfatta");
    }

    // Deallocazione
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
        free(S[i]);
    }
    free(A);
    free(S);

    puts("");
    return 0;
}

bool func(char ***A, int n, int m, char *S)
{
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (strstr(A[i][j], S) != NULL) // é una funzione che serve a cercare una sottostringa dentro una stringa
            {
                found++;
                if (found >= 2)
                {
                    return true;
                }
            }
        }
    }

    return false;
}