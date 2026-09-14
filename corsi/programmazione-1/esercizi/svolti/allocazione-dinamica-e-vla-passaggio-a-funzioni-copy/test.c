#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COLS 10
#define ROWS 5

// size_t é il tipo di dato che si aspetta una malloc e, anche se inserisco un intero, forzo la conversione per essere sicuro che non ci sia rischio di overflow di segno, se il numero intero fosse grande

// ERRORI CHE POSSONO ESSERCI:
// ---1) “Segmentation fault (core dumped)” ovvero che il programma ha dcercato di leggere o scrivere in una zona di memoria che non gli appartiana. Come si verifica? ecco i casi
// Uso un puntatore che non é mai stato inizializzato, Accesso fuori dei limiti, dopo la free uso la zona di memoria che non esiste piú, doppia free

//COSA SIGNIFICA PSEUDO-CASUALE?


// Per il passaggio di array multidimensionali allocati nel free store (HEAP) il prototipo della funzione che riceve il dato deve specificare un array di puntatori di un certo tipo che dipende dal
// numero di dimensioni dell'array

/* void init(int **v, int n, int m);        // OK */
/* void init(int *v[], int n, int m); */ // OK

int main()
{
    srand(time(0));
    // lo HEAP é un segmento di memoria che permette alle applicazioni di memorizzare dati in modo dinamico
    // in qeusto caso l'allocazione a la deallocazione avvengono mediante apposite chiamate a funzioni
    // funzioni malloc() e free() della libreria stdlib.h

    // ALLOCAZIONE DINAMICA: HEAP O FREE STORE
    /*  double *arr = malloc(sizeof(double) * 10); */
    /*  free(arr); */ // deallocazione

    // malloc() alloca dinamicamente un blocco di memoria nello HEAP (o Free Store)
    // - argomento é dimensione in byte (IMPORTANTE USO DI SIZEOF)
    // - restituisce un puntatore generico, ovvero di tipo void *, per questo bisogna operare un type casting al tipo desiderato
    // la funzione free() libera la memoria precendentemnete allocata

    // DIFFERENZE TRA ALLOCAZIONE AUTOMATICA E ALLOCAZIONE DIMANICA
    //  allocazione automatica: memoria automaticamente deallocata dopo ultima istruzione del blocco in cui la variabile é stata dichiarata.
    //  allocazione dinamica: la memoria allocata dinamicamente va successivamente liberata neduabte ka funzione free

    // il valore dell'array rimarrá invariato:
    double *arr1 = malloc(sizeof(double) * 10);
    printf("\n%p", arr1);

    free(arr1);

    printf("\nFree: %p", arr1);
    puts("");

    // MEMORY LEAK / ALIASING
     double *arr2 = malloc(sizeof(double) * 10);
     double *v = malloc(sizeof(double) * 10);

     v = arr2;

    // A seguito dellla copia di un differente indirizzo di memoria nella variabile v ("effetto aliasing") si perde il riferimento (indirizzo) al blocco di memoria degli elementi double
    // Deallocare il blocco di memoria referianziato da v?? Non piú possibile manca il puntatore --> memory leak

     double *arr3 = malloc(sizeof(double) * 10);

    free(arr3);
    free(arr3);
    // comportamento indefinito!
    // puó capitare in programmi lunghi di fare accidentalmente due free, come abbiamo detto in precendenza il valore dopo la prima free rimarrá invariato, ulteriore tentativo avrá comportamente indefinito

    double *arr4 = malloc(sizeof(double) * 10);

    if (arr4)
    {
        free(arr4);
        arr4 = NULL;
    }

    // - ad ogni tentativo di deallocazione, inserire un controllo sul valore del puntatore,
    // - "azzerare" il puntatore dopo invocazione a funzione free()

    double *arr5 = malloc(sizeof(double) * 10);
    double *v1 = arr5; // v é l'alias di arr5

    if (arr5)
    {
        free(arr5);
        arr5 = NULL;
    }
    v[5] = 4, 56789;

    // dopo la free di arr5, operata per errore, esso sará null ma v conserva il vecchio valore di arr5

      double *arr6[ROWS];  // allocazione automatica nello stack
                                 // OPPURE
     double **arr6_ = malloc(sizeof(double) * ROWS);  // allocazione dinamica nel free store/heap

    // alllocazione dinamica di ROWS vettori di COLS celle di tipo double
    for (size_t i = 0; i < ROWS; i++)
    {
        arr6_[i] = malloc(sizeof(double) * COLS);
    }
    // accesso agli elementi sintatticamente equivalente a quello relativo array a due dimensioni allocati nello stack
    /* int i, j;
    arr7[i][j];
    (*(arr7 + i))[j];
    *(arr[i] + j);
    *(*(arr + i) + j); */

    // PASSAGGIO DI ARRAY A FUNZIONI(ALLOCAZIONE DINAMICA)
    int *x = malloc(sizeof(int) * 10);
    /* init(x, 10); */

    // ARRAY A DUE DIMENSIONI
    int **v2 = malloc(sizeof(int *) * 5);
    for (unsigned short i = 0; i < 5; i++)
    {
        v2[i] = malloc(sizeof(int) * 10);
        init(v2, 5, 10);
    }
    // crea una matrice di 5 righe e 10 colonne di int, ma allocata dimanicamente quindi le dimensioni possono essere decise in runtime(PROGRAMMA IN ESECUZIONE)

    // ARRAY A 3 DIMENSIONI
    //  array[piano][riga][colonna]
    // Piano 0:
    // [0][0][0] [0][0][1] [0][0][2] [0][0][3]
    // [0][1][0] [0][1][1] [0][1][2] [0][1][3]
    // [0][2][0] [0][2][1] [0][2][2] [0][2][3]

    //  Piano 1:
    // [1][0][0] [1][0][1] [1][0][2] [1][0][3]
    // [1][1][0] [1][1][1] [1][1][2] [1][1][3]
    // [1][2][0] [1][2][1] [1][2][2] [1][2][3]

    int ***v3 = malloc(sizeof(int **) * 5);
    for (unsigned short i = 0; i < 5; i++)
    {
        v3[i] = malloc(sizeof(int *) * 7);
        for (unsigned short j = 0; j < 7; j++)
        {
            *(*(v3+i)+j) = malloc(sizeof(int) * 9);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        puts("");
        printf("Piano %d", i);
        puts("");
        for (int j = 0; j < 7; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                *(*(*(v3 + i) + j) + k) = rand() % 100 + 1;
                printf("rray[%d][%d][%d]: %d", i, j, k, v3[i][j][k]);
                printf("\t");
            }
            printf("\n");
        }
    }

    free(v3);
}

// FUNZIONI CHE RESTIUISCONO UN PUNTATORE
// ESEMPIO DI FUNZIONE SBAGLIATA
/* int *func (int k)
{
    int arr[k];
    for (int i = 0; i < k; i++)
    {
        arr[i] = 2*i;
        return arr; // NO SBAGLIATO
    }

    int *array = func(10);
}
 */
// CORRETTO NO!!!
//  infatti arr presenta un blocco di memoria allocato nello stack, dopo istruzione return record di attivazione per la func() distrutto.

int *func(int k)
{
    int *arr = malloc(sizeof(int) * k); // allocato dinamicamente nel free store
    for (int i = 0; i < k; i++)
    {
        arr[i] = 2 * i;
        return arr; // NO SBAGLIATO
    }

    int *array = func(10);
}

// in questo caso memoria allocata per arr nel free store non sará liberata fino a chiamata di free(arr)

// PASSAGGIO DI ARRAY A FUNZIONI(ALLOCAZIONE DINAMICA)
/* void init(int *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = 0;
    }
} */

// OPPURE FORMA EQUIVALENTE A QUELLA PRECENDENTE
/* void init2(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = 0;
    }
} */
