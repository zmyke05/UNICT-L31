#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 200

int main()
{
    double V[N];
    const double *ptrV = V;
    double *const ptrCV = V;

    srand(time(0));

    //Input e Output dell'array originale
    printf("\n");
    printf("STAMPA DELL'ARRAY ORIGINALE");
    for (int i = 0; i < N; i++)
    {
        int min = 10;
        int max = 50;
        V[i] = (double)rand() / RAND_MAX * (max - min) + min;
        printf("\narray[%d]: %.2lf", i, *(V+i));
    }

    printf("\n");
    printf("\n");

    printf("STAMPA DELL'ARRAY NON DIVISIBE PER 2 E NE PER 3");
    for (int i = 0; i < N; i++)
    {
        if ((int)*(ptrV+i)%2 != 0 && (int)*(ptrV+i)%3 != 0)
        {
            printf("\narray[%d]: %.2lf", i, *(ptrV+i));
        }  
    }

    printf("\n");
    printf("\n");

    printf("STAMPA DELL'ARRAY CAMBIATO");
    for (int i = 0; i < N; i++)
    {
        int min = 100;
        int max = 200;
        *(ptrCV + i) = (double)rand() / RAND_MAX * (max - min) + min;
        printf("\narray[%d]: %.2lf", i, *(ptrCV+i));
    }
    printf("\n");
}