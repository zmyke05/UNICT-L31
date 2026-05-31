/* Esercizio PRECEDENTE (avanzato): Crea una gerarchia Conto → ContoCorrente → ContoCorrente_Premium con questi requisiti:

Conto gestisce un array dinamico di double che rappresenta lo storico delle transazioni (usa la Regola del Tre completa). Ha metodi deposita(), preleva() (no saldo negativo), stampa_storico(). 
Ha un attributo static num_conti. Implementa operator<<.
ContoCorrente aggiunge limite_scoperto — preleva() permette saldo negativo fino al limite. Chiama Conto::preleva() se possibile, gestisce autonomamente solo il caso scoperto.
ContoCorrente_Premium aggiunge cashback_percentuale — ogni prelievo riuscito aggiunge automaticamente il cashback% dell'importo come deposito. Ridefinisce preleva() chiamando quello di ContoCorrente.

Verifica nel main:

Ordine di costruzione e distruzione
Copia tramite costruttore di copia (deep copy dello storico)
operator<< su tutti e tre i livelli
Tutti i casi limite: prelievo oltre saldo, prelievo oltre limite scoperto, cashback applicato correttamente
Il contatore static aggiornato correttamente */

/* Esercizio 3 (avanzato): Estendi la gerarchia Conto → ContoCorrente → ContoCorrente_Premium dell'esercizio precedente. 
Aggiungi un metodo virtual rendiconto() che stampa un riepilogo diverso per ogni livello — Conto stampa saldo e storico, ContoCorrente aggiunge lo scoperto utilizzato, ContoCorrente_Premium aggiunge il cashback totale accumulato. 
Aggiungi un attributo cashback_totale che si accumula ad ogni prelievo riuscito. 
Crea un array polimorfico di tre puntatori a Conto, assegna uno per tipo, chiama rendiconto() su tutti — verifica che il dispatch dinamico chiami la versione giusta. 
Verifica che il distruttore virtual chiami la catena corretta con delete sul puntatore base. */
#include <iostream>

using namespace std;

class Conto
{
private:
    double *storico;
    int num_transazioni;
    double saldo;
    int capacita_massima;
    static int num_conti;

protected:
    void aggiungi_transazione(double importo)
    {
        if (this->num_transazioni < capacita_massima)
            this->storico[num_transazioni++] = importo;
    }

public:
    Conto(const double *storico, const int num_transazioni, const double saldo, const int capacita_massima)
        : storico(new double[capacita_massima]),
          num_transazioni(num_transazioni),
          saldo(saldo),
          capacita_massima(capacita_massima)
    {
        // Se il puntatore esterno è nullo, non possiamo copiare transazioni passate!
        if (storico == nullptr)
        {
            this->num_transazioni = 0;
        }
        else
        {
            // Per evitare Buffer Overflow, non copiare mai più elementi di quanti l'array possa contenerne
            if (this->num_transazioni > capacita_massima)
            {
                this->num_transazioni = capacita_massima;
            }

            for (int i = 0; i < this->num_transazioni; i++)
                this->storico[i] = storico[i];
        }
        num_conti++;
    }

    // Setter
    void set_saldo(const double saldo) { this->saldo = saldo; }
    void set_capacita_massima(const int capacita_massima) { this->capacita_massima = capacita_massima; }

    // Getter
    double get_saldo() const { return this->saldo; }
    int get_capacita_massima() const { return this->capacita_massima; }

    // REGOLA DEL TRE
    // - distruttore
    // - costruttore di copia
    // - overloding con operator=
    virtual ~Conto()
    {
        delete[] storico;
        num_conti--;
    }

    Conto(const Conto &altro)
    {
        this->num_transazioni = altro.num_transazioni;
        this->capacita_massima = altro.capacita_massima;
        this->saldo = altro.saldo;
        this->storico = new double[this->capacita_massima];
        for (int i = 0; i < this->num_transazioni; i++)
        {
            this->storico[i] = altro.storico[i];
        }
        num_conti++;
    }

    Conto &operator=(const Conto &altro)
    {
        if (this == &altro)
        {
            return *this;
        }
        delete[] storico;
        this->num_transazioni = altro.num_transazioni;
        this->capacita_massima = altro.capacita_massima;
        this->saldo = altro.saldo;
        this->storico = new double[this->capacita_massima];
        for (int i = 0; i < this->num_transazioni; i++)
        {
            this->storico[i] = altro.storico[i];
        }
        return *this;
    }

