#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    // Una stringa di caratteri memorizzati in celle di memoria adiacenti (array)
    char s1[] = {'m', 'a', 'r', 'i', 'o', '\0'}; // CORRETTO
    char s2[] = {'m', 'a', 'r', 'i', 'o'};       // SBAGLIATO, le funzioni strlen() che operano su array di caratteri non potranno identificare la fine della stringa

    // Array di caratteri inizializzati mediante lista di inizializzatori: necessita il carattere finale null terminator ('\0') anche detto carattere 'null'

    char s[] = "my_string"; // corretto
    char *ps = "my_string"; // dovrebbe essere const, poiché é un puntatore ad array di caratteri, in quanto il ocmpilatore memorizza il letterale in locazione di memoria (read-only) e conserva il puntatore

    // ACCESSO IN SCRITTURA AD ELEMENTO DI PS DARÁ ERRORE A TEMPO DI ESEECUZIONE

    // é buona norma scrivere il qualificatore const
    const char *ps1 = "my_string"; // corretto
    ps1[3] = 'k';                  // il compilatore dará errore
    // Qualsiasi tentativo di accesso in scrittura ad elemento dello array di caratteri dará errore di compilazione
    // il qualificatore const obbliga al programmatore a scrivere codice "safe"

    // FUNZIONI DELLA LIBRERIA STANDARD PER ARRAY DI CARATTERI
    // copia di stringhe
    char name[15];
    strcpy(name, "pippo");
    // copia la stringa source nell'area di memoria puntata da destination

    // confronto lessicografico
    strcmp("pippo", "paperino"); // restituisce un int > 0;
    strcmp("paperino", "pippo"); // restituisce un int < 0;
    strcmp("pippo", "pippo");    // restituisce 0;
    // NON USARE MAI S1 == S2 per confrontare due caratteri "MAI"

    // Confronto lessicografico "lengh-bounded": imita il confronto ai primi count caratteri
    int strncmp(const char *lhs, const char *rhs, size_t count);

    // Copia di stringhe versione "lengh-bounded": copia i primi count caratteri di src nell'area puntata da dest.
    char *strncpy(char *dest, const char *src, size_t count);

    // Ricerca di sottostringhe
    const char *strstr(const char *str1, const char *str2);
    char *strstr(char *str1, const char *str2);

    char s2[] = "CesareGiulio";
    char *found = strstr(s, "are");
    printf("%s", found); // output: areGiulio
    // La funzione strstr restituisce un puntatore al primo carattere della prima occorenza di str2 trovata in str1

    // Conversione di stringhe a interi
    // Se stringa non rappresenta un numero atoi/atol/atoll potrebbe
    // Restituire la conversione dei primi caratteri della stringa, se questi rappresentano un numero ES: per la stringa "22aabb" restitiurebbe 22
    int atoi(const char *str);
    long atol(const char *str);
    long long atoll(const char *str);

    // restituire zero se la stringa non inizia con un numero, in qeusto caso non é possibile distinguere il caso "0" dagli altri casi...

    // CONVERSIONI NUMERICHE: ARRAY DI CARATTERI --> TIPO NUMERICO
    // Famiglia di funzioni strtoX (float/double)
    long strtol(const char *nptr, char **endptr, int base);
    double strtod(const char *nptr, char **endptr);
    float strtof(const char *nptr, char **endptr);
    long double strtold(const char *nptr, char **endptr);

    // Caratteristca
    // resitituisce il valore riconosciuto nella stringha rappresentata da nptr;
    // pone nel secondo argomento (puntatore a puntatore). l'indirizzo di una cella che contiene il puntatore al primo carattere non usato nella conversione
    // é possibile riconoscere il caso a cui nessuna conversione sia avvenuta, basta controllare che *endptr==nptr

    // funzione sscanf() piú "sofisticata": permette di estrarre piú di un elemenmto (non solo numeri) alla volta.
    int sscanf(const char *buffer, const char *format, ...);
    // Ricerca di elementi (stringhe e numeri) da estrarre da una stringa (contenuta nell'argomento buffer) sulla base di pattern definiti nel secondo argomento (format);
    // Salvataggio nelle aree di memoria specificare nella lista variabile di parametri dopo il secondo argomento


    // LETTURA DI UN NUMERO
    int x;
    const char *str = "1234";
    sscanf(str, "%d", &x);

    // conmportamento analogo alla funzione atoi/I/II(): se uno piú carateri a inizio stringa sono validi la funzione restituisce la loro conversione.
    // ES: "12aa34" sscanf() resituirá il numero 12


    // LETTURA DI UN NUMERO IN VIRGOLA MOBILE
    float y;
    double x1;
    const char *str = "1234.567899012345";
    sscanf(str, "%f", &y); // sscanf(string-scan formatted) é come scanf, ma invece di leggere da tastiera legge da una stringa di testo giá esistente in memoria
    // str é una variabile di tipo const char * che contiene il testo da cui vogliamo estrarre un numero


    //TIPO NUMERICO --> STRINGA

    int sprintf(char *buffer, const char *format, ...);
    // scrive una stringa (cioé nell'array buffer) i dati formattati secondo la stringa di formato 
    // format, in modo simile a come printf scrive sullo schermo

}