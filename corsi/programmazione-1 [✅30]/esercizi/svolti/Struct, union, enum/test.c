#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Le strutture sono molto usate nel linguaggio C definite mediante la keyword struct
// Una struttura é un tipo composto di un insieme di dati (comunamente chiamato record)
// La struct in C é l'antenato della classe in C++
// Queste é una struct
struct record
{
    char *nome;
    char *cognome;
    float saldo;

} s1, s2; // definisce il tipo struct record e variabili s1, s2 dello stesso tipo

// PUNTATORI A STRUTTURE, STRUTTURE AUTOREFERENZIALI
// La strutture non puó contenere una variabile dello stesso tipo della struttura, ma puó contenere un puntatore alla struttura stessa
struct record1
{
    char *nome;
    char *cognome;
    float saldo;
    struct record1 *next; // Puntatore a strutture dello stesso tipo utile a creare stutture dati collegate!
};

// CONFRONTO DI STRUTTURE
// Vanno confrontati i membri, singolarmente. Non é possibile confrontare due variabili dello stesso tipo struct con gli operatori "==" e "!="
// in quanto alcuni campi della struttura potrebbero essere allineati ad una word di memoria pur essendo piú piccoli della word stessa
// ESEMPIO
struct record2
{
    char c; // 1 byte ma (probabilmente) allineato a 4 byte
    int k;  // 4 byte
    // Il carattere potrebbe essere cointenuto in una word di 4 byte, anche se viene sato solo un byte
};

// ACCESSO AI DATI, OPERATORE "NARROW" (- >)
struct record3
{
    float x;
    float y;
};

// PUNTATORI A FUNZIONI E STRUTTURE
struct record4
{
    float x, y;
    float (*sum)(struct record4 *ptr);
};

float sum_func(struct record4 *ptr) // la funzione riceve come argomento un puntatore a una struttura di tipo struct struttura
{
    return ptr->x + ptr->y;
    // ptr->x e ptr->y accedo ai campi x e y del record4 a cui punta ptr
}

/// USO DELLA PAROLA TYPEDEF
// la parola typedef permette di creare alias di dati precedentemente definiti (anche tipi primitivi)
typedef struct record5
{
    float x;
    float y;
} srec; // nuovo tipo equivalente a record5

srec myrecord;    // crea una variabile chiamata myrecord di tipo srec(cioé struct record5) contiene direttamente i campi x e y
srec *ptr_record; // dichiara un puntatore a srec chiamato *ptr_record al momento non punta nulla dovró assegnargli l'indirizzo di una variabile srec o allocare la memoria

// ENUMERAZIONI (ENUM)
// Enum crea un tipo con una serie di constanti intere, usa virgole per separare i nomi e non i punti e virgola
enum Mese     // diventa un nuovo tipo i cui valori possibili sono costanti elencate
{             // per default hanno valori:
    Gennaio,  // 0
    Febbraio, // 1
    Marzo,    // 2
    Aprile,
    Maggio,
    Giugno,
    Luglio,
    Agosto,
    Settembre,
    Ottobre,
    Novembre,
    Dicembre // 11..
};

enum Mese m = Gennaio; // dichiara una variabile m di tipo enum MEse la inizializza al valore costante Gennaio (che in realtá corrisponde al numero 0 se non ho cambiato nulla)
// i nomi definiti in una enum "sono esportati" nella scope in cui la enumerazione é stata indefinita

// I nomi di una enumerazione sono rappresentati in memoria come numeri interi, i cuui valori, se non sono specificati dal programmatore partono da zero
// conversioni int->enum o enum->int sono entrambe valide

m = Dicembre;
// Queste due istruzioni fanno riferimento a due "nomi" definiti nella enumerazione
enum Mese m2 = 10; // OK m2 = Novembre
int mese = m2;

// LE ENUMERAZIONI INOLTRE POSSONO ESSERE USATE PURE NEI COSTRUTTI SWITCH
const char *traduci_mese(enum Mese m) // la funzione restituisce un puntatore a carattere constante, cioe l'indirizo di una stringa letterale
// costante significa che il chiamante non deve modificare il contenuto della stringa
{
    switch (m)
    {
    case Gennaio:
        return "Gennaio";
        break;
    case Febbraio:
        return "Febbraio";
        break;
    default:
        break;
    }
}

// SCOPE VS ENUMERAZIONI
// Compile-time error! name clash
// Questo succede perché? Per il semplice motivo che i nomi di una enum diventano globali, cioé visibili in tutto il file sorgente
// Allora gli identificatori scritti al suo interno se giá sono presenti nel file dará errore
// Cosa significa SCOPE? significa ambito di visibilitá: l'aera del programma in cui un nome (variabile, costante, funzione ecc..) é conosciuto e puó essere usato
/* enum MeseEstivo
{
    Giugno,
    Luglio,
    Agosto
}; */

