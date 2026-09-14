/* Esercizio 2 (medio): Crea una classe Banca con:

Attributo static tasso_interesse (double) — uguale per tutti i conti
Attributo static num_conti (int) — conta i conti esistenti
Attributi privati per istanza: titolare (string) e saldo (double)
Costruttore che incrementa num_conti, distruttore che lo decrementa
Metodo deposita(double) che restituisce *this per chiamate a catena
Metodo applica_interessi() che moltiplica il saldo per (1 + tasso_interesse)
Metodi static get_num_conti() e static set_tasso(double)
Metodo info() che stampa titolare, saldo e tasso corrente */
#include <iostream>

using namespace std;

class Banca
{
private:
    static double tasso_interesse;
    static int num_conti;
    string titolare;
    double saldo;

public:
    Banca(const string &titolare, double saldo) : titolare(titolare), saldo(saldo) { num_conti++; }
    ~Banca() { num_conti--; }

    void set_titolare(const string &titolare) { this->titolare = titolare; }
    void set_saldo(const double saldo) { this->saldo = saldo; }
    static void set_tasso(double tasso) { tasso_interesse = tasso; }

    string get_titolare() const { return this->titolare; }
    double get_saldo() const { return this->saldo; }
    static int get_num_conti() { return num_conti; }

    Banca &deposita(double importo)
    {
        saldo += importo;
        return *this;
    }

    Banca& applica_interesse()
    {
        this->saldo *= (1 + this->tasso_interesse);
        return *this;
    }

    void stampa()
    {
        cout << "\nTitolare: " << this->titolare << "\nSaldo: " << this->saldo << "\nTasso interesse: " << tasso_interesse << endl;
    }
};

double Banca::tasso_interesse = 0;
int Banca::num_conti = 0;

int main()
{
    Banca conto("Michele", 500);
    conto.stampa();
    conto.deposita(50).deposita(50);
    conto.stampa();
}