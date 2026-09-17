// Variabile static
#include <stdio.h>

// main.c
void foo()
{
    static int foo_calls = 0;
    foo_calls++;
    printf("foo_calls: %d", foo_calls);
}

// La variabile static viene allocata con la prima chiamata a funzione
// La variabile static veien deallocata solo alla fine del programma
// La variabile static foo_calls viene inizializzata solo alla prima invocazione di funzione

// bar.c
void bar()
{
    foo(); // ERORRE
}
// La funzione static potrá essere invocata solo da codice appartenente allo stesso file sorgente (translation unit), in alte parole, la visibilitá ella funzione non sará piú hlobale ma "locale"
// alle sole funzioni presenti nel suo modulo sorgente

// EXTERN, funzione (non static) che é definita in un altro file sorgente
// main.c
extern void foo();
// La dichiarazione dei prototipi avviene nei file header, anche se si inserisce extern, il compilatore "assume" che la funzione sia extern

// VARIABILI EXTERN
extern int var;

//INLINE
int sum (int a, int b)
{
    return a+b;
}
// il vantaggio evidente dell'uso delle funzioni é il riuso del codice e la modularitá, tuttavia le chiamate a funzioni costose in termini di tempo e cpu
// L'introduzione della keyword "inline" C/C++:
// 1) permette al programmatore di "suggerire" al compilatore di sostituire le chiamate ad una certa funzione con il corpo della funzione stessa
// 2) alternativa all'uso di macro (preprocessore)
// 3) C e C++ differiscono nell'interpretazione della keyword "inline";
// I compilatori scelgono di efettuare "inlining" del corpo della fuzione indipendentemente dai suggerimenti del programmatore per ottenere codice piú veloce

// ======================
// MACRO (PREPROCESSORE)
// ======================
#define inc(i) (i+1)
// é un esempio molto sem0plice diu macro con parametri, cioé un'istruzione del preprocessore in C
// COSA É IL PREPROCESSORE?
// Il preprocessore in C é una specie di "segretario" che lavora prima del compilatore vero e proprio, il suo compito é leggere il codice sorgente e trasformarlo, applicando regole e direttive che iniziano con #

// Cosa fa davvero questa macro?
// Il preprocessore, prima della compilazione, sostituisce ogni occorrenza di inc(x) con (x+1) quindi;
// se scrivo -->
int a = 3;
int b = inc(a); // inc(a+1)

// Le inline function hanno lo stesso scopo di velocizzare piccole operazioni ma sono molto piú sicure e gestite dal compilatore
// ============================================
// Semantica (C) della keyword inline
// ============================================
// Si suggerisce al compilatore di sostituire la chiamata alla funzione con il corpo stessa
// dato che la funzione é inline, la sua implementazione non viene passata al linker (colui che unisce tutto il codice in un'unico eseguibile), Quindi:
// 1) nel caso il compilatore non decida di sostituire la chiamata a funzione con l'implementazione inline suggerita dal programmatore, il compilatore produrrá una apposita chiamat
// 2) il linker produrrá un errore: undefined reference to function..
// Di conseguenza, va usata la keyword static per "forzare" il compilatore a usare, all'interno del modulo, la definizione inline della funzione


// ============================================
// COSA FA QUESTA KEYWORD?
// ============================================
// In C inline é un suggerimento al compilatore, Ehi, questa funzione é piccola e usata spesso, invece di fare la solita chiamata a funzione copia direttamente il corpo dentro il chiamante
// Immagina di avere dei post-it con una formula che uso spesso, senza inline ogni volta che mi serve vado a cercare quel post-it nel cassetto (chiamata a funzione)
// con inline copio la formula direttamente accanto l'esercizio che sto facendo (il compilatore incolla il codice al posto della chiamata)

//DIFFERENZE CON LE MACRO
// macro copia e incolla ciechi del preprocessore (il preprocessore si dice che é cieco, quando vede una macro fa la sostituzione testuale, non capisce nulla dei tipi, logica o semantica del C)
// inline é codice vero, con controllo dei tipi, debugging corretto

inline int inc(int i)
{
    return i+1;
}

int main()
{
    foo(); // call to global function foo()
    bar();

    // una variabile definite fuori dalle funzioni avrá visibilita globale. Tuttavia va dichiarata con la parola chiave extern in ogni modulo diverso da quello in cui la variabile stessa é definita
    // main.c
    int x = var*3;
    

    //zoo.c
    int var = 10; // dichiarazione e definizione

    //main.c
    extern int var; // solo dichiarazione
    // In assenza della dichiarazxione extern int var, il compilatore produrebbe un errore, Nella pratica, la dichiarazione di tali variabili extern andrebbe nei file header.
    // (La dichiarazione di una variabile extern non implica allocazione di memoria)

    
}

// zoo.c
int var = 10;
void zoo()
{
    int a = var * 2;
}
