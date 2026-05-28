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
                    new_node->set_next(curr->get_next());
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
};

int main()
{
}