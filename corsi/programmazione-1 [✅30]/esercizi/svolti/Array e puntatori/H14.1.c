#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Dichiarazione e inizializzazione delle variabili
    double a = 3.14;
    unsigned short b = 65000;
    char c = 'X';

    // Puntatori
    double *pA = &a;
    unsigned short *pB = &b;
    char *pC = &c;

    // Stampa tramite le variabili
    printf("\nValore di a (double): %lf", a);
    printf("\nValore di b (unsigned short): %hu", b);
    printf("\nValore di c (char): %c", c);

    // Stampa tramite dereferenziazione dei puntatori
    printf("\nValore di a tramite pA: %lf", *pA);
    printf("\nValore di b tramite pB: %hu", *pB);
    printf("\nValore di c tramite pC: %c", *pC);

    // Stampa degli indirizzi contenuti nei puntatori
    printf("\nIndirizzo contenuto in pA: %p", pA);
    printf("\nIndirizzo contenuto in pB: %p", pB);
    printf("\nIndirizzo contenuto in pC: %p\n", pC);

    return 0;
}
