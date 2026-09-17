#include <stdio.h>
#include <stdlib.h>

short valoreAssoluto(short a, short b);

int main()
{
    int risultato = valoreAssoluto(5, 4);
    printf("\nRISULTATO: %hd\n", risultato);
}

short valoreAssoluto(short a, short b)
{
    int prodotto = a * b;
    int prodottoAbs = abs(prodotto);

    return prodottoAbs;


}