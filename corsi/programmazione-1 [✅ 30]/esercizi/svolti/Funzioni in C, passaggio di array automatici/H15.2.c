#include <stdio.h>
#include <stdlib.h>

void valoreAssoluto(short a, short b, short unsigned *ptr);

int main()
{
    short unsigned p;
    valoreAssoluto(5, 4, &p);
    printf("\nRISULTATO: %hd\n", p);
}

void valoreAssoluto(short a, short b, short unsigned *ptr)
{
    int prodotto = a * b;
    *ptr = abs(prodotto);
}
