/* Esercizio 1 (medio): Aggiungi costruttore di copia e operator= alla classe ArrayDinamico dell'esercizio precedente.
Testa che modificare la copia non modifichi l'originale, sia con costruttore di copia che con operator=. */
#include <iostream>
using namespace std;
class ArrayDinamico
{
private:
    int dimensione;
    int *array_dinamico;

public:
    ArrayDinamico(int d) : dimensione(d), array_dinamico(new int[dimensione])
    {
        for (int i = 0; i < dimensione; i++)
        {
            array_dinamico[i] = 0;
        }
    }
    ~ArrayDinamico()
    {
        delete[] this->array_dinamico;
        
        cout << "Memoria liberata" << endl;
    }

    ArrayDinamico(const ArrayDinamico &d) : dimensione(d.dimensione), array_dinamico(new int[d.dimensione])
    {
        for (int i = 0; i < dimensione; i++)
        {
            array_dinamico[i] = d.array_dinamico[i];
        }
    }

    ArrayDinamico &operator=(const ArrayDinamico &d)
    {
        if (this == &d)
        {
            return *this;
        }

        delete[] array_dinamico;

        dimensione = d.dimensione;

        array_dinamico = new int[d.dimensione];
        for (int i = 0; i < dimensione; i++)
        {
            array_dinamico[i] = d.array_dinamico[i];
        }

        return *this;
    }

    // setter
    void set_array(int indice, int valore)
    {
        if (indice >= 0 && indice < this->dimensione)
        {
            this->array_dinamico[indice] = valore;
        }
    }
    // getter
    int get_array(int indice)
    {
        if (indice >= 0 && indice < this->dimensione)
        {
            return this->array_dinamico[indice];
        }
        else
        {
            cerr << "Errore indice non valido" << endl;
            return -1;
        }
    }
};

int main()
{
    // 1. Creazione e inizializzazione dell'originale
    ArrayDinamico a(3);
    a.set_array(0, 10);
    a.set_array(1, 20);
    a.set_array(2, 30);

    // 2. Copia tramite costruttore di copia
    // 'b' riceve una copia esatta dei valori di 'a' in una nuova area di memoria
    ArrayDinamico b = a;

    // 3. Copia tramite operatore di assegnazione
    ArrayDinamico c(1); // creato inizialmente con dimensione 1
    c = a;              // la memoria di c viene liberata e riallocata per ospitare i valori di a

    // Verifica dei contenuti
    cout << "--- Contenuto degli array ---" << endl;
    cout << "Array A: " << a.get_array(0) << ", " << a.get_array(1) << ", " << a.get_array(2) << endl;
    cout << "Array B: " << b.get_array(0) << ", " << b.get_array(1) << ", " << b.get_array(2) << endl;
    cout << "Array C: " << c.get_array(0) << ", " << c.get_array(1) << ", " << c.get_array(2) << endl;
    return 0;
}