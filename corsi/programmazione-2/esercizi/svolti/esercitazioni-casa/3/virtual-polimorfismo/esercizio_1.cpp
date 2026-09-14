/* Esercizio 1 (base): Crea una classe base Forma con un metodo virtual descrizione() che stampa "Sono una forma". 
Derivane Cerchio e Rettangolo, ognuna ridefinisce descrizione() con override stampando le proprie misure. Crea un array di tre puntatori a Forma, assegna oggetti di tipo diverso e chiama descrizione() su tutti — verifica il dispatch dinamico. 
Aggiungi messaggi nei costruttori e distruttori per verificare l'ordine. */
#include <iostream>

using namespace std;

class Forma
{
public:
    Forma() { cout << "Costruttore: Forma" << endl; }
    virtual ~Forma() { cout << "Distruttore: Forma" << endl; }

    virtual void descrizione()
    {
        cout << "Sono una forma" << endl;
    }
};

class Cerchio : public Forma
{
public:
    Cerchio() { cout << "Costruttore: Cerchio" << endl; }
    ~Cerchio() override { cout << "Distruttore: Cerchio" << endl; }

    void descrizione() override
    {
        Forma::descrizione();
        cout << "Un Cerchio" << endl;
    }
};

class Rettangolo : public Forma
{
public:
    Rettangolo() { cout << "Costruttore: Rettangolo" << endl; }
    ~Rettangolo() override { cout << "Distruttore: Rettangolo" << endl; }

    void descrizione() override
    {
        Forma::descrizione();
        cout << "Un Rettangolo" << endl;
    }
};

int main()
{
    Forma* array[3];
    array[0] = new Forma();
    array[1] = new Cerchio();
    array[2] = new Rettangolo();

    for(int i = 0; i < 3; i++)
    {
        array[i]->descrizione();
        cout << endl;
    }
}