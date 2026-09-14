#include <iostream>

using namespace std;

class Patient
{
private:
    int id;
    string name;
    string condition;

public:
    Patient(const int id, const string &name, const string &condition) : id(id), name(name), condition(condition) {}
    ~Patient() {}

    string get_condition() const { return this->condition; }
    void print()
    {
        cout << "id: " << this->id << " | " << "name: " << this->name << " | " << "condition: " << this->condition << endl;
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

    Patient get_key() const { return this->key; }
    Node *get_next() const { return this->next; }
    void set_next(Node *next) { this->next = next; }
};

class Queue
{
private:
    Node *head;
    Node *tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue() {}

    bool isEmpty() { return this->head == nullptr; }

    void enqueue(Patient value)
    {
        Node *new_node = new Node(value);
        if (this->isEmpty())
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            // Caso codice rosso
            if (value.get_condition() == "rosso")
            {
                // caso inserimento in testa se sono presenti solo verdi
                if (this->head->get_key().get_condition() == "verde")
                {
                    new_node->set_next(this->head);
                    this->head = new_node;
                }
                else
                {
                    // caso inserimento se sono presenti dei rossi
                    Node *curr = this->head;
                    while (curr->get_next() != nullptr && curr->get_next()->get_key().get_condition() == "rosso")
                    {
                        curr = curr->get_next();
                    }
                    if (curr->get_next() == nullptr)
                    {
                        new_node->set_next(curr->get_next());
                        this->tail = new_node;
                    }
                    else
                    {
                        new_node->set_next(curr->get_next());
                    }
                    curr->set_next(new_node);
                }
            }
            else
            {
                this->tail->set_next(new_node);
                this->tail = new_node;
            }
        }
    }

    Patient dequeue()
    {
        if (this->isEmpty())
        {
            cerr << "the queue is empty " << endl;
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
        Node *curr = this->head;
        while (curr != nullptr)
        {
            curr->get_key().print();
            curr = curr->get_next();
        }
    }

    friend ostream &operator<<(ostream &os, Queue &q)
    {
        q.stampa();
        return os;
    }
};

int main()
{
    Queue pronto_soccorso;
    pronto_soccorso.enqueue(Patient(1, "Franco", "verde"));
    pronto_soccorso.enqueue(Patient(2, "Mario", "rosso"));
    pronto_soccorso.enqueue(Patient(3, "Gianni", "verde"));
    pronto_soccorso.enqueue(Patient(4, "Paolo", "rosso"));
    pronto_soccorso.enqueue(Patient(5, "Francesco", "rosso"));
    pronto_soccorso.enqueue(Patient(6, "Manu", "verde"));

    cout << pronto_soccorso;
}