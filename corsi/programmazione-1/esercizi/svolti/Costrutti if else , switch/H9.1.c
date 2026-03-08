#include <stdio.h>

int main()
{
    int a = 7;
    int b = 9;
    int c = 3; 

    int max = a;
    if (b > max)
    {
        max = b;
    } else
    {
        max = c;
    }

    printf("Il numero massimo é %d", max);
    printf("\n");
}