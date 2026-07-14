// =========================================
// Preprocessore
// =========================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DIM 100
#define MAX_LEN_STRING 5

// =========================================
// Prototipi delle funzioni
// =========================================
int inserisci_dimensione(char *nome, int max);
short *func(char ***S, int n, int m, char *C, char *D);

// =========================================
// Inizio main
// =========================================
int main()
{
    puts("");
    srand(time(0));
    // ======================
    // Richiesta dimensione
    // ======================
    int n, m;
    n = inserisci_dimensione("S[n][m] -> n: ", MAX_DIM);
    m = inserisci_dimensione("S[n][m] -> m: ", MAX_DIM);

    // ======================
    // Allocazione dinamica
    // ======================
    // ---------------------
    // S[n][m]
    // ---------------------
    char ***S = malloc((size_t)n * sizeof(char **));
    char **S_ptrs = malloc((size_t)n * m * sizeof(char *));
    char *S_data = malloc((size_t)n * m * (MAX_LEN_STRING + 1) * sizeof(char));

    for (int i = 0; i < n; i++)
    {
        S[i] = &S_ptrs[i * m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            S[i][j] = &S_data[(i * m + j) * (MAX_LEN_STRING + 1)];
        }
    }

    // ---------------------
    // C[n]
    // ---------------------
    char *C = malloc((size_t)(1 + n) * sizeof(char));

    // ---------------------
    // D[n]
    // ---------------------
    char *D = malloc((size_t)(1 + n) * sizeof(char));

    // ======================
    // Inserimento
    // ======================
    // ---------------------
    // S[n][m]
    // ---------------------
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int len = 1 + rand() % (MAX_LEN_STRING - 1);
            for (int k = 0; k < len; k++)
            {
                S[i][j][k] = 'a' + rand() % 26;
            }
            S[i][j][len] = '\0';
        }
    }

    // ---------------------
    // C[n]
    // ---------------------
    for (int i = 0; i < n; i++)
    {
        C[i] = 'a' + rand() % 26;
    }
    C[n] = '\0';

    // ---------------------
    // D[n]
    // ---------------------
    for (int i = 0; i < n; i++)
    {
        D[i] = 'a' + rand() % 26;
    }
    D[n] = '\0';

    // ======================
    // Stampa
    // ======================
    // ---------------------
    // S[n][m]
    // ---------------------
    puts("");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\nS[%d][%d]: %s", i, j, S[i][j]);
        }
        puts("");
    }
    // ---------------------
    // C[n]
    // ---------------------
    puts("");
    for (int i = 0; i < n; i++)
    {
        printf("\nC[%d]: %c", i, C[i]);
    }

    // ---------------------
    // D[n]
    // ---------------------
    puts("");
    for (int i = 0; i < n; i++)
    {
        printf("\nD[%d]: %c", i, C[i]);
    }

    // ======================
    // Obiettivo esercizio
    // ======================
    puts("");
    short *result = func(S, n, m, C, D);
    for (int i = 0; i < n; i++)
    {
        printf("\nresult[%d]: %d", i, result[i]);
    }

    // ======================
    // Deallocazione
    // ======================
    free(S_data);
    free(S_ptrs);
    free(S);
    free(C);
    free(D);

    // ======================
    // Fine programma
    // ======================
    puts("");
    return 0;
}

// =========================================
// Funzioni
// =========================================

// ======================
// Obiettivo esercizio
// ======================
short *func(char ***S, int n, int m, char *C, char *D)
{
    short *result = malloc((size_t)n * sizeof(short));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int len = strlen(S[i][j]);
            if (len > 0)
            {
                char c_inizio = S[i][j][0];
                char c_fine = S[i][j][len - 1];
            }

            for (int l = 0; l < n; l++)
            {
                if (c_inizio == C[i] && c_fine == D[i])
                {
                    result[i] = i;
                }
            }
        }
    }
    return result;
}

// ======================
// Richiesta dimensione
// ======================
int inserisci_dimensione(char *nome, int max)
{
    int v;
    do
    {
        printf("Dimensione di %s", nome);
        if (scanf("%d", &v) != 1)
        {
            while (getchar() != '\n')
            {
                v = max + 1;
            }
        }

    } while (v < 1 || v > max);

    return v;
}