    // Metodo deposita()
    Conto &deposita(double importo)
    {
        if (importo <= 0)
        {
            cout << "Importo errato" << endl;
            return *this;
        }
        this->saldo += importo;
        aggiungi_transazione(+importo);
        return *this;
    }

    // Metodo preleva()
    virtual Conto &preleva(double importo)
    {
        if (importo <= 0)
        {
            cout << "Importo errato" << endl;
            return *this;
        }

        if (this->saldo >= 0 && this->saldo - importo >= 0)
            this->saldo -= importo;
        else
        {
            cout << "Saldo non sufficente" << endl;
            return *this;
        }
        aggiungi_transazione(-importo);
        return *this;
    }

    // Metodo stampa_storico()
    void stampa_storico()
    {
        for (int i = 0; i < num_transazioni; i++)
        {
            cout << "[" << i << "]" << this->storico[i] << endl;
        }
    }

    // Metodo rendi_conto()
    virtual void rendi_conto() const
    {
        cout << "Conto | " << "Saldo:" << this->get_saldo() << " | " << "Numero Transazioni:" << this->num_transazioni;
    }

    // Operator<<
    friend ostream &operator<<(ostream &os, const Conto &c)
    {
        c.rendi_conto();
        return os;
    }
};

class ContoCorrente : public Conto
{
private:
    double limite_scoperto;

public:
    ContoCorrente(const double *storico, const int num_transazioni, const double saldo, const int capacita_massima, const double limite_scoperto) : Conto(storico, num_transazioni, saldo, capacita_massima), limite_scoperto(limite_scoperto) {}
    ~ContoCorrente() {}

    ContoCorrente(const ContoCorrente &altro) : Conto(altro), limite_scoperto(altro.limite_scoperto) {}

    ContoCorrente &operator=(const ContoCorrente &altro)
    {
        if (this == &altro)
        {
            return *this;
        }

        Conto::operator=(altro);
        this->limite_scoperto = altro.limite_scoperto;
        return *this;
    }

    // Setter
    void set_limite_scoperto(const double limite_scoperto) { this->limite_scoperto = limite_scoperto; }

    // Getter
    double get_limite_scoperto() const { return this->limite_scoperto; }

    // Metodo preleva()
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
            aggiungi_transazione(-importo);
            return *this;
        }

        cerr << "Limite scoperto superato" << endl;
        return *this;
    }

    // Metodo rendi_conto()
    void rendi_conto() const override
    {
        Conto::rendi_conto();
        cout << " | Limite Scoperto:" << this->limite_scoperto;
    }
};

ostream &operator<<(ostream &os, const ContoCorrente &cc)
{
    cc.rendi_conto();
    return os;
}

class ContoCorrente_Premium : public ContoCorrente
{
private:
    double cashback_percentuale;

public:
    ContoCorrente_Premium(const double *storico, const int num_transazioni, const double saldo,  int capacita_massima, const double limite_scoperto, const double cashback_percetuale) : ContoCorrente(storico, num_transazioni, saldo, capacita_massima, limite_scoperto), cashback_percentuale(cashback_percetuale) {}
    ~ContoCorrente_Premium() override {}

    ContoCorrente_Premium(const ContoCorrente_Premium &altro) : ContoCorrente(altro), cashback_percentuale(altro.cashback_percentuale) {}

    ContoCorrente_Premium &operator=(const ContoCorrente_Premium &altro)
    {
        if (this == &altro)
        {
            return *this;
        }
        ContoCorrente::operator=(altro);
        this->cashback_percentuale = altro.cashback_percentuale;
        return *this;
    }

    // Setter
    void set_cashback_percentuale(const double cashback_percentuale) { this->cashback_percentuale = cashback_percentuale; }

    // Getter
    double get_cashback_percentuale() const { return this->cashback_percentuale; }

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

    // Metodo rendi_conto()
    void rendi_conto() const override
    {
        ContoCorrente::rendi_conto();
        cout << "| Cashback:" << "%" << this->get_cashback_percentuale();
    }
};

ostream &operator<<(ostream &os, const ContoCorrente_Premium &ccp)
{
    ccp.rendi_conto();
    return os;
}

int Conto::num_conti = 0;

int main()
{
    Conto *conto[3];
    conto[0] = new Conto(nullptr, 0, 700, 2000);
    conto[1] = new ContoCorrente(nullptr, 0, 700, 2000, 40);
    conto[2] = new ContoCorrente_Premium(nullptr, 0, 700, 2000, 40, 5);
    for(int i = 0; i < 3; i++)
        cout << "\n" << *conto[i] << endl << endl;

    for (int i = 0; i < 3; i++)
    delete conto[i];   // ← aggiungilo
}