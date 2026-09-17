#include <iostream>

using namespace std;

// Gerararchia di classi
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

class UtenteSpeciale : public Utente // ereditarietá
{
    private:
        int code;
    
    public:
        UtenteSpeciale(const string& nome, const string & cognome, const int& code)
        : Utente(nome, cognome), code(code)
        {
            
        }
};

int main()
{
}