// ============================================================
// Programma di generazione casuale di:
//   - matrice A[n][m] di stringhe
//   - matrice C[k][z] di caratteri
// Versione ottimizzata: poche malloc, memoria contigua,
// PRNG veloce (xorshift), eventuale parallelizzazione OpenMP.
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     // per uint32_t
#include <string.h>
#include <time.h>

#define MAX_LEN 20      // lunghezza massima delle stringhe di A

#ifdef _OPENMP
#include <omp.h>        // se compili con -fopenmp abilita il multithreading
#endif

// ---------------------------------------------------------------------------
// PRNG: xorshift32
// Molto più veloce di rand(), perfetto per generare dati di test.
// Riceve e aggiorna un seed a 32 bit.
// ---------------------------------------------------------------------------
static inline uint32_t xorshift32(uint32_t *s) {
    uint32_t x = *s;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *s = x;
    return x;
}

// ==============================================
// COSA SIGNIFICA E COME FUNZIONA QUESTA FUNZIONE?
// ==============================================
// Static -> funzione privata a questo file
// Inline -> suggerisce al compilatore (se puoi inserisci direttamente il codice qui invece di chiamare la funzione)
// uint32_t -> é un tipo di dato, un numero intero senza segno che occupa 32 bit (é definito in stdint.h)
// xorshift32 -> é il nome della funzione, il 32 indica che lavora con uno stato a 32 bit
// (uint32_t *s) -> qui s é un puntatore, non é il numero é l'indirizzo dove é tenuto il numero (il seed); passiamo l'indirizzo cosí la funzione puó modificare lo stato esterno (aggiornare il seed)
// ---------------------------------------------
// DENTRO LA FUNZIONE
// --------------------------------------------
// uint32_t x = *s -> prende il numero memorizzato dove punta s e lo copia in x, (s é un promemoria che indica una scatola, *s apre la scatola e prende il valore)
// x ^= x << 13 -> x << 13 sposta tutti i bit di x verso sinistra di 13 posizioni (i bit che “escono” spariscono, dall’altro lato entrano zeri).
// ^= -> é l'operazione XOR con assegnazione x = x ^ (x << 13)
// x ^= x >> 17 -> simile, ma >> 17 sposta i bit verso destra di 17 posti (per gli interi non segnati i nuovi bit a sinistra sono 0 — chiamato shift logico).
// x ^= x << 5 -> ancora uno shift a sinistra di 5 e XOR
// *s = x -> scrive il nuovo valore di x nella scatola indicata da s (aggiorna il seme per la prossima chiamata)
// return x -- > restituisce il numero generato

// ==============================================
// COME FA A FUNZIONARE? 
// ==============================================
// L'algoritmo si chiama xorshift (inventato da George Marsaglia). Usa solo spostamenti di bit e XOR, operazioni molto veloci per la CPU, per mescolare i bit del seme e ottenere una seguenza che sembra casuale.
// É rapido e leggero. MAI INIZIARE CON 0, se il seed é zero questo algoritmo ritornerá sempre zero (stato bloccato)
// ==============================================
// TIPI DI ALGORITMI
// ==============================================
// xorshift: perfetto per capire i bit e molto veloce, buon compromesso.
// PCG (Permuted Congruential Generator): qualità statistica eccellente, altrettanto semplice da implementare.
// Mersenne Twister (mt19937): ottimo per simulazioni scientifiche, un po’ più pesante.

