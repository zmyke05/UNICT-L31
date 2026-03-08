#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// -> : si usa quando ho un puntatore alla struct
// .  : so isa qiamdp jp ima variabile diretta della struct, cioé non un puntatore

typedef struct // uso typedef in modo tale che posso scrivere semplicemente record r, invece di struct record r
{
    double numero;
    char carattere;
    char *S;
    char *W;
} record;

void func(record *r, int lenS, int lenW);

int main()
{
    srand(time(NULL)); // inizializza il generatore casuale

    record r;

    func(&r, 5, 5); // S e W di lunghezza 5

    printf("Numero: %.2f\n", r.numero);
    printf("Carattere: %c\n", r.carattere);
    printf("S: %s\n", r.S);
    printf("W: %s\n", r.W);

    // Liberare la memoria
    free(r.S);
    free(r.W);

    return 0;
}

void func(record *r, int lenS, int lenW)
{
    r->numero = (double)rand() / RAND_MAX * 100.0;
    r->carattere = 'A' + rand() % 26;

    // Allochiamo memoria per le stringhe (+1 per '\0')
    r->S = malloc((lenS + 1) * sizeof(char));
    r->W = malloc((lenS + 1) * sizeof(char));

    // Riempire la stringa S con lettere [a-z]
    for (int i = 0; i < lenS; i++)
    {
        r->S[i] = 'a' + rand() % 26;
    }
    r->S[lenS] = '\0'; // terminatore della stringa

    // Riempire W con cifre [0-9]
    for (int i = 0; i < lenW; i++)
    {
        r->W[i] = '0' + rand() % 10;
    }
    r->W[lenW] = '\0'; // terminatore stringa
}