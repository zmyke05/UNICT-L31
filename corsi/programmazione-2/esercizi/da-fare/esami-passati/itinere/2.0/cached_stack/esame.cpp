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
    ~Node() {}

    Node<T> *get_next() const { return this->next; }
    void set_next(Node<T> *next) { this->next = next; }

    T get_key() const { return this->key; }
};

template <class T>
class ChachedStack
{
private:
    Node<T> *top;
    Node<T> *cache_top;
    size_t cache_size;

public:
    ChachedStack() : top(nullptr), cache_top(nullptr), cache_size(0) {}
    ~ChachedStack() {}

    bool isEmpty() { return this->top == nullptr; }

    size_t cache_undo_size() const { return this->cache_size; }

    void push(T value)
    {
        Node<T> *new_node = new Node<T>(value);
        new_node->set_next(this->top);
        this->top = new_node;
    }

    T pop()
    {
        if (this->isEmpty())
        {
            cerr << "The stack is empty\n";
            exit(1);
        }
        else
        {
            Node<T> *tmp_node = this->top;
            this->top = this->top->get_next();
            T tmp_key = tmp_node->get_key();
            tmp_node->set_next(this->cache_top);
            this->cache_top = tmp_node;
            cache_size++;
            Node<T> *curr = this->cache_top;
            if (cache_size > 4)
            {
                for (size_t i = 0; i < 3; i++)
                {
                    curr = curr->get_next();
                }
                Node<T> *nodo_da_eliminare = curr->get_next();
                curr->set_next(nullptr);
                delete nodo_da_eliminare;
                this->cache_size--;
            }
            return tmp_key;
        }
    }

    void undo()
    {
        if (this->cache_top == nullptr)
        {
            cerr << "The cache is empty\n";
            exit(1);
        }

        Node<T> *tmp_cache_node = this->cache_top;
        this->cache_top = this->cache_top->get_next();
        tmp_cache_node->set_next(this->top);
        this->top = tmp_cache_node;
        cache_size--;
    }

    void print_cache()
    {
    }

    void print(ostream &os) const
    {
        Node<T> *current = this->top;
        while (current != nullptr)
        {
            os << current->get_key() << " ";
            current = current->get_next();
        }
    }
};

int main()
{
}