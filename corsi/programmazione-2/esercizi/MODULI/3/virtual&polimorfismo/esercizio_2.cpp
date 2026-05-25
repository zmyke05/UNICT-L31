/* Esercizio 2 (medio): Crea una classe base Impiegato con attributi nome e stipendio_base, e un metodo virtual calcola_stipendio(). 
Derivane ImpiegatoFisso (stipendio invariato), ImpiegatoOrario (aggiunge ore_lavorate e tariffa_oraria — stipendio = ore * tariffa) e ImpiegatoVendite (aggiunge vendite e commissione_percentuale — stipendio = base + vendite * commissione / 100). 
Crea un array polimorfico, calcola e stampa lo stipendio di tutti. Implementa operator<< nella base e ridefiniscilo nelle derivate. */
#include <iostream>

using namespace std;

class Impiegato
{
    private:
        string nome;
        double stipendio_base;

    public:
        Impiegato(const string& nome, const double stipendio_base) : nome(nome), stipendio_base(stipendio_base) {}
        virtual ~Impiegato() {}

        // Setter
        void set_nome(const string& nome) { this->nome = nome; }
        void set_stipendio(const double stipendio_base) { this->stipendio_base = stipendio_base; }

        // Getter
        string get_nome() const { return this->nome; }
        double get_stipendio_base() const { return this->stipendio_base; }

        virtual double calcola_stipendio() const { return this->stipendio_base; }

        friend ostream& operator<<(ostream& os, Impiegato& impiegato);
};

ostream& operator<<(ostream& os, Impiegato& impiegato)
{
     os << "Stipendio dell'impiegato: " << impiegato.calcola_stipendio();
     return os;
}

class ImpiegatoFisso : public Impiegato
{
    public:
        ImpiegatoFisso(const string& nome, const double stipendio_base) : Impiegato(nome, stipendio_base) {}
        ~ImpiegatoFisso() override {}
        
        double calcola_stipendio() const override { return this->get_stipendio_base(); }
};

ostream& operator<<(ostream& os, ImpiegatoFisso& impiegato_fisso)
{
     os << "Stipendio dell'impiegato: " << impiegato_fisso.calcola_stipendio();
     return os;
}

class ImpiegatoOrario : public Impiegato
{
    private:
        int ore_lavorate;
        double tariffa_oraria;
    
    public:
        ImpiegatoOrario(const string& nome, const double stipendio_base, const int ore_lavorate, const double tariffa_oraria) : Impiegato(nome, stipendio_base), ore_lavorate(ore_lavorate), tariffa_oraria(tariffa_oraria) {}
        ~ImpiegatoOrario() override {}

        // Setter
        void set_ore_lavorate(const int ore_lavorate) { this->ore_lavorate = ore_lavorate; }
        void set_tariffa_oraria(const double tariffa_oraria) { this->tariffa_oraria = tariffa_oraria; }

        // Getter
        int get_ore_lavorate() const { return this->ore_lavorate; }
        double get_tariffa_oraria() const { return this->tariffa_oraria; }

        double calcola_stipendio() const override { return this->ore_lavorate * this->tariffa_oraria; }
};

ostream& operator<<(ostream& os, ImpiegatoOrario& impiegato_orario)
{
     os << "Stipendio dell'impiegato: " << impiegato_orario.calcola_stipendio();
     return os;
}

class ImpiegatoVendite : public Impiegato
{
    private:
        int vendite;
        double commissione;
    
    public:
        ImpiegatoVendite(const string& nome, const double stipendio_base, const int vendite, const double commissione) : Impiegato(nome, stipendio_base), vendite(vendite), commissione(commissione) {}
        ~ImpiegatoVendite() override {}

        // Setter
        void set_vendite(const int vendite) { this->vendite = vendite; }
        void set_commissione(const double commissione) { this->commissione = commissione; }

        // Getter
        int get_vendite() const { return this->vendite; }
        int get_commissione() const { return this->commissione; }

        double calcola_stipendio() const override { return this->get_stipendio_base() + this->vendite * (commissione / 100); }
}; 

ostream& operator<<(ostream& os, ImpiegatoVendite& impiegato_vendite)
{
     os << "Stipendio dell'impiegato: " << impiegato_vendite.calcola_stipendio();
     return os;
}

int main()
{
    Impiegato* impiegati[3];
    impiegati[0] = new ImpiegatoFisso("Mario", 10);
    impiegati[1] = new ImpiegatoOrario("Pippo", 200, 70, 5);
    impiegati[2] = new ImpiegatoVendite("Test", 400, 30, 3);
    
    for (int i = 0; i < 3; i++)
    {
        cout << *(impiegati[i]) << endl;
    }
}