int main(void) {
    int n, m, k, z;

    // --- Input sicuro con validazione ---
    puts("");
    printf("---- A[n][m] ----\n");

    // Richiede n e m tra 1 e 100 (ripete finché l'input non è valido)
    do {
        printf("Inserisci la dimensione di A[n][m] -> n (1..100): ");
        if (scanf("%d", &n) != 1) return 1;
        printf("Inserisci la dimensione di A[n][m] -> m (1..100): ");
        if (scanf("%d", &m) != 1) return 1;
    } while (n < 1 || n > 100 || m < 1 || m > 100);

    puts("\n---- C[k][z] ----");
    // Idem per k e z
    do {
        printf("Inserisci la dimensione di C[k][z] -> k (1..100): ");
        if (scanf("%d", &k) != 1) return 1;
        printf("Inserisci la dimensione di C[k][z] -> z (1..100): ");
        if (scanf("%d", &z) != 1) return 1;
    } while (k < 1 || k > 100 || z < 1 || z > 100);

    // ============================================================
    // ALLOCAZIONE OTTIMIZZATA
    // ============================================================
    // Invece di tante malloc piccole (una per ogni stringa),
    // usiamo pochi grandi blocchi contigui:
    //  1) char*** A   : array di puntatori a righe
    //  2) char**  A_ptrs : puntatori alle celle (n*m)
    //  3) char*   A_data : grande blocco con tutte le stringhe
    // Così facciamo solo 3 malloc per A, invece di n*m+… malloc.
    // Stesso approccio per C (una malloc per le righe e una per i dati).
    // ------------------------------------------------------------

    char ***A = malloc((size_t)n * sizeof(char**));
    char **A_ptrs = malloc((size_t)n * m * sizeof(char*));
    char *A_data = malloc((size_t)n * m * (MAX_LEN + 1) * sizeof(char));
    if (!A || !A_ptrs || !A_data) { perror("malloc A"); return 1; }

    // A[i] punta all'inizio della riga i (griglia di puntatori)
    for (int i = 0; i < n; ++i)
        A[i] = A_ptrs + (size_t)i * m;

    // Ogni A[i][j] punta alla giusta posizione nel blocco A_data
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            A[i][j] = A_data + ((size_t)i * m + j) * (MAX_LEN + 1);

    // Stesso schema per C: un array di puntatori alle righe + un blocco dati
    char **C = malloc((size_t)k * sizeof(char*));
    char *C_data = malloc((size_t)k * z * sizeof(char));
    if (!C || !C_data) { perror("malloc C"); return 1; }

    for (int i = 0; i < k; ++i)
        C[i] = C_data + (size_t)i * z;

    // ============================================================
    // INIZIALIZZAZIONE DEI DATI
    // ============================================================
    // base_seed prende un valore variabile dall'orologio di sistema
    uint32_t base_seed = (uint32_t)time(NULL) ^ 0xA5A5A5A5u;

    // ------------------------------
    // Popoliamo A con stringhe casuali
    // Possiamo anche parallelizzare con OpenMP: ogni cella è indipendente.
    // ------------------------------
#ifdef _OPENMP
    #pragma omp parallel for collapse(2)
#endif
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Deriviamo un seed unico per ogni cella
            uint32_t seed = base_seed + (uint32_t)(i * 1315423911u + j * 2654435761u);
            char *s = A[i][j];

            // Lunghezza casuale da 1 a MAX_LEN-1
            int len = 1 + (int)(xorshift32(&seed) % (MAX_LEN - 1));

            // Riempimento della stringa con lettere 'a'..'z'
            for (int x = 0; x < len; ++x)
                s[x] = 'a' + (char)(xorshift32(&seed) % 26);

            s[len] = '\0'; // terminatore C-string
        }
    }

    // ------------------------------
    // Popoliamo C con caratteri casuali
    // Anche qui possiamo parallelizzare
    // ------------------------------
#ifdef _OPENMP
    #pragma omp parallel for collapse(2)
#endif
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < z; ++j) {
            uint32_t seed = base_seed + (uint32_t)(i * 2654435761u + j * 1315423911u);
            C[i][j] = 'a' + (char)(xorshift32(&seed) % 26);
        }
    }

    // ============================================================
    // STAMPA (solo per debug: l'I/O è lento, meglio evitarlo su dati grandi)
    // ============================================================
    printf("\n---- A[n][m] ----");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("\nA[%d][%d]: %s", i, j, A[i][j]);
        puts("");
    }

    // ============================================================
    // DEALLOCAZIONE
    // ============================================================
    // Basta liberare i grandi blocchi nell’ordine inverso.
    free(A_data);
    free(A_ptrs);
    free(A);
    free(C_data);
    free(C);

    puts("");
    return 0;
}
