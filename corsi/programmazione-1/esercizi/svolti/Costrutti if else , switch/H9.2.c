#include <stdio.h>

int main() 
{
    double a = 4;
    double b = 2;
    double c = 8;
    int k;

    printf("\nInserisci un numero intero: ");
    scanf("%d", &k);

    if((a != c)&(k > 8))
    {
        b = a + c;
        printf("\nPrimo caso%f\n", b);
    }

    if ((a == c)&(k < 8))
    {
        a = c - b;
        printf("\nSecondo caso%f\n", a);
    }
    
    printf("Il terzo caso %f\n", (a + b + c)/3);
    
}