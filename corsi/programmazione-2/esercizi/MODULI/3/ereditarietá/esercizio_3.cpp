/* Esercizio 3 (avanzato): Crea una gerarchia Conto → ContoCorrente → ContoCorrente_Premium con questi requisiti:

Conto gestisce un array dinamico di double che rappresenta lo storico delle transazioni (usa la Regola del Tre completa). Ha metodi deposita(), preleva() (no saldo negativo), stampa_storico(). Ha un attributo static num_conti. Implementa operator<<.
ContoCorrente aggiunge limite_scoperto — preleva() permette saldo negativo fino al limite. Chiama Conto::preleva() se possibile, gestisce autonomamente solo il caso scoperto.
ContoCorrente_Premium aggiunge cashback_percentuale — ogni prelievo riuscito aggiunge automaticamente il cashback% dell'importo come deposito. Ridefinisce preleva() chiamando quello di ContoCorrente.

Verifica nel main:

Ordine di costruzione e distruzione
Copia tramite costruttore di copia (deep copy dello storico)
operator<< su tutti e tre i livelli
Tutti i casi limite: prelievo oltre saldo, prelievo oltre limite scoperto, cashback applicato correttamente
Il contatore static aggiornato correttamente */
#include <iostream>

using namespace std;

class Conto
{
private:
    double *storico;
    int num_transizioni;
    double saldo;
    int capacita_massima;
    static int num_conti;

protected:
    void aggiungi_transizione(double importo)
    {
        if (num_transizioni < capacita_massima)
        {
            storico[num_transizioni++] = importo;
        }
    }

public:
    // ALLOCAZIONE FISSA: allochiamo sempre in base a capacita_massima per evitare sfondamenti dell'array
    Conto(const double *storico, const int num_transizioni,
          const double saldo, const int capacita_massima)
        : storico(new double[capacita_massima]),
          num_transizioni(num_transizioni),
          saldo(saldo),
          capacita_massima(capacita_massima)
    {
        for (int i = 0; i < this->num_transizioni; i++)
            this->storico[i] = storico[i]; // sicuro solo se storico != nullptr
        num_conti++;
        cout << "[Conto] Costruttore" << endl;
    }

    virtual ~Conto()
    {
        delete[] storico;
        cout << "[Conto] Distruttore" << endl;
        num_conti--;
    }

    Conto(const Conto &altro)
    {
        this->num_transizioni = altro.num_transizioni;
        this->capacita_massima = altro.capacita_massima;
        this->storico = new double[this->capacita_massima]; // Allocazione corretta
        for (int i = 0; i < this->num_transizioni; i++)
        {
            this->storico[i] = altro.storico[i];
        }
        this->saldo = altro.saldo;
        num_conti++;
    }

    Conto &operator=(const Conto &altro)
    {
        if (this == &altro)
        {
            return *this;
        }

        delete[] storico;
        this->num_transizioni = altro.num_transizioni;
        this->capacita_massima = altro.capacita_massima;
        this->storico = new double[this->capacita_massima];
        for (int i = 0; i < this->num_transizioni; i++)
        {
            this->storico[i] = altro.storico[i];
        }
        this->saldo = altro.saldo;
        return *this;
    }

    // Metodo statico per leggere il contatore
    static int get_num_conti() { return num_conti; }

    void set_saldo(const double saldo) { this->saldo = saldo; }
    double get_saldo() const { return this->saldo; }
    int get_num_transizioni() const { return this->num_transizioni; }

    Conto &deposita(double importo)
    {
        if (importo <= 0)
            return *this;
        this->saldo += importo;
        aggiungi_transizione(importo);
        return *this;
    }

    virtual Conto &preleva(double importo)
    {
        if (importo <= 0)
        {
            cerr << "Importo non valido " << endl;
            return *this;
        }

        if (this->saldo - importo < 0)
        {
            cerr << "Saldo insufficiente " << endl;
            return *this;
        }

        this->saldo -= importo;
        aggiungi_transizione(-importo); // Segno meno per coerenza con i prelievi
        return *this;
    }

    void stampa_storico() const
    {
        cout << "Storico Transazioni (Saldo attuale: " << saldo << "):";
        for (int i = 0; i < this->num_transizioni; i++)
        {
            cout << "\n[" << i << "] Transazione: " << storico[i];
        }
        cout << endl;
    }

    friend ostream &operator<<(ostream &os, const Conto &c)
    {
        os << "Conto | Saldo=" << c.saldo
           << " | Transazioni: " << c.num_transizioni
           << "/" << c.capacita_massima;
        return os;
    }
};

// Inizializzazione della variabile statica obbligatoria in C++
int Conto::num_conti = 0;

class ContoCorrente : public Conto
{
private:
    double limite_scoperto;

public:
    ContoCorrente(const double *storico, const int num_transizioni, const double saldo, const int capacita_massima, const double limite_scoperto)
        : Conto(storico, num_transizioni, saldo, capacita_massima), limite_scoperto(limite_scoperto) { cout << "[ContoCorrente] Costruttore" << endl; }
    virtual ~ContoCorrente() { cout << "[ContoCorrente] Distruttore" << endl; }

