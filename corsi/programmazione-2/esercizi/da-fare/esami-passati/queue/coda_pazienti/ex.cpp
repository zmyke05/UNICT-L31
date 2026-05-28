#include <iostream>

using namespace std;

class Patient
{
private:
    string name;
    int id;
    string condition;

public:
    Patient(const string &name, const int id, const string &condition) : name(name), id(id), condition(condition) {}
    ~Patient() {}

    // Setter
    void set_name(const string &name) { this->name = name; }
    void set_condition(const string &condition) { this->condition = condition; }
    void set_id(const int id) { this->id = id; }

    // Getter
    string get_name() const { return this->name; }
    string get_condition() const { return this->condition; }
    int get_id() const { return this->id; }

    void print()
    {
        cout << "name: " << this->name << " | " << "condition: " << this->condition << endl;
    }
};

class Node
{
private:
    Patient key;
    Node *next;

public:
    Node(const Patient &key) : key(key), next(nullptr) {}
    ~Node() {}

    Patient &get_key() { return this->key; }
    Node *get_next() const { return this->next; }
    void set_next(Node *next) { this->next = next; }
    void set_key(Patient &key) { this->key = key; }
};

class Queue
{
private:
    Node *head;
    Node *tail;
    size_t size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}
    ~Queue() 
    {
        while (!this->isEmpty())
        {
            dequeue();
        }
        
    }

    bool isEmpty() { return this->head == nullptr; }
    void enqueue(Patient val)
    {
        Node *new_node = new Node(val);
        if (this->isEmpty())
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            // caso 1 (sono solo presenti verdi nella lista)
            if (val.get_condition() == "rosso")
            {
                if (this->head->get_key().get_condition() == "verde")
                {
                    new_node->set_next(this->head);
                    this->head = new_node;
                }
                else
                {
                    // caso 2 (se é presente almeno 1 rosso)
                    Node *curr = this->head;
                    while (curr->get_next() != nullptr && curr->get_next()->get_key().get_condition() == "rosso")
                    {
                        curr = curr->get_next();
                    }
                    new_node->set_next(curr->get_next());
                    curr->set_next(new_node);

                    // Se inserito alla fine, aggiorna la coda
                    if (new_node->get_next() == nullptr)
                    {
                        this->tail = new_node;
                    }
                }
            }
            else
            {
                tail->set_next(new_node);
                this->tail = new_node;
            }
        }
    }

    Patient dequeue()
    {
        if (this->isEmpty())
        {
            cerr << "the queue is empty";
            exit(1);
        }

        Node *tmp = this->head;
        this->head = this->head->get_next();
        if (this->isEmpty())
        {
            this->tail = nullptr;
        }

        Patient buffer = tmp->get_key();
        delete tmp;
        return buffer;
    }

    void stampa() 
    {
        Node* curr = this->head;
        while (curr != nullptr)
        {
            cout << "Codice: " << curr->get_key().get_condition() << endl;
            curr = curr->get_next();
        }        
    }
};

int main()
{
    Queue pronto_soccorso;

    cout << "--- ARRIVO PAZIENTI IN PRONTO SOCCORSO ---" << endl;

    // Inseriamo i pazienti nell'ordine temporale di arrivo
    cout << "Arriva Antonio (Verde)" << endl;
    pronto_soccorso.enqueue(Patient("Antonio", 1, "verde"));

    cout << "Arriva Beatrice (Rosso)" << endl;
    pronto_soccorso.enqueue(Patient("Beatrice", 2, "rosso"));

    cout << "Arriva Carlo (Verde)" << endl;
    pronto_soccorso.enqueue(Patient("Carlo", 3, "verde"));

    cout << "Arriva Diana (Rosso)" << endl;
    pronto_soccorso.enqueue(Patient("Diana", 4, "rosso"));

    cout << "Arriva Elia (Verde)" << endl;
    pronto_soccorso.enqueue(Patient("Elia", 5, "verde"));


    pronto_soccorso.stampa();
    cout << endl; 

    cout << "\n--- CHIAMATA PAZIENTI (DEQUEUE) ---" << endl;

    // Svuotiamo la coda un paziente alla volta finché non è vuota
    while (!pronto_soccorso.isEmpty())
    {
        // Estraiamo il primo paziente della fila
        Patient p = pronto_soccorso.dequeue();

        // Stampiamo i suoi dati usando il metodo print della classe Patient
        p.print();
    }

    return 0;
}