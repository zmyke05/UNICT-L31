/* Esercizio 1 (base): Crea una classe Veicolo con attributi privati marca (string) e velocita_max (double), costruttore, getter e un metodo info() che stampa tutto. 
Crea una classe derivata Auto che aggiunge num_porte (int) e una classe derivata Moto che aggiunge cilindrata (int). 
Entrambe chiamano Veicolo::info() nel loro metodo info() e aggiungono le proprie informazioni. Verifica l'ordine di costruzione e distruzione con messaggi nei costruttori e distruttori. Testale nel main. */
#include <iostream>

using namespace std;

class Veicolo 
{
    private:
        string marca;
        double velocita_max;
    
    public:
        Veicolo(const string& marca, const double velocita_max) : marca(marca), velocita_max(velocita_max) { cout << "\ncostruttore classe Veicolo" << endl; }
        virtual ~Veicolo() { cout << "\ndistrutto classe Veicolo" << endl; }

        // Setter
        void set_marca(const string& marca) { this->marca = marca; }
        void set_velocita_max(const double velocita_max) { this->velocita_max = velocita_max; }

        // Getter
        string get_marca() const { return this->marca; }
        double get_velocita_max() const { return this->velocita_max; }

        // Metodo info()
        virtual void info() const
        {
            cout << "marca: " << this->marca << "\nvelocita massima: " << this->velocita_max;
        }
};

class Auto : public Veicolo 
{
    private:
        int num_porte;
    
    public:
        Auto(const string& marca, const double velocita_max, const int num_porte) : Veicolo(marca, velocita_max), num_porte(num_porte) { cout << "\ncostruttore classe Auto" << endl; }
        ~Auto() override { cout << "\ndistrutto classe Auto" << endl; }

        // Setter
        void set_num_porte(int num_porte) { this->num_porte = num_porte; }

        // Getter
        int get_num_porte() { return this->num_porte; }

        // Metodo info()
        void info() const override
        {
            Veicolo::info();
            cout << "\nnumero porte: " << num_porte;
        }
};

class Moto : public Veicolo 
{
    private:
        int cilindrata;
    
    public:
        Moto(const string& marca, const double velocita_max, const int cilindrata) : Veicolo(marca, velocita_max), cilindrata(cilindrata) { cout << "\ncostruttore classe Moto" << endl; }
        ~Moto() override { cout << "\ndistrutto classe Moto" << endl; }

                // Setter
        void set_cilindrata(int cilindrata) { this->cilindrata = cilindrata; }

        // Getter
        int get_cilindrata() { return this->cilindrata; }

        // Metodo info()
        void info() const override
        {
            Veicolo::info();
            cout << "\ncilindrata: " << this->cilindrata;
        }
};

int main()
{
    Veicolo v1("Fiat", 200);
    Auto a1("panda", 140, 4);
    Moto m1("yamaha r1", 250, 700);

    cout << endl;
    v1.info();
    cout << endl << endl;
    a1.info();
    cout << endl << endl;
    m1.info();
}