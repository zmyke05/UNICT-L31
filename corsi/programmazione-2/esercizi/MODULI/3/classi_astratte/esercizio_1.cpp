/* Esercizio 1 (base): Crea una classe astratta Veicolo con metodi puri accelera(), frena() e descrizione().
Implementa due classi concrete Auto (con num_porte) e Moto (con cilindrata).
Ogni classe implementa i tre metodi puri stampando informazioni specifiche.
Crea un array polimorfico, chiama tutti i metodi su ogni elemento, verifica che Veicolo non sia istanziabile direttamente. Aggiungi messaggi nei costruttori e distruttori. */
#include <iostream>

using namespace std;

class Veicolo
{
public:
    Veicolo() { cout << "Costruttore: Veicolo" << endl; }
    virtual ~Veicolo() { cout << "Distruttore: Veicolo" << endl; }

    virtual void accelera() const = 0;
    virtual void frena() const = 0;
    virtual void descrizione() const = 0;
    friend ostream &operator<<(ostream &os, const Veicolo &v)
    {
        v.descrizione();
        return os;
    }
};

class Auto : public Veicolo
{
private:
    int num_porte;

public:
    Auto(const int num_porte) : num_porte(num_porte) { cout << "Costruttore: Auto" << endl; }
    ~Auto() override { cout << "Distruttore: Auto" << endl; }

    // Setter
    void set_num_porte(const int num_porte) { this->num_porte = num_porte; }

    // Getter
    int get_num_porte() const { return this->num_porte; }

    void accelera() const override { cout << "Accelera" << endl; }
    void frena() const override { cout << "Frena" << endl; }
    void descrizione() const override { cout << "numero porte: " << this->num_porte; }
};

/* ostream& operator<<(ostream& os, const Auto& a)
{
    a.descrizione();
    return os;
} */

class Moto : public Veicolo
{
private:
    int cilindrata;

public:
    Moto(const int cilindrata) : cilindrata(cilindrata) { cout << "Costruttore: Moto" << endl; }
    ~Moto() override { cout << "Distruttore: Moto" << endl; }

    // Setter
    void set_num_porte(const int cilindrata) { this->cilindrata = cilindrata; }

    // Getter
    int get_num_porte() const { return this->cilindrata; }

    void accelera() const override { cout << "Accelera" << endl; }
    void frena() const override { cout << "Frena" << endl; }
    void descrizione() const override { cout << "cilindrata: " << this->cilindrata; }
};

/* ostream& operator<<(ostream& os, const Moto& m)
{
    m.descrizione();
    return os;
} */

int main()
{
    Veicolo *array[2];
    array[0] = new Auto(4);
    array[1] = new Moto(125);

    cout << "\n\nSTAMPA DESCRIZIONI" << endl;
    for (int i = 0; i < 2; i++)
        cout << *array[i] << endl;

    cout << "\n\nDISTRUTTORI" << endl;
    for (int i = 0; i < 2; i++)
        delete array[i];
}