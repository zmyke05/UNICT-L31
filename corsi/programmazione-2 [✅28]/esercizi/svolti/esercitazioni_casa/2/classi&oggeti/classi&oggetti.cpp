/* Esercizio 3 (avanzato): Crea una classe ArrayDinamico con un array di interi allocato dinamicamente. Il costruttore prende la dimensione, il distruttore libera la memoria.
Aggiungi metodi set(int indice, int valore) e get(int indice) con controllo dei bounds (indice valido). Testala nel main. */
#include <iostream>
using namespace std;
class ArrayDinamico
{
private:
    int *array_dinamico;
    int dimensione;

public:
    ArrayDinamico(int d)
    {
        dimensione = d;
        array_dinamico = new int[dimensione];
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
    // setter
    void set_array(int indice, int valore)
    {
        if (indice > 0 && indice < this->dimensione)
        {
            this->array_dinamico[indice] = valore;
        }
    }
    // getter
    int get_array(int indice)
    {
        if (indice > 0 && indice < this->dimensione)
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
    int dimensione = 10;
    ArrayDinamico array(dimensione);
    for (int i = 0; i < dimensione; i++)
    {
        array.set_array(i, i * 2);
    }
    cout << endl;
    for (int i = 0; i < dimensione; i++)
    {
        cout << array.get_array(i) << "\t";
    }
    cout << endl;
}