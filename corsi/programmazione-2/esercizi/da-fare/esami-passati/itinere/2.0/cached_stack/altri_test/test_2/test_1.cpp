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
    T get_key() const { return this->key; }

    void set_next(Node<T> *next) { this->next = next; }
};

template <class T>
class CachedStack
{
private:
    Node<T> *top;
    Node<T> *cache_top;
    size_t cache_size;

public:
    CachedStack() : top(nullptr), cache_top(nullptr), cache_size(0) {}
    ~CachedStack() {}

    bool isEmpty() const { return this->top == nullptr; }
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

        Node<T> *tmp_node = this->top;
        this->top = this->top->get_next();
        T tmp_key = tmp_node->get_key();
        tmp_node->set_next(this->cache_top);
        this->cache_top = tmp_node;
        this->cache_size++;
        Node<T> *curr = this->cache_top;
        if (cache_size > 4)
        {
            for (size_t i = 0; i < 3; i++)
            {
                curr = curr->get_next();
            }

            Node<T> *buffer = curr->get_next();
            curr->set_next(nullptr);
            delete buffer;
            this->cache_size--;
        }
    }

    void undo()
    {
        if (this->cache_top == nullptr)
        {
            cerr << "The cache is empty\n";
            exit(1);
        }

        Node<T> *buffer = this->cache_top;
        this->cache_top = cache_top->get_next();
        buffer->set_next(this->top);
        this->top = buffer;
        this->cache_size--;
    }
};

int main()
{
}