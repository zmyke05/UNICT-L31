#include <iostream>

using namespace std;

class Persona
{
private:
    string nome;
    string cognome;
    string codice_fiscale;

public:
    Persona(const string &codice_fiscale, const string &nome, const string &cognome) : codice_fiscale(codice_fiscale), nome(nome), cognome(cognome) {}
    virtual ~Persona() {}

    const string &get_codice_fiscale() const { return this->codice_fiscale; }
};

class Paziente : public Persona
{
public:
    Paziente(const string &codice_fiscale, const string &nome, const string &cognome) : Persona(codice_fiscale, nome, cognome) {}
    ~Paziente() override {}
};

class Disciplina
{
private:
    string nome;
    size_t codice_univoco;

public:
    Disciplina(const string &nome, const size_t codice_univoco) : nome(nome), codice_univoco(codice_univoco) {}
    virtual ~Disciplina() {}

    const string &get_nome() const { return this->nome; }
    size_t get_codice_univoco() const { return this->codice_univoco; }
};

class Medico : public Persona
{
private:
    Disciplina *specializzazione;

public:
    Medico(const string &codice_fiscale, const string &nome, const string &cognome) : Persona(codice_fiscale, nome, cognome) {}
    ~Medico() override {}

    Disciplina *get_specializzazione() const { return this->specializzazione; }
};

class Turno
{
private:
    int numero_turno;
    Medico* medico;
    Paziente** pazienti;
    int num_pazienti;

public:
    Turno(const int num_turno, Medico* medico, const int num_pazienti) : numero_turno(numero_turno), medico(medico), num_pazienti(0) 
    {
        this->pazienti = new Paziente*[num_pazienti];
    }

    ~Turno() { delete this->pazienti; }

    void aggiungi_paziente(Paziente* p)
    {
        this->pazienti[num_pazienti] = p;
        this->num_pazienti++;
    }
};

int main()
{
}