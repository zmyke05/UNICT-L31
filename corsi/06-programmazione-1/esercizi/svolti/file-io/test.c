#include <stdio.h>
// Un file é una seguenza di bytes. con tale astrazione si possono memorizzare dati su vari supporti in modo permanente(hard-disk etc..)
// i file in C vanno manipolati con le funzioni della libreria standard che operano su stream (flussi)

// APERTURA DI UN FILE -> si usa la funzione fopen() con opportuni argomenti: FILE *fopen(const char *filename, const char *mode)
// le varie modalitá di apertura:
// 1) r (lettura)
// 2) w (scrittura)
// 3) a (append) scrittura, se il file esiste aggiunge bytes in coda, invece se il file non esiste ne viene creato uno nuovo
// 4) r+ o w+ lettura e scrittura, ma nel secondo case se il file non esister ne verrá creato uno nuovo
// la funzione fopen() restituisce un puntatore ad un tipo FIL

// CHIUSURA DI UN FILE -> dopo opportune operazioni di lettura/scrittura il comando é int fclose(FILE *stream)
// permette di liberare risorse dal sistema operatoivo
// infatti un ssistema operativo mette a disposizione un numero di file limitato, per tutte le applicazioni, quindi é necessario chiudere il file quando questo non serve piú
// L'invocazione di fclose() provoca l'invocazione automatica di fflush() fa in modo che eventuali byte rimasti in memoria (buffer, dati temporanei) a seguito di operazioni di scrittura vengano scaricati su file

// IO a caratteri su file
//  int fprintf(FILE *restrict stream, const char *restrict format, ...);
//  int fscanf(FILE *restrict stream, const char *restrict format, ...);
//  char *fgets(char *restrict s, int size, FILE *restrict stream);
//  int fputs(const char *restrict s, FILE *restrict stream)
// La funzione fscanf() non memorizza il carattere newline contrariamente a fgets()
// Inoltre la funzione fscanf() prova a leggere "token" che andranno memorizzati all'interno di opportune variabili rappresentate da parametri attuali. mentre la funzione fgets() legge una seguenza di al piú s caratteri
// piazzandoli in un buffer(variabile temporanea)
// ESEMPIO
int main()
{
    // Scrivere informazioni all'interno di un file con la funzione fprintf()
    FILE *fp = fopen("a.txt", "r");
    if (fprintf())
    {
        
    } 
}
