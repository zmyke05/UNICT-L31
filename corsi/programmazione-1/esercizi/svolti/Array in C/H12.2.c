#include <stdio.h>
#include <math.h>

int main()
{
    double N, M;

    printf("\n");
    printf("Inserimento Dimensione\n");
    do
    {
        printf("Inserisci il I valore > 1: ");
        scanf("%lf", &N);

        printf("Inserisci il II valore > 1: ");
        scanf("%lf", &M);

        if (N < 1 || M < 1)
        {
            printf("\nError");
        }

    } while (N < 1 || M < 1);

    int roundN = round(N);
    int roundM = round(M);

    double matrice[roundN][roundM];

    printf("\n");
    printf("Inserimento Array\n");
    for (int i = 0; i < roundN; i++)
    {
        for (int j = 0; j < roundM; j++)
        {
            printf("Inserisci matrice[%d][%d]: ", i, j);
            scanf("%lf", &matrice[i][j]);
        }
    }

    int min = N;
    if (M < min)
    {
        min = M;
    }

    double matriceMin[min][min];

    printf("\n");
    printf("\nNuova Matrice");
    for (int i = 0; i < min; i++)
    {
        for (int j = 0; j < min; j++)
        {
            matriceMin[i][j] = matrice[i][j];
            printf("\nMatrice[%d][%d]: %.2lf", i, j, matrice[i][j]);
        }
    }

    printf("\n");
}