// SCOPE VS RAPPRESNETAZIONI DELLE ENUMERAZIONI
enum MeseInvernale
{
    Dicembre, // 0
    Gennaio,  // 1
    Febbraio  // 2
};

enum MeseEstivo
{
    Giugno, // 0
    Luglio, // 1
    Agosto  // 2
};

// Per default abbiamo visto che i valori corrispondenti alle enumerazioni partono da zero, ma il programmaztore puó specificarli.
// Dopop ogni valore specificato perun simbolo, il successivo (se non specificato dal programmatore), viene assegnato sulla base del valore precendente

enum Mese1
{
    Gennaio1,       // 0
    Febbraio1 = 20, // 20
    Marzo1,         // 21
    Aprile1,        // 22
    Maggio1,        // 23
    // etc..
}

// UNION
// Una union é una struttura i cui membri sono allocati tutti a partire dallo stesso indirizzo di memoria
// Lo spazio realmente occupato in memoria sará uguale alla dimensioni del campo piú grande
// Di conseguenza tale struttura potrá contenere non piú di un dato alla volta
union Value
{
    char c;
    int num;
};

// Il record puó essere un carattere oppure un numero
// La struttura di tipo union consente di risparmiare spazio in memoria
// La memoria totale é circa sizeof(char) + sizeof(int) puó scirvere e leggere entrambi i campi indipendentemente v.c e v.num contengano valori separati
// Tutti i campi partono dallo stesso indirizzo di memoria, c e num si sovrappongono fisicamente nella RAM ció significa che c'é un unico blocco di memoria

//  ESEMPIO PRATICO
// Se assegno un valore a uno dei membri, sto modificando quell'unico blocco 
// union Value v;

// v.c = 'A';       // scrive il byte della lettera 'A' nella memoria
// printf("%c\n", v.c);   // stampa 'A'
// printf("%d\n", v.num); // interpreta gli stessi byte come un int → valore “spazzatura” o imprevedibile

// v.num = 1000;    // ora i 4 byte contengono la rappresentazione binaria di 1000
// printf("%d\n", v.num); // stampa 1000
// printf("%c\n", v.c);   // interpreta il primo byte di quei 4 come un char → carattere casuale

// Qui si vede che posso tenere in memoria solo "un significato alla volta", o uso il campo c oppure uso il campo num
// non posso pretendere che entrambi abbiano conteporaneamente un valore "sensato"

// PERCHÉ USARLA?
// risparmio dello spazio: ad esempio una variabile puó essere, a seconda del caso, un numere o un carattere, ma mai tutti e due nello stesso momento
// implementazioni di varianti, protocolli, pacchetti di rete etc.. dove la stssa area di memoria va interpretata in modi diversi a seconda del tah

// Una union é come avere un solo cassetto con piú etichette possibili (c o enum) posso mettere dentro un oggetto alla volta: se cambio etichetta senza cambiare contenuto, 
// sto solo guardando lo stesso cassetto con un'ottica diversam e il risultato puó non avere un senso


int main()
{

    // UNION
    union Value v;
    v.c = 'c';
    v.num = 10;

    enum MeseInvernale m = Dicembre;
    if (m == Giugno) // Attenzione! per default non verrá dato nessun warning
    {
        /* code */
    }

    // INIZLIZZAZIONE DI STRUTTURE
    // puó avvenire:
    // 1) con una lista di inizializzazione ed eventuale uso di "disegnatori"
    /* struct stuttura s1 = {}; */
    struct record1 s2 = {"mario", "rossi", 123.45};
    /* struct stuttura s2 = {.cognome = "mario", .nome = "rossi", .saldo = 123.45}; */

    // 2) oppure dopo la deinizione con l'operatore "punto" '.'
    s1.nome = "Elena";
    s1.cognome = "Bianchi";
    s1.saldo = 345.67;

    struct record3 *rec = (struct record3 *)malloc(sizeof(struct record3)); // *rec dichiara rec come puntatore a struct record
    // malloc(sizeof(struct record3)) alloca dinamicamente un blocco di memoria grande abbastanza per contenere struct record3
    // Risultato: rec ora punta a una zona di memoria appena riservata che conterrà una struct record3.
    rec->x = 0.3;
    rec->y = 0.7;

    struct record4 rec1;         // ccrea una variabile rec di tipo struct record, non é un puntatore é l'oggetto vero e proprio
    rec1.x = rec1.y = 0.9;       // assegna 0.9 a x e y
    rec1.sum = sum_func;         // associa la funzione al puntatore
    float sum = rec1.sum(&rec1); // chiama la funzione puntata da rec.sum, passando l'indirizzo di rec (&rec) come argomento
}