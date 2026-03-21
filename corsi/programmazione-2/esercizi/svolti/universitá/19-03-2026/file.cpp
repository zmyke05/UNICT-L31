// gli attributi non vengono mai inizializzati durant
#include <iostream>

using namespace std;

class Utente
{
private:
    string nome;
    string cognome;

public:
    Utente(const string &nome, const string &cognome) : nome(nome), cognome(cognome) {}

    Utente(): nome(""), cognome("") {} // default 
    Utente(const Utente& origin)
    {
        nome = origin.nome;
        cognome = origin.cognome;
    }

    ~Utente() // distruttore della classe Utente 
    {
        nome = "";
        cognome = "";
    }

    /* Utente()
    {
        nome = "";
        cognome = "";
    } */

    // oppure Utente() = default;

    const string &getNome() const // funzione che non consente di modificare il valore al suo interno
    {
        // protezione contenuto metodo
        // protezione valore di ritorno
        return this->nome;
    }

    const string &getCognome() const // funzione che non consente di modificare il valore al suo interno
    {
        // protezione contenuto metodo
        // protezione valore di ritorno
        return this->cognome;
    }

    void setNome(const string &nome)
    {
        this->nome = nome;
    }

    void setCognome(const string &cognome)
    {
        this->cognome = cognome;
    }

    // metodi inline
    inline void print()
    {
        cout << this->nome << " " << this->cognome << endl;
    }
};

int main()
{
    Utente mario("Mario", "Rossi");
    Utente *luca = new Utente("Luca", "Bianchi");
    Utente giovanni;
    /* delete luca; */
    mario.setNome("Luigi");

    luca->setNome("Luchino");

    /* Utente* luca2 = new Utente(luca->getNome(), luca->getCognome()); */

    // copy costructore

    cout << mario.getNome() << " " << mario.getCognome() << endl;
    return 0;
}