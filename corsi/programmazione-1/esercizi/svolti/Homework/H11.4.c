#include <stdio.h>

int main()
{
    int a;
    int b; 
    double somma;
    double media;
    double max;

    printf("\nInserisci il primo valore: ");
    scanf("%d", &a);

    printf("\nInserisci il secondo valore: ");
    scanf("%d", &b);

    somma = a + b;

    media = (a + b)/2;

    max = a;
    if (b > max)
    {
        max = b;
    }

    printf("\nSomma: %.4e", somma);
    printf("\nMedia: %.4e", media);
    printf("\nMax: %.4e", max);
    printf("\n");
}