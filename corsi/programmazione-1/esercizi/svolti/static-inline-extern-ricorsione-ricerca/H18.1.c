// Implementazione di un calcolo fattoriale
#include <stdio.h>
#include <stdlib.h>

long fattoriale(int n)
{
    printf("\nfatto(%d)", n);
    if (n == 0)
    {
        return 1; // caso base
    }
    return n * fattoriale(n - 1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\n No argument! ");
        return -1;
    }

    printf("\n risultato: %le", (double)fattoriale(atoi(argv[1])));
    return 0;
}