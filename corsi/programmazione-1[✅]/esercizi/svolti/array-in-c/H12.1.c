#include <stdio.h>
#include <math.h>

int main()
{
    double p;
    int roundP;
    int array[100];

    do
    {
        printf("\nInserisci La dimensione dell'array: ");
        scanf("%lf", &p);

        if (p < 1)
            printf("\nInserimento errato.");

    } while (p < 1);

    roundP = round(p);
    printf("\n");
    printf("CICLO FOR\n");
    for (int i = 0; i < roundP; i++)
    {
        printf("Inserisci l'array[%d]: ", i);
        scanf("%d", &array[i]);
    }

    printf("\n");
    printf("CICLO WHILE\n");
    int i = 0;
    while (i < roundP)
    {
        printf("Inserisci l'array[%d]: ", i);
        scanf("%d", &array[i]);

        i++;
    }

    printf("\n");
    printf("CICLO DO WHILE\n");
    i = 0;
    do
    {
        printf("Inserisci l'array[%d]: ", i);
        scanf("%d", &array[i]);

        i++;
    } while (i < roundP);

    printf("\n");
    printf("STAMPA");
    for (int i = 0; i < roundP; i++)
    {
        printf("\nl'array[%d]: %d", i, array[i]);
    }

    printf("\n");
}