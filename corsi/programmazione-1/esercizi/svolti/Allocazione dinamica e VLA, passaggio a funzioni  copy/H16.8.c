// Questo programma é poco efficiente. PRNG (psuedo random number generator) non ottimale. Stampa massiccia
// Riduzione delle malloc
// Puntatori sparsi, ogni stringa é un blocco separato, scorrere le stringhe causa TLB/cache miss 
// TLB(traslation lockside buffer) é una piccola cache speciale che memorizza le trduzioni da indirizzi virtuali a indirizzi fisici.
// Ogni volta che il processore deve accedere a un indirizzo di memoria, guarda nella TLB per vedere se ha già la mappatura pronta. Se manca: TLB miss.
/*Cache miss = dato non trovato nella memoria veloce dei dati.
  TLB miss = traduzione dell’indirizzo non trovata nella mini-cache che fa da dizionario tra indirizzi virtuali e fisici. */
// Se non mi serve necessariamente la stampa é meglio evitare
// nessuna validazione robusta input e messaggi troppo ambigui
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 20

bool func(char ***A, char **C, int n, int m, int k, int z, short w);
int main()
{
    srand(time(0));

    // --- Variabili ---
    int n, m, k, z; // n, m -> dimensioni di A; k, z -> dimensioni di C
    char ***A, **C; // A -> matrice[n][m] di stringhe, C -> matrice[k][z] di caratteri

    // Dimensione A[n][m]
    puts("");
    printf("---- A[n][m] ----\n");
    do
    {
        printf("Inserisci la dimensione di A[n][m] -> n: ");
        scanf("%d", &n);

        printf("Inserisci la dimensione di A[n][m] -> m: ");
        scanf("%d", &m);

        if (n > 100 || m > 100)
        {
            printf("Inserisci un valore < 100");
        }

    } while (n > 100 || m > 100);

    // Dimensione C[k][z]
    puts("");
    printf("---- C[k][z] ----\n");
    do
    {
        printf("Inserisci la dimensione di C[k][z] -> k: ");
        scanf("%d", &k);

        printf("Inserisci la dimensione di C[k][z] -> z: ");
        scanf("%d", &z);

        if (k > 100 || z > 100)
        {
            printf("Inserisci un valore > 100");
        }

    } while (k > 100 || z > 100);

    // --- Allocazione Dinamica ---
    // A[n][m]
    A = malloc(sizeof(*A) * n); // righe
    if (!A)
    {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        A[i] = malloc(sizeof(**A) * m); // colonne
        if (!A[i])
        {
            perror("malloc");
            return 1;
        }
        for (int j = 0; j < m; j++)
        {
            A[i][j] = malloc(sizeof(***A) * (MAX_LEN + 1)); // singola stringa (+1 -> '\0')
            if (!A[i][j])
            {
                perror("malloc");
                return 1;
            }
        }
    }

    // C[k][z]
    C = malloc(sizeof(*C) * k); // righe
    if (!C)
    {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < k; i++)
    {
        C[i] = malloc(sizeof(**C) * z); // colonne
        if (!C[i])
        {
            perror("malloc");
            return 1;
        }
    }

    // --- Inserimento Caratteri/Stringhe pseudo-casuali ---
    // A[n][m]
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int len = 1 + rand() % (MAX_LEN - 1); // lunghezza pseudo-casuale delle stringhe
            for (int x = 0; x < len; x++)
            {
                A[i][j][x] = 'a' + rand() % 26;
            }
            A[i][j][len] = '\0'; // aggiungo il terminatore finita la stringa
        }
    }

    // C[k][z]
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < z; j++)
        {
            C[i][j] = 'a' + rand() % 26;
        }
    }

    // --- Stampa ---
    printf("\n---- A[n][m] ----");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\nA[%d][%d]: %s", i, j, A[i][j]);
        }
        puts("");
    }

    printf("\n---- C[k][z] ----");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < z; j++)
        {
            printf("\nC[%d][%d]: %c", i, j, C[i][j]);
        }
        puts("");
    }

    // --- Obiettivo ---
    puts("");
    bool result = func(A, C, n, m, k, z, 3);
    if(result)
    printf("La condizione é vera");
    else
    printf("La condizione é falsa");

    // --- Deallocazione ---
    // A[n][m]
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);

    // A[n][m]
    for (int i = 0; i < k; i++)
    {
        free(C[i]);
    }
    free(C);

    puts("");
    return 0;
}

bool func(char ***A, char **C, int n, int m, int k, int z, short w)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int start = 0; A[i][j][start + w - 1] != '\0'; start++) // tenta di far partire ogni substyring di lunghezza 'w' nella stringa, fermandosi qwuando l'ultimo carattere del blocco é '\0'
            {
                // copia i w caratteri nella VLA seq (non é terminata da '\0')
                char seq[w];
                for (int t = 0; t < w; t++)
                    seq[t] = A[i][j][start + t];

                // controlla righe di C
                for (int r = 0; r < k; r++)
                    for (int col = 0; col <= z - w; col++)
                    {
                        int match = 1;
                        for (int t = 0; t < w; t++)
                            if (seq[t] != C[r][col + t])
                                match = 0;
                        if (match)
                            return true;
                    }

                // controlla colonne di C
                for (int c = 0; c < z; c++)
                    for (int row = 0; row <= k - w; row++)
                    {
                        int match = 1;
                        for (int t = 0; t < w; t++)
                            if (seq[t] != C[row + t][c])
                                match = 0;
                        if (match)
                            return true;
                    }
            }
        }
    }
    return false;
}
