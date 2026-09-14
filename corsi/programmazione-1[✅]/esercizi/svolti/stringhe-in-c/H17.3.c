#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    char *nome = malloc(15 + 1);
    char *cognome = malloc(15 + 1);
    char *completo = malloc(30 + 1);

    printf("\nInserisci il nome: ");
    scanf("%s", nome);

    printf("Inserisci il cognome: ");
    scanf("%s", cognome);

    puts("");

    strcpy(completo, nome);
    strcat(completo, ";");
    strcat(completo, cognome);

    printf("completo: %s", completo);

    free(nome);
    free(cognome);
    free(completo);
}