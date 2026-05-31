#include <iostream>

using namespace std;

template<class T> class Node 
{
private:
	T key;
	Node<T>* next;
public:
	Node(const T& key) : key(key), next(nullptr){}
	Node* getNext() { return next; }
	void set_next(Node* new_node) { this->next = new_node; }
	const T& get_key() const { return key; }
};

template<class T> class Queue
{
    private:
        Node<T>* head; 
        Node<T>* tail; 
        size_t size;
    
    public:
        Queue() : head(nullptr), tail(nullptr), size(0) {} 
        const size_t& get_size() const { return size; }
        const T& get_head_key() const { return head->getKey(); }
        const T& get_tail_key() const { return tail->getKey(); }
        bool is_empty() const { return head == nullptr; }
        Queue* enqueue(const T& key)
        {
            Node<T>* new_head = new Node<T>(key);
            if (this->is_empty())
            {
                this->set_tail(new_head);
            }
            new_head->set_next(this->head);
            head = new_head;
            increase_size();
            return this; 
        }

        Queue* dequeue()
        {
            if (this->is_empty())
            {
                return this;
            }
            if (this->get_head == this->get_tail )
            {
                this->set_head(nullptr);
            }
            this->decrease_size;
        }

    protected:
        Node<T>* get_head() const { return head; }
        Node<T>* get_tail() const { return tail; } 

        // Setter 
        void set_head(Node<T>* head) { this->head = head; }
        void set_tail(Node<T>* tail) { this->tail = tail; }
        void increase_size() { this->size++; } // verificare prima size
        void decrease_size() { this->size--; }
 };

int main()
{
    Queue<int>* q = new Queue<int>();
    q->enqueue(50);
    cout << q->get_head_key() << endl;
    cout << q->get_tail_key() << endl;

    q->enqueue(89);

    cout << q->get_head_key() << endl;
    cout << q->get_tail_key() << endl;
}