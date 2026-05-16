/* Esercizio 1 (base): Prendi la classe Vettore2D degli esercizi precedenti e aggiungi operator+, operator-, operator==, operator!=. Testali nel main con almeno tre vettori. */
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

    // OPERATOR
    Vettore2D operator+(const Vettore2D &altro) const { return Vettore2D(this->x + altro.x, this->y + altro.y); }
    Vettore2D operator-(const Vettore2D &altro) const { return Vettore2D(this->x - altro.x, this->y - altro.y); }
    bool operator==(const Vettore2D altro) { return this->x == altro.x && this->y == altro.y; }
    bool operator!=(const Vettore2D altro) { return this->x != altro.x && this->y != altro.y; }

    Vettore2D &scala(double fattore)
    {
        this->x *= fattore;
        this->y *= fattore;
        num_operazioni++;
        return *this;
    }

    Vettore2D &transla(double dx, double dy)
    {
        this->x += dx;
        this->y += dy;
        num_operazioni++;
        return *this;
    }

    Vettore2D &ruota90()
    {
        double temp = this->x;
        this->x = -this->y;
        this->y = temp;
        num_operazioni++;
        return *this;
    }

    Vettore2D &stampa()
    {
        cout << "(" << this->x << ", " << this->y << ")" << endl;
        num_operazioni++;
        return *this;
    }
};

int Vettore2D::num_operazioni = 0;

int main()
{
    Vettore2D v1(1.0, 2.0);
    Vettore2D v2(3.0, 4.0);
    Vettore2D v3 = v1 + v2;
    Vettore2D v4 = v1 - v2;


    v3.stampa();
    v4.stampa();
    cout << (v1 == v2) << endl;
    cout << (v1 != v2) << endl;

    return 0;
}
