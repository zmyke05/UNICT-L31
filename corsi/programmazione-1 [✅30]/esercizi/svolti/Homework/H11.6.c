#include <stdio.h>
#include <string.h>

int main() {
    char nome[50], cognome[50];

    printf("Inserisci il nome: ");
    scanf("%s", nome);

    printf("Inserisci il cognome: ");
    scanf("%s", cognome);

    printf("Caratteri in comune: ");

    for (int i = 0; nome[i] != '\0'; i++) {
        for (int j = 0; cognome[j] != '\0'; j++) {
            if (nome[i] == cognome[j]) {
                printf("%c", nome[i]);
                break; // eviti di stampare più volte lo stesso nome[i]
            }
        }
    }

    printf("\n");
    return 0;
}