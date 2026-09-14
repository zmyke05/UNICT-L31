#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 20

int leggi_dimensione(const char *nome, int max);

int main()
{
    srand(time(0));
    int n, m, k, z;
    const int max_dim = 100;

    // ==============================
    // Validazione della dimnesione
    // ==============================
    // A[n][m]
    n = leggi_dimensione("A[n][m] -> n", max_dim);
    m = leggi_dimensione("A[n][m] -> m", max_dim);
    // C[k][z]
    k = leggi_dimensione("C[k][z] -> k", max_dim);
    z = leggi_dimensione("C[k][z] -> z", max_dim);

    // ==============================
    // Allocazione dinamica
    // ==============================
    // A[n][m]
    char ***A = (char ***)malloc((size_t)n * sizeof(char **));                   // Array di righe
    char **A_ptrs = (char **)malloc((size_t)n * m * sizeof(char *));             // Puntatori in ogni cella
    char *A_data = (char *)malloc((size_t)n * m * (MAX_LEN + 1) * sizeof(char)); // blocco unico di dati

    for (int i = 0; i < n; i++)
    {
        A[i] = A_ptrs + i * m;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            A[i][j] = A_data + (i * m + j) * (MAX_LEN + 1);
        }
    }
    // C[k][z]
    char **C = (char **)malloc((size_t)k * sizeof(char *));
    char *C_data = (char *)malloc((size_t)k * z * sizeof(char));

    for (int i = 0; i < k; i++)
    {
        C[i] = C_data + (size_t)i * z;
    }

    // ==============================
    // Inserimento
    // ==============================
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int len = 1 + rand() % (MAX_LEN - 1);
            for (int k = 0; k < len; ++k)
            {
                A[i][j][k] = 'a' + rand() % 26;
            }
            A[i][j][len] = '\0'; // fine stringa
        }
    }

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < z; ++j)
        {
            C[i][j] = 'a' + rand() % 26;
        }
    }

    // ==============================
    // Stampa
    // ==============================
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\nA[%d][%d]: %s", i, j, A[i][j]);
        }
        puts("");
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < z; j++)
        {
            printf("\nC[%d][%d]: %c", i, j, C[i][j]);
        }
        puts("");
    }

    free(A);
    free(A_ptrs);
    free(A_data);

    return 0;
}

int leggi_dimensione(const char *nome, int max)
{
    int v;
    do
    {
        printf("Inserisci la dimensione di %s (<=%d): ", nome, max);
        if (scanf("%d", &v) != 1)
        {
            // input non numerico: pulisci e riprova
            while (getchar() != '\n') // serve a ripulire il buffer di input quando l'utente digita qualcosa che non é un numero
            // getchar(): é la funzione piú semplice, legge il prossimo byte disponibile da stdin e lo restituisce come int
            // '\n' é il carattere che indica al compilatore che l'utente ha premuto invio
            {
                v = max + 1;
            }
        }
    } while (v < 1 || v > max);
    return v;
}