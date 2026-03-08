#include <stdio.h>
// ======================================================
// Ricerca sequenziale di un elemento in un array.
// ======================================================
// Data una struttura dati lineare (esempio: array), ricercare un elemento X tra le componenti dello array.
// Nella sua forma piú semplice (ricerca tutte le occorenze del numero nella struttura lineare)
// Questa é un algoritmo semplice ma poco efficente, poiché deve controllare da i=0 a i=n-1

int A[DIM];
while (i++ < dim)
{
    if (A[i] == numero)
    {
        printf("Hai trovato il numero")
    }
}

// ====================
// Ricerca Dicomotica
// ====================
// Dicotomia == divisione in due parti
// Sia A un array ordinato (in modo crescente o decrescente), si confronta la chiave di ricerca con l'emento centrale (M) dell'array
// se sono uguali, l'elemento é stato trovato
// se la chiave di ricerca é minore di M, la ricerca prosegue iterativamente nella prima metá di A
// se la chiave di ricerca é maggioredi M, la ricerca prosegue nella seconda metá di A

// Come funziona?
// Immagina di cercare un nome in un dizionario ordinato, non parti dalla prima pagina come nella ricerca seguenziale, ma:
// apri a metá
// confronti: se il nome che cerchi viene prima, guardi la metá sinistra, altrimento la metá destra
// ripeti dimezzando ogni volta finché trovi o finisci le possibilitá.
// Caratteristiche:
// FUNZIONA SOLO SU ARRAY ORDINATI (crescente o decrescente).
// molto piú: dimezza lo spazio di ricerca a ogni passo.
// complessitá:
// tempo: O(log2n)
// tempo: O(1) (se implementata in modo iterativo).

// inizio = 0
// fine = n-1

// mentre inizio <= fine:
// medio = (inizio + fine) / 2
// se A[medio] == chiave:
// restituisci medio
// se A[medio] < chiave:
// inizio = medio + 1
// altrimenti:
// fine = medio - 1

// restituisci -1 (non trovato)
int ricerca_binaria(int arr[], int n, int chiave)
{
    int inizio = 0;
    int fine = n - 1;

    while (inizio <= fine)
    {
        int medio = (inizio + fine) / 2;

        if (arr[medio] == chiave)
            return medio; // trovato

        if (arr[medio] < chiave)
            inizio = medio + 1; // cerca a destra
        else
            fine = medio - 1; // cerca a sinistra
    }
    return -1; // non trovato
}

int main()
{
    int numeri[] = {10, 20, 30, 40, 50};
    int n = 5;
    int chiave = 30;

    int pos = ricerca_binaria(numeri, n, chiave);

    if (pos != -1)
        printf("Elemento trovato in posizione %d\n", pos);
    else
        printf("Elemento non trovato\n");

    return 0;
}

// ========================================
// DIFFERENZE DICOMOTICA - SEGUENZIALE
// ========================================
// RICERCA SEGUENZIALE -> semplice, funziona sempre, ma lenta O(n)
// RICERCA DICOMOTICA -> velocissima O(log n), ma richiede l'array ordinato

// ========================================
// COSA SIGNIFICANO 0(n) E 0(log n)
// ========================================
// BIG-O (complessitá computazionale)
// Questa notazione é un modo per descrivere quanto tempo (o memoria) un algoritmo richiede in funzione della dimensione dei dati in ingresso
// - non misura i secondi reali o i cicli della CPU
// Serve per confrontare algoritmi in modo astratto, guardando come cresce il costo al crescere della dimnesione dei dati

// O(n) -> crescita lineare
// O(log n) -> crescita logaritmica

// ====================
// Ricorsione
// ====================
// La ricorsione é quando una funzione chiama se stessa per risolvere un problema piú piccolo. In altre parole,  divido il problema in versioni piú semplici dello stesso provllema dino a raggiungere un caso base che sai
// risolvere direttamente
// 2. Metafora intuitiva
// Immagina una scatola dentro un’altra scatola dentro un’altra scatola, e così via.
// La tua regola: “apri la scatola, se dentro c’è un’altra scatola, apri anche quella, altrimenti prendi l’oggetto.”
// Ogni scatola è un passo della funzione ricorsiva.
// Quando trovi la scatola finale → caso base → la funzione smette di chiamarsi.

// VANTAGGI E SVANTAGGI
// Dato un certo un problema, na soluzione che faccia uso di una funzione ricorsiva
// VANTAGGI:
// É intuitamente piú semplice da concepire
// Minor numero di linee di codice

// SVANTAGGI
// consuma molta memoria
// consuma molto tempo rispetto ad una soluzione iterativa

// Il consumo di memoria é dobuto alla locazione dei record di attivazione dello stack dovuta alla seguenza di chiamate ricorsive, una dopo l'altra
// Il consumo di tempo `e dovuto all’allocazione dei record sullo stack, la copia dell’indirizzo di ritorno e della variabili locali.

// Qualsiasi funzione ricorsiva si puó sempre esprimere in forma non ricorsiva.
// 1) Ricorsione di coda: la chiamata ricorsiva é l'ultima azione della funzione ricorsiva
// 2) Ricorsione non di coda: la ricorsione puó essere elimita con l'ausilio di uno stack esterno
