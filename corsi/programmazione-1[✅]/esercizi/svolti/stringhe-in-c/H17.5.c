#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 50

int main()
{
    char *str1, *str2, *str3; // per memorizzare le stringhe
    double num1, num2, num3;  // per memorizzare i numeri convertiti

    // Allocazione in memoria dinamica
    str1 = malloc(MAX_LEN + 1);
    str2 = malloc(MAX_LEN + 1);
    str3 = malloc(MAX_LEN + 1);
    if (!str1 || !str2 || str3)
    {
        perror("malloc");
        return 1; // é il valore che indica l'uscita del programma se é != da 0 vuol dire che c'é stato qualche errore durante l'esecuzione del programma
    }
    

    printf("Inserisci il primo numero: ");
    scanf("%49s", str1);

    printf("Inserisci il secondo numero: ");
    scanf("%49s", str2);

    printf("Inserisci il terzo numero: ");
    scanf("%49s", str3);

    // ---1) primo numero con atof ---
    num1 = atof(str1); // atof prende una stringa e restituisce un double

    // ---2) secondo numero con sscanf ---  // funzione sscanf() piú "sofisticata": permette di estrarre piú di un elemenmto (non solo numeri) alla volta.
    sscanf(str2, "%lf", &num2); // lf per il formato double, &num2 puntatore della variabile dove salvare

    // ---3) terzo numero con strtof --- restiuisce float ma possiamo assegnarlo a double senza problemi
    num3 = strtof(str3, NULL); // il secondo parametro (NULL) puó essere usato se vogliamo sapere dove finisce il numero della stringa ma qui non ci serve

    // Libero la memoria delle stringhe visto che non mi serve piú
    free(str1);
    free(str2);
    free(str3);

    // ---4) la media tra i 3 numeri in virgola mobile ---
    double media = (num1 + num2 + num3) / 3;

    printf("\nLa media dei tre numeri è: %.2f\n", media); // STAMPA DELLA MEDIA
    puts("");


}