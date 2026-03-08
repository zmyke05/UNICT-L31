// PUNTATORI E ARRAY
#include <stdio.h>
#include <malloc.h>

void scambia(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    void scambia(int *a, int *b); // PROTOTIPO FUNZIONE

    // un array é un blocco contiguo di celle, il nome dell'array é gia un puntatore alla prima cella
    printf("INTRODUZIONE ARRAY\n");
    int v[3] = {10, 20, 30};
    printf("Stampa del primo valore dell'array con l'aritmetica dei puntatori: %d", *(v + 1));
    printf("\n");
    printf("\n");

    printf("MOMERIA DINAMICA\n");
    // malloc restituisce un puntatore a un blocco di memoria
    // free libera quel blocco.

    int *arr = malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        arr[i] = i * 2;
    }
    free(arr);

    /* Immagina la memoria del computer come una lunga strada piena di cassette della posta.
    Ogni cassetta ha un numero (questo numero si chiama indirizzo).
    Dentro ogni cassetta puoi mettere un valore (ad esempio il numero 7, una lettera, ecc.). */

    int x = 7; // cassetta a 4 byte che chiameró x cha all'interno conterrá il valore 7
    // x é solo il nome che mi aiuta a trovare la cassetta ma dietro le quinte ha un numero di indirizzo (tipo 0x7ffee3b4…).
    int *pX;
    pX = &x;

    // IDEA DEL PUNTATORE
    // un puntatore é una variabile che non contiene un valore normale, ma l'indirizzo di memoria di un'altra cassett

    int y = 5;
    int *pY;
    pY = &y;

    // int *p una variabile puntatore che mi serve per puntare ad un intero, * significa che é un puntatore a int
    // p = &y; dentro p metto l'indirizzo di memoria della cassetta dove c'é y

    // DEFERENZIARE (aprire la cassetta)
    // se voglio leggere o scrivere dentro la cassetta a cui punta p, uso di nuovo *

    printf("DEFERENZIARE (aprire la cassetta)\n");
    printf("%d\n", *pY); // stampa 5
    *pY = 10;            // il contenuto di y diventa 10
    printf("\n");

    // *p vado all'indirizzo che c'é guardo/cambio il valore che c'é dentro
    // p l'indirizzo (tipo 0x7ffee3b4…)
    // *p il contenuto (es 5, 10)

    // A COSA SERVONO?
    // Immagina di dover passare una cassetta a una funzione, non solo una copia del contenuto.
    // Con i puntatori puoi dire: “Ehi funzione, qui c’è l’indirizzo della cassetta, aprila tu direttamente”.
    // ESEMPIO CAMBIO I VALORI
    printf("ESEMPIO CAMBIO I VALORI\n");
    printf("Stampa prima del cambio: X -> %d - Y -> %d", *pX, *pY);
    scambia(pX, pY);

    printf("\nStampa dopo del cambio: X -> %d - Y -> %d", *pX, *pY);
    printf("\n");
    printf("\n");

    // PUNTATORI E ARRAY
    printf("PUNTATORI E ARRAY\n");
    // un array é una fvila di cassette una dopo l'altra: 1 --> 2 --> 3 --> 4 etc..
    // Il nome di una array é giá un puntatore alla prima cassetta
    int num[3] = {10, 20, 30};
    printf("Valore dell'array con puntatore: %d", *(num + 1));
    printf("\n");
    printf("\n");

    // RIEPILOGO
    // Variabile normale = cassetta che contiene un valore.
    // Indirizzo = numero di quella cassetta.
    // Puntatore = cassetta che contiene un indirizzo.
    //& = “dammi il numero della cassetta”.
    //\* davanti a un puntatore = “vai a vedere (o cambia) il contenuto della cassetta a quell’indirizzo”.

    // PUNTATORE DOPPIO
    printf("PUNTATORE DOPPIO\n");
    //  Un doppio puntatore è una variabile che contiene l’indirizzo di un puntatore.
    int a = 42;
    int *pA = &a;
    int **ppA = &pA;
    // pp contiene l’indirizzo di p.
    //*pp → è il contenuto di p (cioè l’indirizzo di a).
    //**pp → segui due volte: arrivi al contenuto di a (42).
    printf("Puntatore doppio prima della modifica: %d", **ppA);
    printf("\n");
    **ppA = 77;
    printf("Puntatore doppio dopo la modifica: %d", **ppA);
    printf("\n");
    printf("\n");

    // PERCHÉ SERVE?
    // Quando vuoi che una funzione possa cambiare un puntatore. Es: allocare memoria dentro una funzione (malloc).

    // TRIPLO PUNTATORE
    printf("TRIPLO PUNTATORE\n");
    // un triplo puntatore é lo stesso concetto del dobbio ma con tre salti
    int b = 5;
    int *pB = &b;
    int **ppB = &pB;
    int ***pppB = &ppB;
    // ppp → indirizzo di pp
    // *ppp → è pp
    // **ppp → è p
    // ***ppp → è a(5)
    // Puoi fare ***ppp = 100; per cambiare a.

    printf("Puntatore doppio prima della modifica: %d", ***pppB);
    printf("\n");
    ***pppB = 98;
    printf("Puntatore doppio dopo la modifica: %d", ***pppB);
    printf("\n");
    printf("\n");
    
    // A COSA SERVE?
    // Molto raro, ma utile quando hai array di puntatori a puntatori (es. matrici dinamiche, funzioni che devono modificare un doppio puntatore).
}