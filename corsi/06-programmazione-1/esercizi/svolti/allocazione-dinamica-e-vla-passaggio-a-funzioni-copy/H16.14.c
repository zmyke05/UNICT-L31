#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DIM 100
#define MAX_LEN 30

// =================================
// Prototipi di funzione
// =================================
int leggi_dimensione(char *nome, int max);
short riga_con_piu_match(char ***S, short *B, int n, int m);

int main()
{
    srand(time(NULL));
    int n, m;
    puts("");

    // =================================
    // Input
    // =================================
    n = leggi_dimensione("S[n][m] -> n", MAX_DIM);
    m = leggi_dimensione("S[n][m] -> m", MAX_DIM);

    // =================================
    // Allocazione Dinamica
    // =================================
    // --- A[n][m] ---
    char ***S = malloc((size_t)n * sizeof(char **));                     // array di righe
    char **S_ptrs = malloc((size_t)n * m * sizeof(char *));              // puntatori ad ogni cella
    char *S_data = malloc((size_t)n * m * (MAX_LEN + 1) * sizeof(char)); // unico blocco di dati

    for (int i = 0; i < n; i++)
    {
        S[i] = S_ptrs + i * m;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            S[i][j] = S_data + (i * m + j) * (MAX_LEN + 1);
        }
    }

    // --- B[m] ---
    short *B = malloc((size_t)m * sizeof(short));

    // =================================
    // Inserimento
    // =================================
    // --- A[n][m] ---
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int len = 1 + rand() % (MAX_LEN - 1);
            for (int k = 0; k < len; k++)
            {
                S[i][j][k] = 'a' + rand() % 26;
            }
            S[i][j][len] = '\0';
        }
    }

    // --- B[m] ---
    for (int i = 0; i < m; i++)
    {
        B[i] = rand() % 7 + 1;
    }

    // =================================
    // Stampa
    // =================================
    // --- B[m] ---
    for (int i = 0; i < m; i++)
    {
        printf("\nB[%d]: %d", i, B[i]);
    }

    // --- A[n[m] ---
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\nA[%d][%d]: %s", i, j, S[i][j]);
        }
        puts("");
    }

    // =================================
    // Obiettivo
    // =================================
    puts("");
    short res = riga_con_piu_match(S, B, n, m);
    printf("Riga con più stringhe <= B[j]: %hd\n", res);

    // =================================
    // Deallocazione
    // =================================
    free(S);
    free(S_ptrs);
    free(S_data);
    free(B);
}

// =================================
// Funzioni
// =================================
int leggi_dimensione(char *nome, int max)
{
    int v;
    do
    {
        printf("Inserisci la dimensione di %s (<=%d): ", nome, max);
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

short riga_con_piu_match(char ***S, short *B, int n, int m)
{
    short best_riga = -1;
    int max_match = -1;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < m; j++)
        {
            if ((int)strlen(S[i][j]) <= B[j])
            {
                count++;
            }
            if (count > max_match)
            {
                max_match = count;
                best_riga = (short)i;
            }
        }
    }
    return best_riga;
}