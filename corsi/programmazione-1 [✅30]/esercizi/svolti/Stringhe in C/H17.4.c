#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_VERBI 30
#define MAX_LEN 50

int termina_con(const char *parola, const char *suffisso);

int main()
{
    puts("");
    char *verbi[N_VERBI]; // Array di 30 puntatori
    // Ogni cella contiene un puntatore a char, coié l'indirizzo di una stringa in memoria
    // QUINDI non é un "grande blocco di testo unico" é una scato con 20 caselle, e in ogni casella metti l'indirizzo del primo carattere della stringa che voglio memorizzare
    // verbi
    // +-----+-----+-----+-----+ ... +-----+
    // |  *  |  *  |  *  |  *  |     |  *  |   <-- 30 celle
    // +-----+-----+-----+-----+ ... +-----+
    //  |      |      |
    //  v      v      v
    // "andare" "correre" "saltare"
    // Pensa come a 30 foglietti che indicano dov'é scritto il verbo

    char buffer[MAX_LEN]; // é solo unh contenitore temporaneo dove appoggio la parole che l'utente digita prima di copiarla nella memoria definitiva
    // Perché serve?
    // Quando l'utente scrive la parole, non conosco in anticipo la lunghezza, per poter chiamare la funzione malloc() devo sapere quanti byte mi servono
    // il flusso sará quindi -->
    // utente --> buffer temporaneo --> strlen(buffer) --> malloc --> strcpy
    // Leggo nel buffer (scanf("%49s", buffer)), che ha una capienza massima nota (MAX_LEN).
    // Uso strlen(buffer) per calcolare i caratteri reali.
    //  Alloco con malloc(strlen(buffer)+1) lo spazio esatto.
    //  Copio (strcpy) dal buffer al nuovo spazio.
    int i;
    for (i = 0; i < N_VERBI; i++)
    {
        printf("Inserisci verbo %d (oppure \"fine\" per terminare): ", i + 1);
        if (scanf("%49s", buffer) != 1) // questo controllo significa che se gli arriva una stringa vuota dará 0 e quindi il programma si chiuderá
        {
            break;
        }
        if (strcmp(buffer, "fine") == 0)
        {
            break;
        }

        // Alloco solo lo spazio necessario (+ 1 per '\0')
        verbi[i] = malloc(strlen(buffer) + 1);
        // controllo malloc
        if (!verbi[i])
        {
            perror("malloc");
            return 1;
        }

        strcpy(verbi[i], buffer); // copio tutti i caratteri di buffer nello spazio allocato corettamente in verbi[i]
    }

    puts("");
    // Stampa dei verbi
    for (int j = 0; j < i; j++)
    {
        printf("%s\n", verbi[j]);
    }

    puts("\nVerbi con suffisso 'are', 'ere' o 'ire':");
    for (int j = 0; j < i; j++)
    {
        if (termina_con(verbi[j], "are") || termina_con(verbi[j], "ere") || termina_con(verbi[j], "ire")) // la funzione termina_con restituisce 1(vero) se il verbo finisce con uno dei suffissi e 0 se é falso
        {
            printf("%s\n", verbi[j]);
        }
        free(verbi[j]); // libero la memoria
    }
}

// Funzione che controlla se la parola termina con un certo suffisso
int termina_con(const char *parola, const char *suffisso)
{
    size_t len_parola = strlen(parola);
    size_t len_suff = strlen(suffisso);

    if (len_parola < len_suff)
        return 0; // troppo corta
    return strcmp(&parola[len_parola - len_suff], suffisso) == 0;
    // &parola é l'indirizzo di quel carattere, cioé il puntatore a char
}