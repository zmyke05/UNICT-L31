#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int arrayCaratteri(char s1[50], size_t n);

int main()
{
    char s1[100]; // array di caratteri
    int n;        // dimensione
    int count;

    srand(time(0));

    do
    {
        printf("\nInserisci la dimensione dell'array di caratteri: ");
        scanf("%d", &n);

        if (n < 0)
        {
            printf("\nInserisci un valore > 0.");
        }

    } while (n < 0);

    count = arrayCaratteri(s1, n);
    printf("Il numero di vocali: %d", count);
    printf("\n\n");
}

int arrayCaratteri(char s1[100], size_t n)
{
    int countV = 0;
    for (size_t i = 0; i < n; i++)
    {
        *(s1 + i) = 'a' + rand() % 26;
        int c = s1[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            countV++;
        }
    }
    s1[n] = '\0';
    return countV;
}
