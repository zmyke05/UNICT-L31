// gli attributi non vengono mai inizializzati durant
#include <iostream>

using namespace std;

class Utente
{
private:
    string nome;
    string cognome;

public:
    Utente(const string &nome, const string &cognome)
    {
        this->nome = nome;
        this->cognome = cognome;
    }

    Utente()
    {
        nome = "";
        cognome = "";
    }

    // oppure Utente() = default;

    const string& getNome() const // funzione che non consente di modificare il valore al suo interno
    {
        // protezione contenuto metodo
        // protezione valore di ritorno
        return this->nome;
    }

    const string& getCognome() const // funzione che non consente di modificare il valore al suo interno
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
    Utente* luca = new Utente("Luca", "Bianchi");
    Utente giovanni;
    delete luca;
    mario.setNome("Luigi");
    cout<<mario.getNome()<<" " <<mario.getCognome() << endl;
    return 0;
}