#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int N; //Costante
    printf("\nInserisci una costante: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        int dado1 = rand() %7;
        int dado2 = rand() %7;
        
        printf("%d %d\n", dado1, dado2);
    }
}