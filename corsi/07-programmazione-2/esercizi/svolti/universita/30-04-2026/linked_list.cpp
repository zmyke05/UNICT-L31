#include <iostream>
using namespace std;

template <class T>
class LinkedNode
{
private:
    T key;
    LinkedNode<T> *next;

public:
    LinkedNode(const T &key) : key(key), next(nullptr) {}

    const T &get_key() const { return key; }
    LinkedNode<T> *get_next() const { return next; }
    void set_key(const T &key) { this->key = key; }
    void set_next(LinkedNode<T> *next) { this->next = next; }
};

template <class T>
ostream &operator<<(ostream &os, const LinkedNode<T> *node)
{
    os << node->get_key();
    return os;
}

template <class T>
class LinkedList
{
private:
    LinkedNode<T> *head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}

    bool is_empty() const { return head == nullptr; }

    LinkedList<T> *insert_head(const T &key)
    {
        LinkedNode<T> *new_head = new LinkedNode<T>(key);
        if (!this->is_empty() == false)
            new_head->set_next(head);
        this->head = new_head; // Directly set head instead of calling set_head
        this->size++;
        return this; // Return this pointer to allow chaining
    }

    LinkedList* insert_key(const T& key)
    {
        LinkedNode<T>* ptr = 21
    }

    const T* search_key(const T& key) const
    {
        /* if (this->is_empty())
        {
            return nullptr;
        } */
        /* LinkedNode<T>* ptr = this->head;
        while (ptr != nullptr && ptr->get_key() != key)
        {
            ptr = ptr->get_next();
        }
        if (ptr == nullptr)
        {
            return nullptr;
        }
        else {
            return &ptr->get_key();
        } */
       LinkedNode<T>* node = this->search_key(key);
       if (node == nullptr)
       {
            return nullptr;
       }

       return ptr;
       
    }

    const T *get_head()
    {
        if (this->is_empty())
        {

            return nullptr;
        }
        return &this->head->get_key();
    }

    size_t get_size() const { return size; }

    // Destructor to free memory
    ~LinkedList()
    {
        LinkedNode<T> *current = head;
        while (current != nullptr)
        {
            LinkedNode<T> *next = current->get_next();
            delete current;
            current = next;
        }
    }
    protected:
     LinkedList* set_head(LinkedNode<T>* new_head){}
};


int main()
{
    LinkedList<int> *l = new LinkedList<int>();
    cout << l->is_empty() << endl; // Output: 1 (true)
    l->insert_head(80)->insert_head(100);
    cout << l->is_empty() << endl; // Output: 0 (false)

    delete l; // Don't forget to delete the linked list
    cout << l->get_head() << endl;

    cout << *(l->search_key(80)) << endl;
    if (l->search_key(192) == nullptr)
    {
        cout << "Chiave non trovata" << endl;
    }
    
    return 0;
}