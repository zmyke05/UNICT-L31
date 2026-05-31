/* Esercizio 3 (avanzato): Crea una classe Vettore2D con attributi x e y (double). Implementa i seguenti metodi che restituiscono tutti *this per permettere chiamate a catena:

scala(double fattore) — moltiplica x e y per il fattore
trasla(double dx, double dy) — somma dx a x e dy a y
ruota90() — ruota il vettore di 90° (nuovo x = -y, nuovo y = x)
stampa() — stampa le coordinate e restituisce *this

Aggiungi un attributo static num_operazioni che si incrementa ogni volta che viene chiamato uno dei metodi sopra. Nel main costruisci una catena di almeno 4 operazioni e verifica il contatore. */
#include <iostream>

using namespace std;

class Vettore2D
{
private:
    double x;
    double y;
    static int num_operazioni;

public:
    Vettore2D(const double x, const double y) : x(x), y(y) {}
    ~Vettore2D() {}

    void set_x(const double x) { this->x = x; }
    void set_y(const double y) { this->y = y; }

    double get_x() const { return this->x; }
    double get_y() const { return this->y; }
    static int get_num_operazioni() { return num_operazioni; }

    Vettore2D& scala(double fattore)
    {
        this->x *= fattore;
        this->y *= fattore;
        num_operazioni++;
        return *this;
    }

    Vettore2D& transla(double dx, double dy)
    {
        this->x += dx;
        this->y += dy;
        num_operazioni++;
        return *this;
    }

    Vettore2D& ruota90()
    {
        double temp = this->x;
        this->x = -this->y;
        this->y = temp;
        num_operazioni++;
        return *this;
    }

    Vettore2D& stampa()
    {
        cout << "\nx: " << this->x << "\ny: " << this->y << endl;
        num_operazioni++;
        return *this;
    }
};

int Vettore2D::num_operazioni = 0;

int main()
{
    Vettore2D v(1.0, 2.0);

    cout << "Stato iniziale:" << endl;
    v.stampa();

    cout << "\nEsecuzione catena di operazioni..." << endl;
    // Chiamata a catena (Method Chaining)
    v.transla(2, 3).scala(2).stampa();

    cout << "\nNumero totale di operazioni eseguite: " << Vettore2D::get_num_operazioni() << endl;

    return 0;
}
