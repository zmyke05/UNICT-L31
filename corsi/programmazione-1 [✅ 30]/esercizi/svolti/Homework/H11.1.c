#include <stdio.h>

int main()
{
    double x;
    double y;

    do
    {
        printf("\nInserisci il primo valore 0 < x < 1: ");
        scanf("%lf", &x);

        if (x < 0 || x > 1)
        {
            printf("\nIl valore inserito é errato riprova");
        }

    } while (x < 0 || x > 1);

    printf("Inserisci il secondo valore y < 0 || y > 0: ");
    scanf("%lf", &y);

    int i = 0;
    do
    {
        y = y * x;
        printf("\nValore %d: %e", i, y);

        i++;
    } while (y != 0);

    printf("\n");
}