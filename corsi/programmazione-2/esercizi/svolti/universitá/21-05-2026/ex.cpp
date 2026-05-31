#include <iostream>
#include <queue>

using namespace std;

template <class T>
class Nodo
{
private:
    T key;
    Nodo *left;
    Nodo *right;
    Nodo *parent;

public:
    Nodo(const T &key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}

    // Getter
    const T &get_key() const { return this->key; }
    Nodo *get_left() const { return this->left; }
    Nodo *get_right() const { return this->right; }
    Nodo *get_parent() const { return this->parent; }

    // Setter
    void set_key(const T &key) { this->key = key; }
    void set_left(Nodo *left) { this->left = left; }
    void set_parent(Nodo *parent) { this->parent = parent; }
    void set_right(Nodo *right) { this->right = right; }
};

template <class T>
class BST
{
private:
    Nodo<T> *radice;

protected:
    Nodo<T>* get_radice() const { return this->radice; }
    
    void inserimento_bst_ricorsiva(const T& key, Nodo<T>* nodo)
    {
        // Se la chiave è MINORE, andiamo a SINISTRA
        if(key < nodo->get_key())
        {
            if (nodo->get_left() == nullptr)
            {
                Nodo<T>* child = new Nodo<T>(key);
                child->set_parent(nodo);
                nodo->set_left(child);
            }
            else
            {
                inserimento_bst_ricorsiva(key, nodo->get_left());
            }
        }
        // Se la chiave è MAGGIORE o UGUALE, andiamo a DESTRA
        else
        {
             if (nodo->get_right() == nullptr)
            {
                Nodo<T>* child = new Nodo<T>(key);
                child->set_parent(nodo);
                nodo->set_right(child); // Corretto: set_right e non set_left
         }

            else
            {
                inserimento_bst_ricorsiva(key, nodo->get_right());
            }
        }
    }

    void inorder(Nodo<T>* nodo)
    {
        if(nodo == nullptr)
        return;

        inorder(nodo->get_left());
        cout << nodo->get_key() << " ";
        inorder(nodo->get_right());
    }

public:
    BST() : radice(nullptr) {}

    BST* inserimento_bst(const T& key)
    {
        if (this->get_radice() == nullptr) // Aggiunte le parentesi ()
        {
            this->radice = new Nodo<T>(key);
        }
        else
        {
           inserimento_bst_ricorsiva(key, radice);
        }
        return this;
    }
};

int main()
{
    BST<int>* bst = new BST<int>();
    bst->inserimento_bst(50);
    bst->inserimento_bst(30);
    bst->inserimento_bst(70);
    bst->inserimento_bst(80);
    bst->inserimento_bst(12);
    bst->inserimento_bst(24);
    bst->inserimento_bst(12);
    delete bst; 
    return 0;
}