#include <stdio.h>
#include <math.h>

int main()
{
    double x;
    double y;

    do
    {
        printf("\nInserisci il primo valore x < 1: ");
        scanf("%lf", &x);

        if (x > 1)
        {
            printf("\nInserimento errato riprova");
        }

    } while (x > 1);

    do
    {
        printf("\nInserisci il secondo valore y > 1: ");
        scanf("%lf", &y);

        if (y < 1)
        {
            printf("\nInserimento errato riprova");
        }

    } while (y < 1);

    int i = 0;
    do
    {
        y = y * x;
        printf("\nIl valore %d: %e", i, y);

        i++;

    } while (!isinf(y) && y > 0.0);

    if (isinf(y))
        printf("\nSi è verificata la condizione di OVERFLOW (INF)");
    else if (y == 0.0)
        printf("\nSi è verificata la condizione di UNDERFLOW (0)");

    printf("\n\n");
}