#include <stdio.h>
#include <string.h>

// ====== Struttura precedente (record “base”) ======
typedef struct {
    char nome[30];
    int valore;
} Record;

// ====== Nuova struttura annidata ======
typedef struct {
    int ID;         // deve essere positivo, -1 se “vuoto”
    Record info;    // struct annidata
} Data;

// ====== Prototipi ======
void initRecord(Record *r);
void initData(Data *d, int id);

// --------------------------------------------------
int main(void) {
    const int N = 5;          // dimensione dell’array
    Data array[N];

    // k elementi da inizializzare
    int k = 3;                // puoi cambiare a piacere
    for (int i = 0; i < k; i++) {
        initData(&array[i], i + 1);   // ID univoci da 1 in su
    }

    // Gli elementi successivi a k li marchiamo con ID = -1
    for (int i = k; i < N; i++) {
        array[i].ID = -1;
    }

    // ----- Stampa per verifica -----
    for (int i = 0; i < N; i++) {
        if (array[i].ID == -1) {
            printf("[%d] elemento vuoto (ID = -1)\n", i);
        } else {
            printf("[%d] ID=%d  Nome=%s  Valore=%d\n",
                   i, array[i].ID,
                   array[i].info.nome,
                   array[i].info.valore);
        }
    }

    return 0;
}

// ====== Funzioni di inizializzazione ======

// Inizializza il “record base” con dati fittizi
void initRecord(Record *r) {
    // Qui puoi leggere da input o assegnare a caso
    snprintf(r->nome, sizeof(r->nome), "Elemento");
    r->valore = 42;
}

// Inizializza un singolo Data, assegnando ID univoco
void initData(Data *d, int id) {
    d->ID = id > 0 ? id : 1;   // garantiamo ID positivo. Condzione id > 0, se é vera usa id, se é falsa usa 1
    initRecord(&d->info);
}
