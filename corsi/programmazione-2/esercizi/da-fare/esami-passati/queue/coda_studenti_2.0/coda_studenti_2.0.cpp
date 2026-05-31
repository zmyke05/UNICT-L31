#include <iostream>

using namespace std;

class Studente
{
private:
    int matricola;
    string nome;
    string cognome;
    double media;

public:
    Studente(const int matricola, const string &nome, const string &cognome, const double media) : matricola(matricola), nome(nome), cognome(cognome), media(media) {}
    virtual ~Studente() {}

    int get_matricola() const { return this->matricola; }
    const string &get_nome() const { return this->nome; }
    const string &get_cognome() const { return this->cognome; }
    double get_media() const { return this->media; }

    virtual void stampa() const
    {
        cout << this->matricola << ": " << this->nome << " " << this->cognome << " - " << this->media;
    }
};

class BorsaDiStudio
{
private:
    double importo;
    int durata;

public:
    BorsaDiStudio(const double importo, const int durata) : importo(importo), durata(durata) {}
    ~BorsaDiStudio() {}

    double get_importo() const { return this->importo; }
    int get_durata() const { return this->durata; }
};

class StudenteBorsista : public Studente
{
private:
    BorsaDiStudio *borsa;

public:
    StudenteBorsista(BorsaDiStudio *borsa, const int matricola, const string &nome, const string &cognome, const double media) : borsa(borsa), Studente(matricola, nome, cognome, media) {}
    ~StudenteBorsista() override {}

    double get_importo_borsa() const { return borsa->get_importo(); }

    void stampa() const override
    {
        Studente::stampa();
        cout << " [borsa di " << this->get_importo_borsa() << " euro]";
    }
};

class Node
{
private:
    Studente *key;
    Node *next;

public:
    Node(Studente *key) : key(key), next(nullptr) {}
    ~Node() {}

    Studente *get_key() const { return this->key; }
    Node *get_next() const { return this->next; }
    void set_next(Node *next) { this->next = next; }
};

class Coda
{
private:
    Node *head;
    Node *tail;

public:
    Coda() : head(nullptr), tail(nullptr) {}
    ~Coda() {}

    bool isEmpty() { return this->head == nullptr; }

    void enqueue(Studente *value)
    {
        Node *new_node = new Node(value);
        if (this->isEmpty())
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            this->tail->set_next(new_node);
            this->tail = new_node;
        }
    }

    Studente *dequeue()
    {
        if (this->isEmpty())
        {
            cerr << "The queue is empty";
            exit(1);
        }

        Node *tmp_node = this->head;
        this->head = this->head->get_next();

        if (this->isEmpty())
        {
            this->tail = nullptr;
        }

        Studente *tmp_studente = tmp_node->get_key();
        delete tmp_node;
        return tmp_studente;
    }

    void controllo_media_inferiore()
    {
        // Caso nodo inferiore in testa
        Node* curr = this->head;
        Node* prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->get_key()->get_media() < 25)
            {
                cout << "Avviso: rimosso " << curr->get_key()->get_nome()
                     << " Matr: " << curr->get_key()->get_matricola() << endl;

                Node* nodo_da_eliminare = curr;
                if (curr == head)
                {
                    Studente* buffer = dequeue();
                    delete buffer;
                    curr = this->head;
                }
                else
                {
                    prev->set_next(curr->get_next());
                    
                    if (curr == this->tail)
                    {
                        this->tail = prev;
                    }
                    
                    delete nodo_da_eliminare->get_key();
                    delete nodo_da_eliminare;
                    curr = curr->get_next();
                }
            }
            else
            {
                prev = curr;
                curr = curr->get_next();
            }
        }
    }
};

int main()
{
}