    ContoCorrente(const ContoCorrente &altro)
        : Conto(altro), limite_scoperto(altro.limite_scoperto) {}

    ContoCorrente &operator=(const ContoCorrente &altro)
    {
        if (this == &altro)
            return *this;
        Conto::operator=(altro); // delega operator= della base
        limite_scoperto = altro.limite_scoperto;
        return *this;
    }

    double get_limite_scoperto() const { return this->limite_scoperto; }

    Conto &preleva(double importo) override
    {
        if (importo <= 0)
        {
            cerr << "Importo non valido" << endl;
            return *this;
        }

        // Se c'è saldo a sufficienza delega alla classe Base
        if (get_saldo() >= importo)
        {
            return Conto::preleva(importo);
        }

        // Gestione autonoma del caso "scoperto"
        if (get_saldo() - importo >= -limite_scoperto)
        {
            set_saldo(get_saldo() - importo);
            aggiungi_transizione(-importo);
            return *this;
        }

        cerr << "Limite scoperto superato" << endl;
        return *this;
    }

    // Solo dichiarazione friend, nessun corpo vuoto qui!
    friend ostream &operator<<(ostream &os, const ContoCorrente &c);
};

ostream &operator<<(ostream &os, const ContoCorrente &c)
{
    os << static_cast<const Conto &>(c)
       << " | Limite scoperto: " << c.limite_scoperto;
    return os;
}

class ContoCorrente_Premium : public ContoCorrente
{
private:
    double cashback_percentuale;

public:
    ContoCorrente_Premium(const double *storico, const int num_transizioni, const double saldo, const int capacita_massima, const double limite_scoperto, const double cashback_percentuale)
        : ContoCorrente(storico, num_transizioni, saldo, capacita_massima, limite_scoperto), cashback_percentuale(cashback_percentuale) { cout << "[ContoCorrente_Premium] Costruttore" << endl; }
    virtual ~ContoCorrente_Premium()
    {
        cout << "[ContoCorrente_Premium] Distruttore" << endl;
    }

    ContoCorrente_Premium(const ContoCorrente_Premium &altro)
        : ContoCorrente(altro), cashback_percentuale(altro.cashback_percentuale) {}

    ContoCorrente_Premium &operator=(const ContoCorrente_Premium &altro)
    {
        if (this == &altro)
            return *this;
        ContoCorrente::operator=(altro);
        cashback_percentuale = altro.cashback_percentuale;
        return *this;
    }

    double get_cashback_percentuale() const { return cashback_percentuale; }

    Conto &preleva(double importo) override
    {
        double saldo_prima = get_saldo();
        ContoCorrente::preleva(importo);

        if (get_saldo() != saldo_prima)
        {
            double cashback = importo * (cashback_percentuale / 100.0);
            deposita(cashback);
            cout << "[Premium System] Cashback applicato: +" << cashback << " euro" << endl;
        }
        return *this;
    }
};

ostream &operator<<(ostream &os, const ContoCorrente_Premium &c)
{
    os << static_cast<const ContoCorrente &>(c)
       << " | Cashback: " << c.get_cashback_percentuale() << "%";
    return os;
}

int main()
{
    double storico_vuoto[] = {};

    cout << "=== Creazione conti ===" << endl;
    Conto c1(nullptr, 0, 1000.0, 10);
    ContoCorrente cc1(storico_vuoto, 0, 500.0, 10, 200.0);
    ContoCorrente_Premium ccp1(storico_vuoto, 0, 800.0, 10, 300.0, 5.0);

    // Richiamo corretto del metodo statico
    cout << "Conti attivi in memoria: " << Conto::get_num_conti() << endl;

    cout << "\n=== Depositi ===" << endl;
    c1.deposita(500);
    cc1.deposita(200);
    ccp1.deposita(100);

    cout << "\n=== Prelievi ===" << endl;
    c1.preleva(200);    // ok
    c1.preleva(99999);  // saldo insufficiente
    cc1.preleva(600);   // ok — usa limite scoperto
    cc1.preleva(99999); // limite superato
    ccp1.preleva(100);  // ok — cashback applicato

    cout << "\n=== operator<< ===" << endl;
    cout << c1 << endl;
    cout << cc1 << endl;
    cout << ccp1 << endl;

    cout << "\n=== Verifica Copia Profonda (Deep Copy) ===" << endl;
    Conto c2 = c1;
    c2.deposita(9999);
    cout << "c1 (originale) saldo dopo modifica su copia: " << c1.get_saldo() << " (Invariato)" << endl;
    cout << "c2 (copia) saldo: " << c2.get_saldo() << endl;
    cout << "Conti attivi in memoria (dopo la copia c2): " << Conto::get_num_conti() << endl;

    cout << "\n=== Stampe degli Storici ===" << endl;
    c1.stampa_storico();
    ccp1.stampa_storico();

    cout << "\n=== Distruzione automatica ===" << endl;
}