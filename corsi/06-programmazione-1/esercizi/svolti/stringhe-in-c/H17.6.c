#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> // per islower, isdigit, is

#define MAX_STRING 30
#define MAX_LEN 20

int main()
{
    char *string[30];
    char buffer[MAX_LEN];

    int i;
    for (i = 0; i < MAX_LEN; i++)
    {
        printf("Inserisci una stringa (inserire \"fine\" se hai finito di inserire le stringhe): ");
        fgets(buffer, MAX_LEN, stdin); // fgets lgge tutta la riga compresi gli spazi fino al terminatore \n o alla lunghezza massima
        // stdin sta per standard input é uno stream predefinito che rappresenta l'inpput da cui il programma legge normalmente i dati

        // rimuovere l'eventuale newline alla fine
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        /* if (scanf("%19s", buffer) != 1) // %s legge solo fino al primo spazio tab o invio, quindi se l'utente digita "Ciao Mondo", buffer conterrá solo "Ciao" e lo spazio non viene letto
        {
            break;
        } */
        if (strcmp(buffer, "fine") == 0)
        {
            break;
        }

        string[i] = malloc(strlen(buffer) + 1);
        if (!string[i])
        {
            perror("malloc");
            return 1;
        }

        strcpy(string[i], buffer);
    }

    puts("");
    // ---2) controllo minuscole, numeri, spazi ---
    for (int j = 0; j < i; j++) // questo ciclo scorre le stringhe dell'array
    {
        // contatori
        int minuscole = 0;
        int numeri = 0;
        int spazi = 0;

        for (int k = 0; string[j][k] != '\0'; k++) // questo ciclo scorre i caratteri della stringa
        {
            char c = string[j][k];
            if (islower(c))
            {
                minuscole++;
            }
            if (isdigit(c))
            {
                numeri++;
            }
            if (isspace(c))
            {
                spazi++;
            }
        }

        printf("Stringa: %s\n", string[j]);
        printf("Lettere minuscole: %d\n", minuscole);
        printf("Numeri: %d\n", numeri);
        printf("Spazi: %d\n\n", spazi);
    }
}