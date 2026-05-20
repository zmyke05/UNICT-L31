/* Esercizio 2 (medio): Crea una classe Frazione con attributi privati numeratore e denominatore (interi). Implementa operator+, operator*, operator== e operator<<. Per la somma usa la formula a/b + c/d = (a*d + b*c) / (b*d). Aggiungi un metodo privato semplifica() che divide numeratore e denominatore per il loro MCD — chiamalo alla fine di ogni operazione. */
#include <iostream>
#include <numeric>

using namespace std;
using std::gcd;

class Frazione
{
private:
    int numeratore;
    int denominatore;

public:
    Frazione(int numeratore, int denominatore) : numeratore(numeratore), denominatore(denominatore) {}
    ~Frazione() {}

    void set_numeratore(const int numeratore) { this->numeratore = numeratore; }
    void set_denominatore(const int denominatore) { this->denominatore = denominatore; }

    int get_numeratore() const { return this->numeratore; }
    int get_denominatore() const { return this->denominatore; }

    Frazione operator+(const Frazione &altro) const
    {
        int num = (this->numeratore * altro.denominatore) + (altro.numeratore * this->denominatore);
        int den = this->denominatore * altro.denominatore;
        Frazione risultato(num, den);
        risultato.semplifica();
        return risultato;
    }

    // PRODOTTO: a/b * c/d = (a*c) / (b*d)
    Frazione operator*(const Frazione &altro) const
    {
        int num = this->numeratore * altro.numeratore;
        int den = this->denominatore * altro.denominatore;
        Frazione risultato(num, den);
        risultato.semplifica();
        return risultato;
    }
    bool operator==(const Frazione &altro) const
    {
        Frazione a = *this; // copia per non modificare gli originali
        Frazione b = altro;
        a.semplifica();
        b.semplifica();
        return (this->numeratore == altro.numeratore) && (this->denominatore == altro.denominatore);
    }
    friend ostream &operator<<(ostream &os, const Frazione &frazione);

    void semplifica()
    {
        if (denominatore == 0)
        {
            cerr << "Errore: denominatore zero" << endl;
            return;
        }
        int comune = gcd(this->numeratore, this->denominatore);
        this->numeratore /= comune;
        this->denominatore /= comune;

        if (denominatore < 0)
        {
            this->numeratore = -this->numeratore;
            this->denominatore = -this->denominatore;
        }
    }
};

ostream &operator<<(ostream &os, const Frazione &frazione)
{
    os << "(" << frazione.get_numeratore() << "/" << frazione.get_denominatore() << ")" << endl;
    return os;
}

int main()
{
    Frazione f1(1, 2);   // 1/2
    Frazione f2(1, 3);   // 1/3

    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;

    Frazione somma = f1 + f2;
    cout << "f1 + f2 = " << somma << endl;   // atteso: 5/6

    Frazione prod = f1 * f2;
    cout << "f1 * f2 = " << prod << endl;    // atteso: 1/6

    Frazione f3(2, 4);   // equivale a 1/2
    cout << "f1 == f3: " << (f1 == f3) << endl;  // atteso: 1
    cout << "f1 == f2: " << (f1 == f2) << endl;  // atteso: 0
}