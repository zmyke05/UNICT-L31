/* Esercizio PRECEDENTE (avanzato): Crea una gerarchia Conto → ContoCorrente → ContoCorrente_Premium con questi requisiti:

Conto gestisce un array dinamico di double che rappresenta lo storico delle transazioni (usa la Regola del Tre completa). Ha metodi deposita(), preleva() (no saldo negativo), stampa_storico(). Ha un attributo static num_conti. Implementa operator<<.
ContoCorrente aggiunge limite_scoperto — preleva() permette saldo negativo fino al limite. Chiama Conto::preleva() se possibile, gestisce autonomamente solo il caso scoperto.
ContoCorrente_Premium aggiunge cashback_percentuale — ogni prelievo riuscito aggiunge automaticamente il cashback% dell'importo come deposito. Ridefinisce preleva() chiamando quello di ContoCorrente.

Verifica nel main:

Ordine di costruzione e distruzione
Copia tramite costruttore di copia (deep copy dello storico)
operator<< su tutti e tre i livelli
Tutti i casi limite: prelievo oltre saldo, prelievo oltre limite scoperto, cashback applicato correttamente
Il contatore static aggiornato correttamente */



/* Esercizio 3 (avanzato): Estendi la gerarchia Conto → ContoCorrente → ContoCorrente_Premium dell'esercizio precedente. Aggiungi un metodo virtual rendiconto() che stampa un riepilogo diverso per ogni livello — Conto stampa saldo e storico, ContoCorrente aggiunge lo scoperto utilizzato, ContoCorrente_Premium aggiunge il cashback totale accumulato. Aggiungi un attributo cashback_totale che si accumula ad ogni prelievo riuscito. Crea un array polimorfico di tre puntatori a Conto, assegna uno per tipo, chiama rendiconto() su tutti — verifica che il dispatch dinamico chiami la versione giusta. Verifica che il distruttore virtual chiami la catena corretta con delete sul puntatore base. */
#include <iostream>

using namespace std;

class Conto
{
    private:
        double *storico_transazioni;
        double saldo;
        static int num_conti;

    public:
        Conto(const double* storico_transazioni, const double saldo) : storico_transazioni(new double[num_conti]), saldo(saldo)
        {
            for (int i = 0; i < num_conti; i++)
            {
                this->storico_transazioni[i] = storico_transazioni[i];
            }
            num_conti++;
        }

        ~Conto() { delete[] storico_transazioni; num_conti--; }

        // Setter
        void set_saldo(const double saldo) { this->saldo = saldo; } 

        // Getter
        double get_saldo() const { return this->saldo; }
};

class ContoCorrente : public Conto
{
    private:
        double limite_scoperto;

    public:
        ContoCorrente(const double* storico_transazioni, const double saldo, const double limite_scoperto) : Conto(storico_transazioni, saldo), limite_scoperto(limite_scoperto) { }
        ~ContoCorrente() {}

        // Setter
        void set_limite_scoperto(const double limite_scoperto) { this->limite_scoperto = limite_scoperto; }

        // Getter
        double get_limite_scoperto() const { return this->limite_scoperto; }
};      

class ContoCorrente_Premium : public ContoCorrente
{
    private: 
        double cashback_percentuale;

    public:
        ContoCorrente_Premium(const double* storico_transazioni, const double saldo, const double limite_scoperto, const double cashback_percetuale) : ContoCorrente(storico_transazioni, saldo, limite_scoperto),  cashback_percentuale(cashback_percetuale) {}
        ~ContoCorrente_Premium() {}

        // Setter
        void set_cashback_percentuale(const double cashback_percentuale) { this->cashback_percentuale = cashback_percentuale; } 

        // Getter
        double get_cashback_percentuale() const { return this->cashback_percentuale; }
};

int Conto::num_conti = 0;

int main()
{

}