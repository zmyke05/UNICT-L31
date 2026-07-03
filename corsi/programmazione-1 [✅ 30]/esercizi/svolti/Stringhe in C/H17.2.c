#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    srand(time(NULL));
    int min = 10;
    int max = 20;

    // Lunghezze pseudo-casuali con un intervallo [10, 20]
    int len1 = min + rand() % (max - min + 1);
    int len2 = min + rand() % (max - min + 1);
    int len3 = min + rand() % (max - min + 1);

    char *s1 = malloc(sizeof(char) * len1);
    char *s2 = malloc(sizeof(char) * len2);
    char *s3 = malloc(sizeof(char) * len3);

    printf("\ns1: %d - s2: %d - s3: %d", len1, len2, len3);
    puts("");

    // Riempimento della stringa s1 con caratteri pseudo-casuali [a-z]
    for (int i = 0; i < len1; i++)
    {
        int r = rand() % 36;
        if (r < 26)
            s1[i] = 'a' + r; // lettere a-z
        else
            s1[i] = '0' + (r - 26); // numeri 0-9
    }

    // Riempimento della stringa s2 con caratteri pseudo-casuali [a-z]
    for (int i = 0; i < len2; i++)
    {
        int r = rand() % 36;
        if (r < 26)
            s2[i] = 'a' + r; // lettere a-z
        else
            s2[i] = '0' + (r - 26); // numeri 0-9
    }

    // Riempimento della stringa s3 con caratteri pseudo-casuali [a-z]
    for (int i = 0; i < len3; i++)
    {
        int r = rand() % 36;
        if (r < 26)
            s3[i] = 'a' + r; // lettere a-z
        else
            s3[i] = '0' + (r - 26); // numeri 0-9
    }

    printf("\ns1: %s - s2: %s - s3: %s", s1, s2, s3);
    puts("");
    strcmp(s1, s2);
    
}