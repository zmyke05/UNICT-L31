#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    puts("");
    // --- 1) Array di 15 caratteri riempito con lettere random a-z ---
    int len = 15;
    char *s1 = malloc(sizeof(char) * (len + 1)); // + 1 per il terminatore

    if (!s1)
    {
        perror("malloc");
        return 1;
    }

    srand(time(0)); // imposta seed random del generatore di numeri pseudo-casuali mentre time(0) restituisce il tempo corrente in seccondi dal 1 gennaio 1970 é un numero che aumenta ogni secondo

    for (int i = 0; i < len; i++)
        s1[i] = 'a' + (rand() % 26);
    s1[len] = '\0';

    printf("Array di caraatteri casuale: %s", s1);
    puts("");

    free(s1);

    // --- 2) Array mediante una lista di inizalizzazione che abbia almeno 5 caratteri ---
    char s2[] = {'m', 'a', 'r', 'i', 'o', '\0'};

    printf("\nLista di inizalizzazione: %s", s2);
    puts("");


    // --- 3) Array mediante un inizializzatore che sia un letterale stringa ---
    char s3[] = "Hello_World";

    printf("\nLunghezza stringa letterale: %ld", strlen(s3));
    puts("");


    // --- 4) Array di caratteri di sola letturaa ---
    const char *s4 = "Stringa_Constante";
    printf("\nStringha constante: %s - Lunghezza: %ld", s4, strlen(s4));
    puts("");
}