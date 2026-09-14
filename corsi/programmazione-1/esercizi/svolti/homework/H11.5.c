#include <stdio.h>
#include <math.h>

int main()
{
    float a;
    float b;
    float c;

    printf("\nInserisci il primo valore: ");
    scanf("%f", &a);

    printf("\nInserisci il secondo valore: ");
    scanf("%f", &b);

    printf("\nInserisci il terzo valore: ");
    scanf("%f", &c);

    printf("\n Primo valore arrotondato: %.0f", round(a));
    printf("\n Secondo valore arrotondato: %.0f", round(b));
    printf("\n Terzo valore arrotondato: %.0f", round(c));
    
    printf("\n\n");
}