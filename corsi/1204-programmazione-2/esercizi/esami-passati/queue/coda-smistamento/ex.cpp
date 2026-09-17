
#include <iostream>
#include <string>
using namespace std;

class Pacchetto
{
private:
    int codice_univoco;
    string destinazione;
    double peso;

public:
    Pacchetto(const int codice_univoco, const string destinazione, const double peso) : codice_univoco(codice_univoco), destinazione(destinazione), peso(peso) {}

    int get_codice_univoco() const { return codice_univoco; }
    string get_destinazione() const { return destinazione; }
    double get_peso() const { return peso; }

    friend ostream &operator<<(ostream &os, const Pacchetto &p);
};

ostream &operator<<(ostream &os, const Pacchetto &p)
{

    os << "[ codide: " << p.get_codice_univoco() << "]" << "destinazione:" << p.get_destinazione() << "(" << p.get_peso() << ")";
    return os;
}

class Node
{
private:
    Pacchetto data;
    Node *next;

public:
    Node(Pacchetto p) : data(p), next(nullptr) {}

    Node *get_next() const { return next; }
    Pacchetto get_data() const { return data; }
    void set_next(Node *next) { this->next = next; }
};

class SplitQueue
{
private:
    Node *head;

public:
    SplitQueue() : head(nullptr) {}
    Node *get_head() const { return this->head; }
    bool isEmpty() { return head == nullptr; }

    void enqueue(Pacchetto p)
    {
        Node *new_node = new Node(p);
        if (isEmpty())
        {
            head = new_node;
            return;
        }

        if (p.get_peso() > 20)
        {
            Node *curr = head;
            Node *prev = nullptr;

            while (curr != nullptr && curr->get_data().get_peso() > 20)
            {
                prev = curr;
                curr = curr->get_next();
            }

            if (prev == nullptr)
            {
                new_node->set_next(head);
                head = new_node;
            }
            else
            {

                new_node->set_next(curr);
                prev->set_next(new_node);
            }
        }
        else
        {

            Node *curr = head;
            while (curr->get_next() != nullptr)
            {
                curr = curr->get_next();
            }
            curr->set_next(new_node);
        }
    }

    void dequeue()
    {
        Node *tmp = head;
        cout << tmp->get_data() << endl;

        head = head->get_next();
        delete tmp;
    }
};

int main()
{

    SplitQueue linea_produzione;

    Pacchetto p1(101, "roma", 12.5);
    Pacchetto p2(99, "Milano", 35.0);
    Pacchetto p3(102, "Napoli", 8.2);

    linea_produzione.enqueue(p1);
    linea_produzione.enqueue(p2);
    linea_produzione.enqueue(p3);

    while (linea_produzione.get_head() != nullptr)
    {

        linea_produzione.dequeue();
    }
}
