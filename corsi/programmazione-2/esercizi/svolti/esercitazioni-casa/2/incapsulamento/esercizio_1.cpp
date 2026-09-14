/* Crea una classe Veicolo con attributi protected velocita_max (double) e carburante (double), e un attributo private targa (string). Aggiungi un costruttore e un metodo pubblico info() che stampa tutti e tre. */
/* Poi crea una classe Auto che eredita da Veicolo e aggiunge un attributo num_porte (int). Nel costruttore di Auto inizializza anche gli attributi di Veicolo. Aggiungi un metodo descrizione() che accede a velocita_max e carburante direttamente (essendo protected) ma non a targa. */
#include <iostream>
#include <string.h>

using namespace std;

class Veicolo
{
    private:
        string targa;

    protected:
        double carburante;
        double velocita_max;

    public:
        Veicolo(const string& t, double c, double v) : targa(t), carburante(c), velocita_max(v) {}
        ~Veicolo() {}

        // setter   
        void set_targa(const string t) { this->targa = t; }
        void set_carburante(const double c) { this->carburante = c; }
        void set_velocita(const double v) { this->velocita_max = v; }

        // getter
        string get_targa() const { return this->targa; }
        double get_carburante() const { return this->carburante; }
        double get_velocita() const { return this->velocita_max; }

        void info() const
        {
            cout << "targa: " << this->targa << "\ncarburante: " << this->carburante << "\nvelocita max: " << this->velocita_max << endl;
        }
};

class Auto : public Veicolo 
{
    private:
        int num_porte;
    
    public:
        Auto(int num_porte, const string& targa, double carburante, double velocita_max) : Veicolo(targa, carburante, velocita_max), num_porte(num_porte) {} 
        ~Auto() {}

        void set_num_porte(const int n) { this->num_porte = n; }
        int get_num_porte() const { return this->num_porte; }

        void descrizione() const
        {
            cout << "numero porte: " << this->num_porte << "\ncarburante: " << this->carburante << "\nvelocita max: " << this->velocita_max << endl;
        }
}; 

int main()
{

}