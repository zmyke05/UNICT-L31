/* Esercizio 2 (medio): Crea una gerarchia a tre livelli: Dipendente (nome, stipendio base) → Responsabile (aggiunge bonus) → DirettoreRegionale (aggiunge num_filiali). 
Ogni classe aggiunge un metodo stipendio_totale() che calcola il compenso complessivo: per Dipendente è lo stipendio base, per Responsabile è stipendio base + bonus, per DirettoreRegionale è stipendio base + bonus + num_filiali * 500. Ogni classe chiama il metodo della classe sopra nella catena. 
Testa nel main creando un oggetto per ogni livello. */
#include <iostream>

using namespace std;

class Dipendene
{
    private:
        string nome;
        double stipendio_base;
    
    public:
        Dipendene(const string& nome, const double stipendio_base) : nome(nome), stipendio_base(stipendio_base) {}
        virtual ~Dipendene() {}

        // Setter
        void set_nome(const string& nome) { this->nome = nome; }
        void set_stipendio_base(const double stipendio_base) { this->stipendio_base = stipendio_base; } 

        // Getter
        const string get_nome() const { return this->nome; }
        const double get_stipendio_base() const { return this->stipendio_base; }

        // Metodo stipendio_totale()
        const double stipendio_totale() const { return this->stipendio_base; }

        // Metodo info()
        void info() { cout << "nome: " << this->nome << "\nstipendio base: " << this->stipendio_base; }
};

class Responsabile : public Dipendene
{
    private:
        double bonus;
    
    public:
        Responsabile(const string& nome, const double stipendio_base, const double bonus) : Dipendene(nome, stipendio_base), bonus(bonus) {}
        virtual ~Responsabile() {}

        // Setter
        void set_bonus(const double bonus) { this->bonus = bonus; }

        // Getter
        double get_bonus() const { return this->bonus; }

        // Metodo stipendio_totale()
        double stipendio_totale() 
        {
            double stipendio_dipendente = Dipendene::stipendio_totale();
            return stipendio_dipendente + this->bonus;
        }

        // Metodo info()
        void info()
        {
            Dipendene::info();
            cout << "\nbonus: " << this->bonus << endl;
        }
};

class DirettoreRegionale : public Responsabile
{
    private:
        int num_filiali;
    
    public:
        DirettoreRegionale(const string& nome, const double stipendio_base, const double bonus, const int num_filiali) : Responsabile(nome, stipendio_base, bonus), num_filiali(num_filiali) {}
        virtual ~DirettoreRegionale() {}

        // Setter
        void set_num_filiali(const int num_filiali) { this->num_filiali = num_filiali; }

        // Getter
        int get_num_filiali() { return this->num_filiali; }

        // Metodo stipendio_totale()
        double stipendio_totale()
        {
            double stipendio_responsabile = Responsabile::stipendio_totale();
            return stipendio_responsabile + (num_filiali * 500);
        }

        // Metodo info()
        void info()
        {
            Responsabile::info();
            cout << "numero filiali: " << this->num_filiali << endl;
        }
};

int main()
{
    Dipendene d1("Mario", 1200);
    Responsabile r1("Franco", 1200, 400);
    DirettoreRegionale dr1("Optimus Prime", 1200, 400, 5);

    cout << "\nDipendente: " << d1.stipendio_totale() << endl;
    d1.info();

    cout << "\n\nReponsabile: " << r1.stipendio_totale() << endl;
    r1.info();

    cout << "\nDirettore Generale: " << dr1.stipendio_totale() << endl;
    dr1.info();

} 