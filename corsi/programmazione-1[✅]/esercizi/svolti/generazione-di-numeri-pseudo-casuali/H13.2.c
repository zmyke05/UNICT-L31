#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    long long nCampioni;          // numero di punti da generare
    long long puntiNelCerchio = 0; // contatore punti interni al cerchio
    double x, y;

    // Chiedi all'utente il numero di campioni
    printf("Inserisci il numero di campionamenti: ");
    if (scanf("%lld", &nCampioni) != 1 || nCampioni <= 0) {
        printf("Numero non valido.\n");
        return 1;
    }

    // Inizializza il generatore di numeri casuali
    srand((unsigned)time(NULL))

    for (long long i = 0; i < nCampioni; i++) {
        // Genera due coordinate casuali tra 0 e 1
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Verifica se il punto (x,y) è interno al quarto di cerchio di raggio 1
        if (x * x + y * y <= 1.0) {
            puntiNelCerchio++;
        }
    }

    // Stima di π: 4 * (punti nel cerchio / punti totali)
    double pi_approx = 4.0 * (double)puntiNelCerchio / (double)nCampioni;
    printf("Stima di pi greco con %lld campioni: %.10f\n", nCampioni, pi_approx);

    return 0;
}
