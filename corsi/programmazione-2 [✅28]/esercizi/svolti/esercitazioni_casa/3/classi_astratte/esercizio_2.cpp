/* Esercizio 2 (medio): Crea una classe astratta Figura3D con metodi puri volume(), superficie() e descrizione().
Implementa Sfera (volume = 4/3 * PI * r³, superficie = 4 * PI * r²), Cubo (volume = lato³, superficie = 6 * lato²) e Cilindro (volume = PI * r² * h, superficie = 2*PI*r*h + 2*PI*r²).
Aggiungi operator<< nella base che chiama descrizione() tramite polimorfismo.
Implementa un metodo static nella base che riceve un array di puntatori e stampa quella con volume maggiore. Testa tutto nel main. */
#include <iostream>
#include <math.h>

using namespace std;

// Classe astratta
class Figura3D
{
public:
    Figura3D() {}
    virtual ~Figura3D() {}

    virtual double volume() const = 0;
    virtual double superfice() const = 0;
    virtual void descrizione() const = 0;

    static void stampa_maggiore(Figura3D* array[], int dim) 
    {  
        Figura3D* max_volume_figura = array[0];
        for(int i = 0; i < dim; i++)
        {
            if(array[i]->volume() > max_volume_figura->volume())
            {
                max_volume_figura = array[i];
            }
        }

        // Stampa finale del vincitore sfruttando l'operator<< polimorfico
        cout << "\n=========================================" << endl;
        cout << "FIGURA CON VOLUME MAGGIORE:" << endl;
        cout << *max_volume_figura << endl;
        cout << "=========================================" << endl;
    }

    friend ostream &operator<<(ostream &os, const Figura3D &f)
    {
        f.descrizione();
        return os;
    }
};

class Sfera : public Figura3D
{
private:
    double raggio;

public:
    Sfera(const double raggio) : raggio(raggio) {}
    ~Sfera() override {}

    // Setter
    void set_raggio(const double raggio) { this->raggio = raggio; }

    // Getter
    double get_raggio() const { return this->raggio; }

    double volume() const override { return (4 / 3 * 3.14 * pow(this->raggio, 3)); }
    double superfice() const override { return (4 * 3.14 * pow(this->raggio, 2)); }
    void descrizione() const override { cout << "Sfera | " << "Volume:" << this->volume() << " | Superfice:" << this->superfice() << endl; }
};

class Cubo : public Figura3D
{
private:
    double lato;

public:
    Cubo(const double lato) : lato(lato) {}
    ~Cubo() override {}

    // Setter
    void set_lato(const double lato) { this->lato = lato; }

    // Getter
    double get_lato() const { return this->lato; }

    double volume() const override { return pow(this->lato, 3); }
    double superfice() const override { return 6 * pow(this->lato, 2); }
    void descrizione() const override { cout << "Cubo | " << "Volume:" << this->volume() << " | Superfice:" << this->superfice() << endl; }
};

class Cilindro : public Figura3D
{
private:
    double altezza;
    double raggio;

public:
    Cilindro( const double raggio, const double altezza) :  raggio(raggio), altezza(altezza) {}
    ~Cilindro() override {}

    // Setter
    void set_altezza(const double altezza) { this->altezza = altezza; }

    // Getter
    double get_altezza() const { return this->altezza; }

    double volume() const override { return 3.14 * pow(this->raggio, 2) * this->altezza; }
    double superfice() const override { return (2 * 3.14 * this->raggio * this->altezza) + (2 * 3.14 * pow(this->raggio, 2)); }
    void descrizione() const override { cout << "Cilindro | " << "Volume:" << this->volume() << " | Superfice:" << this->superfice() << endl; }
};

int main()
{
    // Creazione dell'array polimorfico
    Figura3D* catalogo[3];
    catalogo[0] = new Sfera(5.0);
    catalogo[1] = new Cubo(4.0);
    catalogo[2] = new Cilindro(10.0, 3.0); // Dopo aver corretto l'ereditarietà di Cilindro

    // Chiamata al metodo statico della classe base
    Figura3D::stampa_maggiore(catalogo, 3);
    for(int i = 0; i < 3; i++) {
        catalogo[i]->descrizione();
    }

    // Pulizia della memoria
    for(int i = 0; i < 3; i++) {
        delete catalogo[i];
    }
}