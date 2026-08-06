#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T key;
    Node<T> *next;

public:
    Node(const T key) : key(key), next(nullptr) {}

    T get_key() const { return this->key; }
    Node *get_next() const { return this->next; }
    void set_next(Node *new_next) { this->next = new_next; }
};

template <class T>
class Stack
{
private:
    Node<T> *top;
    size_t size;

public:
    Stack() : top(nullptr), size(0) {}
    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    bool isEmpty() { return this->top == nullptr; }
    void push(T val)
    {
        Node<T> *new_node = new Node<T>(val);
        new_node->set_next(this->top); // Il nuovo nodo punta al vecchio top (verso il basso)
        this->top = new_node;          // Il top dello stack diventa il nuovo nodo
        this->size++;
    }

    T pop()
    {
        if (this->isEmpty())
        {
            cerr << "The queue is empty";
            return -1;
        }
        else
        {
            Node<T> *tmp = this->top;
            this->top = this->top->get_next();

            T val_estratto = tmp->get_key();
            delete tmp;

            this->size--;
            return val_estratto;
        }
    }

    void stampa()
    {
        Node<T> *cur = this->top;
        while (cur != nullptr)
        {
            cout << cur->get_key() << " ";
            cur = cur->get_next();
        }
    }
};

int main()
{
    Stack<int> stack;
    stack.push(50);
    stack.push(20);
    stack.push(15);

    stack.stampa();
}
