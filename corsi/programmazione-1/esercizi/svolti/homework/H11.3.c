#include <stdio.h>

int main()
{
    double x = 2.0;
    int y = 2;
    double op1;
    int op2;

    op1 = x/0;
    op2 = y/0;

    printf("\nIl risultato della prima operazione: %lf", op1);
    printf("\nIl risultato della prima operazione: %d", op2);
    
}