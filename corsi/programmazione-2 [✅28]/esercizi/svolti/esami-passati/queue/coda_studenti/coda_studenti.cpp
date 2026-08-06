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

    virtual void stampa() const
    {
        cout << this->matricola << ": " << this->nome << " " << this->cognome << " - " << this->media;
    }

    int get_matricola() const { return this->matricola; }
    const string &get_nome() const { return this->nome; }
    const string &get_cognome() const { return this->cognome; }
    double get_media() const { return this->media; }
};

ostream& operator<<(ostream& os, const Studente& studente)
{
    studente.stampa();
    return os;
}

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
    ~StudenteBorsista() override { delete borsa; }

    double get_importo_borsa() const { return borsa->get_importo(); }
    void stampa() const override
    {
        Studente::stampa();
        cout << " [" << "borsa di " << this->borsa->get_importo() << " euro" << " per " << this->borsa->get_durata() << " mesi" << "]";
    }
};

// CODA
class Node
{
private:
    Studente *key;
    Node *next;

public:
    Node(Studente *key) : key(key), next(nullptr) {}
    ~Node() {}

    Node *get_next() const { return this->next; }
    Studente *get_key() const { return this->key; }

    void set_next(Node *next) { this->next = next; }
};

class Queue
{
private:
    Node *head;
    Node *tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}
    virtual ~Queue() {}
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
            exit(1);
        }

        Node *tmp = this->head;
        this->head = this->head->get_next();

        if (this->isEmpty())
        {
            this->tail = nullptr;
        }

        Studente *buffer = tmp->get_key();
        delete tmp;
        return buffer;
    }

    void controlla_voti_media()
    {
        Node *curr = this->head;
        Node *prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->get_key()->get_media() < 25)
            {
                cout << "Avviso: rimosso " << curr->get_key()->get_nome()
                     << " Matr: " << curr->get_key()->get_matricola() << endl;

                Node *nodo_da_eliminare = curr;

                if (curr == head)
                {
                    Studente *buffer_studente = dequeue();
                    delete buffer_studente;
                    curr = this->head;
                }
                else
                {
                    prev->set_next(curr->get_next());

                    // Se stavamo eliminando l'ultimo, il precedente diventa la nuova tail
                    if (curr == tail)
                    {
                        this->tail = prev;
                    }

                    curr = curr->get_next();
                    delete nodo_da_eliminare->get_key();
                    delete nodo_da_eliminare;
                }
            } 
            else
            {
                prev = curr;
                curr = curr->get_next();
            }
        }
    }

    double calcola_totale_borse()
    {
        Node* curr = this->head;
        double totale = 0.0;

        while (curr != nullptr)
        {
            Studente* studente = curr->get_key();
            StudenteBorsista* borsista = dynamic_cast<StudenteBorsista*>(studente);

            if (borsista != nullptr)
            {
                totale += borsista->get_importo_borsa();
            }
            curr = curr->get_next();
        }
        return totale;
    }

    void stampa() const
    {
        Node *curr = this->head;
        while (curr != nullptr)
        {
            curr->get_key()->stampa();
            curr = curr->get_next();
            cout << endl;
        }
    }
};

ostream& operator<<(ostream& os, Queue& queue)
{
    queue.stampa();
    return os;
}

int main()
{
    Queue universita;

    cout << "--- INSERIMENTO STUDENTI ---" << endl;
    
    // 1001 - Mario Rossi (Normale)
    universita.enqueue(new Studente(1001, "Mario", "Rossi", 25.5));

    // 1002 - Anna Verdi (Borsista)
    BorsaDiStudio* b1 = new BorsaDiStudio(880.0, 12);
    universita.enqueue(new StudenteBorsista(b1, 1002, "Anna", "Verdi", 28.0));

    // 1003 - Luca Bianchi (Normale)
    universita.enqueue(new Studente(1003, "Luca", "Bianchi", 26.0));

    // 1004 - Sara Neri (Normale)
    universita.enqueue(new Studente(1004, "Sara", "Neri", 27.5));

    // 1005 - Marco Gialli (Borsista) -> Media < 25, verrà rimosso!
    BorsaDiStudio* b2 = new BorsaDiStudio(500.0, 8);
    universita.enqueue(new StudenteBorsista(b2, 1005, "Marco", "Gialli", 24.0));

    // 1006 - Laura Marroni (Borsista)
    BorsaDiStudio* b3 = new BorsaDiStudio(600.0, 8);
    universita.enqueue(new StudenteBorsista(b3, 1006, "Laura", "Marroni", 29.0));

    cout << "\n--- CONTENUTO INIZIALE DELLA CODA ---" << endl;
    cout << universita;

    cout << "\n--- CONTROLLO MEDIE (PUNTO 5) ---" << endl;
    universita.controlla_voti_media();

    cout << "\n--- CONTENUTO FINALE DELLA CODA ---" << endl;
    cout << universita;

    cout << "\n--- CALCOLO TOTALI (PUNTO 6) ---" << endl;
    double totale_borse = universita.calcola_totale_borse();
    cout << "Totale degli importi delle borse di studio: " << totale_borse << " euro" << endl;

    return 0;
}