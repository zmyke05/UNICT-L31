#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    double D[10];
    int A[10];

    double *ptr_D = D;
    int *ptr_A = A;

    srand(time(0));

    printf("\n");

    // Assegnazione valori all'array double
    printf("STAMPA ARRAY DOUBLE\n");
    for (int i = 0; i < 10; i++)
    {
        double min = 1.25;
        double max = 90;
        D[i] = (double)rand() / RAND_MAX * (max - min) + min;
        printf("array[%d]: %.2lf\n", i, D[i]);
    }

    printf("\n");

    // Assegnazione valori all'array int
    printf("STAMPA ARRAY INT\n");
    for (int i = 0; i < 10; i++)
    {
        double min = 10;
        double max = 50;
        A[i] = (double)rand() / RAND_MAX * (max - min) + min;
        printf("array[%d]: %d\n", i, A[i]);
    }
    
    printf("\n");

    // Stampa dell'array D con indici dispari
    printf("STAMPA ARRAY D CON INDICE DISPARI");
    for (int i = 1; i < 10; i+=2)
    {
        printf("\narray[%d]: %.2lf - %p", i, *(D+i), D+i);
    }

    printf("\n");
    printf("\n");

    // Stampa dell'array T con indici dispari
    printf("STAMPA ARRAY A CON INDICE DISPARI");
    for (int i = 0; i < 10; i+=2)
    {
        printf("\narray[%d]: %d - %p", i, *(A+i), A+i);
    }

    printf("\n");
    
}