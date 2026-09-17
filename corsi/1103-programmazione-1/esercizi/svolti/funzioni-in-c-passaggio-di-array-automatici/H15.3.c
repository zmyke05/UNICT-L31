#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int lenght(char s1[50]);

int main()
{
    char s1[50];
    int lenghtS1;

    printf("\n\nINSERIMENTO");
    printf("\nInserisci la stringa: ");
    scanf("%s", s1);


    printf("\n");
    printf("lenght\n");
    lenghtS1 = lenght(s1);
    printf("Lunghezza della stringa s1: %d", lenghtS1);
    printf("\n\n");
    
    
    

}

int lenght(char s1[50])
{
    int lenght = strlen(s1);
    return lenght;
}

