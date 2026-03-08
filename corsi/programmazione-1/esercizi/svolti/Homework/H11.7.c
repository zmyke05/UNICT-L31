#include <stdio.h>
#include <math.h>

int main()
{
    float a;
    float b;

    printf("\nInserisci il primo cateto: ");
    scanf("%f", &a);

    printf("\nInserisci il secondo cateto: ");
    scanf("%f", &b);

    float ipotenusa = sqrt(pow(a, 2) + pow(b, 2));
    
    printf("\nIpotenusa: %f", ipotenusa);
    printf("\n");
}