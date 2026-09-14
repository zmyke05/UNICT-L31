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
class Coda
{
private:
    Node<T> *tail;
    Node<T> *cache_tail;
    Node<T> *head;
    Node<T> *cache_head;
    size_t cache_size;

public:
    Coda() : tail(nullptr), cache_tail(nullptr), head(nullptr), cache_head(nullptr), cache_size(0) {}
    ~Coda() {}

    bool isEmpty() const { return this->head == nullptr; }

    void enqueue(T value)
    {
        Node<T> *new_node = new Node<T>(value);
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

    T dequeue()
    {
        if (this->isEmpty())
        {
            cerr << "The queue is empty\n";
            exit(1);
        }
        else
        {
            Node<T> *tmp_node = this->head;
            this->head = this->head->get_next();
            if (this->isEmpty())
            {
                this->tail = nullptr;
            }

            T tmp_key = tmp_node->get_key();
            tmp_node->set_next(nullptr);
            if (this->cache_head == nullptr)
            {
                this->cache_head = tmp_node;
                this->cache_tail = tmp_node;
                cache_size++;
            }
            else
            {
                this->cache_tail->set_next(tmp_node);
                this->cache_tail = tmp_node;
                cache_size++;
                if (cache_size > 3)
                {
                     Node<T> *tmp = this->cache_head;
                     this->cache_head = this->cache_head->get_next();
                     delete tmp;
                     cache_size--;
                }
            }

            return tmp_key;
        }
    }
};

int main()
{
}