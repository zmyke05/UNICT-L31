#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

double differenza(int m[100][100], size_t n);

int main()
{
    int m[100][100];
    int n;

    srand(time(0));

    // inserimento dimensione
    do
    {
        printf("\nInserisci la dimensione della matrice: ");
        scanf("%d", &n);

        if (n < 0 || n >= 100)
        {
            printf("\nInserisci un valore > 0.");
        }

    } while (n < 0 || n >= 100);

    printf("\n\n");
    // inserimento numeri pseudocasuali
    printf("MATRICE ORIGINALE");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            *(*(m + i) + j) = rand() % 100 + 1;
            printf("\tmatrice[%ld][%ld]: %d", i, j, *(*(m + i) + j));
        }
        printf("\n");
    }

    printf("\n\n");

    printf("DIAGONALE PRINCIPALE\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("\tmatrice[%ld][%ld]: %d", i, i, *(*(m + i) + i));
    }
    printf("\n\n");

    printf("DIAGONALE SECONDARIA\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("\tmatrice[%ld][%ld]: %d", i, n - 1 - i, *(*(m + i) + (n - 1 - i)));
    }
    printf("\n\n");

    printf("DIFFERENZA TRA DIAGONALE PRINCIPALE E SECONDARIA: %.2lf", differenza(m, n));

    printf("\n\n");
}

double differenza(int m[100][100], size_t n)
{
    int sommaP = 0;
    int sommaS = 0;
    double mediaP = 1;
    double mediaS = 1;
    double differenza = 0;
    for (size_t i = 0; i < n; i++)
    {
        sommaP += *(*(m + i) + (n - 1 - i));
    }

    for (size_t i = 0; i < n; i++)
    {
        sommaS += *(*(m + i) + i);
    }

    mediaP = sommaP / n;
    mediaS = sommaS / n;
    differenza = mediaP - mediaS;
    return abs(differenza);
}