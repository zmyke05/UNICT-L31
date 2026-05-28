/* Esercizio 3 (avanzato): Crea due interfacce pure: Comparable con metodo puro confronta(const Comparable&) const che restituisce -1, 0, o 1, e Stampabile con metodo puro stampa() const.
Crea una classe astratta Prodotto che implementa entrambe le interfacce, con attributi nome (string) e array dinamico prezzi_storici (Regola del Tre completa) e metodo puro categoria() const.
Da Prodotto deriva Elettronico (aggiunge garanzia_mesi) e Alimentare (aggiunge data_scadenza come string).
Entrambe implementano confronta() sul prezzo più recente, stampa() con tutte le info, e categoria().
Crea un array polimorfico di Prodotto*, implementa una funzione ordina(Prodotto** arr, int n) che usa confronta() per ordinare l'array con bubble sort. Stampa l'array prima e dopo l'ordinamento. */
#include <iostream>

using namespace std;

class Comparable
{
public:
    Comparable() {}
    virtual ~Comparable() {}

    virtual int confronta(const Comparable &) const = 0;
};

class Stampabile
{
public:
    Stampabile() {}
    virtual ~Stampabile() {}

    virtual void stampa() const = 0;
};

class Prodotto : public Comparable, Stampabile
{
private:
    string nome;
    int num_prezzi;
    int capacita_massima;
    double *prezzi_storici;

public:
    Prodotto(const string &nome, const int num_prezzi, const int capacita_massima, const double *prezzi_storici) : nome(nome), num_prezzi(num_prezzi), capacita_massima(capacita_massima), prezzi_storici(new double[num_prezzi])
    {
        if (prezzi_storici == nullptr)
            this->num_prezzi = 0;

        if (this->num_prezzi > capacita_massima)
            this->num_prezzi = this->capacita_massima;

        for (int i = 0; i < num_prezzi; i++)
            this->prezzi_storici[i] = prezzi_storici[i];
    }

    // Regola del tre
    // - distruttore
    // costruttore copia
    // overloding con operator=
    ~Prodotto() override
    {
        delete[] prezzi_storici;
    }

    Prodotto(const Prodotto& altro)
    {
        this->nome = altro.nome;
        this->num_prezzi = altro.num_prezzi;
        this->capacita_massima = altro.capacita_massima;
        this->prezzi_storici = new double[this->capacita_massima];
        for(int i = 0; i < this->num_prezzi; i++)
        {
            this->prezzi_storici[i] = altro.prezzi_storici[i];
        }
    }


    Prodotto& operator=(Prodotto& altro)
    {
        if(this == &altro)
        {
            return *this;
        }

        this->nome = altro.nome;
        this->num_prezzi = altro.num_prezzi;
        this->capacita_massima = altro.capacita_massima;

        delete[] this->prezzi_storici;
        this->prezzi_storici = new double[this->capacita_massima];
        for(int i = 0; i < this->num_prezzi; i++)
        {
            this->prezzi_storici[i] = altro.prezzi_storici[i];
        }
        return *this;
    }

    // Metodi stampa() e confronta()
    int confronta(const Comparable& c) const override 
    {

    }

    void stampa() const override
    {
        
    }

    // Metodo puro categoria()
    virtual void categoria() const = 0;
};

class Elettronico : public Prodotto
{
public:
    /* Elettronico() {} */
    ~Elettronico() override {}
};

int main()
{
}