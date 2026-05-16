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

        int operator+(const Frazione& altro) const { return (this->numeratore / this->denominatore) + (altro.numeratore / altro.denominatore); }
        int operator*(const Frazione& altro) const { return ((this->numeratore * altro.denominatore ) + (this->denominatore * altro.numeratore)); }

        bool operator==(const Frazione& altro) const { return (this->numeratore == altro.numeratore) && (this->denominatore == altro.denominatore); }
        friend ostream& operator<<(ostream& os, const Frazione& frazione) {}

        void semplifica()
        {
            int comune = gcd(this->numeratore, this->denominatore);
            this->numeratore /= comune;
            this->denominatore /= comune;

            if (denominatore < 0)
            {
                this->numeratore = - this->numeratore;
                this->denominatore = - this->denominatore;
            }
            
        }
};

ostream& operator<<(ostream& os, const Frazione& frazione)
{
    os << "\n(" << frazione.get_numeratore() << "/" << frazione.get_denominatore() << ")" << endl;
    return os;
}

int main()
{
    Frazione f(4, 2);
}