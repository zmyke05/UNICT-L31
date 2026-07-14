#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int arrayCaratteri(char s1[50], char s2[50]);

int main()
{
    char s1[50];
    char s2[50];

    printf("\n\nINSERIMENTO");
    printf("\nInserisci la prima stringa: ");
    scanf("%s", s1);

    printf("Inserisci la seconda stringa: ");
    scanf("%s", s2);

    printf("\n");
    printf("CONFRONTO\n");
    int confronto = arrayCaratteri(s1, s2);
    if (confronto > 0)
    {
        printf("s1 > s2");
    } else if (confronto < 0)
    {
        printf("s1 < s2");
    } else
    {
        printf("s1 == s2");
    }

    printf("\n\n");
    
    
    

}

int arrayCaratteri(char s1[50], char s2[50])
{
    int confronto = 0;
    if (strcmp(s1, s2) < 0)
    {
        confronto = -1;
    } else if (strcmp(s1, s2) > 0)
    {
        confronto = 1;
    }
    return confronto;
}

