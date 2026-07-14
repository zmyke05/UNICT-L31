#include <stdio.h>

int somma(int a, int b); // prototipo della funzione
void stampaArray(int arr[], int n);

int main()
{
    // VARIABILI
    // Variabili locali: vivono dentro una funzione → appena esci dalla funzione, spariscono.
    // Variabili globali: vivono fuori da tutte le funzioni → tutti le possono usare.
    // Visibilità: indica chi può vedere quella variabile.
    // Classe di memorizzazione (storage class) dice quanto vivono e dove stanno:
    // auto (default): locale, nasce e muore dentro la funzione.
    // static: locale ma non muore mai → ricorda il valore anche dopo che la funzione finisce.
    // extern: variabile definita da un’altra parte, ma la puoi usare.
    // register: chiede al PC di mettere la variabile in un posto super veloce (i registri della CPU).

    // ESEMPIO BASE DI FUNZIONE
    int risultato = somma(5, 5); // chiamata della funzione
    printf("\nRISULTATO: %d", risultato);
    printf("\n\n");

    // PASSAGGIO DI ARRAY A FUNZIONE
    int array[5] = {4, 3, 2, 5, 2};
    printf("STAMPA ARRAY");
    stampaArray(array, 5);
    printf("\n");
}

int somma(int a, int b) // tipo int, parametri a e b
{
    int somma = a + b;
    return somma;
}

void stampaArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\narray[%d]: %d", i, arr[i]);
    }
}

void init (int *v, int n)
{
    
}