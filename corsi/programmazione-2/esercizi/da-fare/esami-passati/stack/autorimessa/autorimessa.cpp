#include <iostream>

using namespace std;

class Auto
{

};

class CicloMotore
{

};

class Veicolo
{
private:
    string targa;
};

class Parcheggio
{
private:
    string cod_parcheggio;
};

class Autorimessa
{
private:
    string cod_autorimessa;
};

class Node
{
private:
    Veicolo *key;
    Node *next;

public:
    Node(Veicolo *key) : key(key), next(nullptr) {}
    ~Node() {}

    Veicolo *get_key() const { return this->key; }
    Node *get_next() const { return this->next; }
    void set_next(Node *next) { this->next = next; }
};

int main()
{

}