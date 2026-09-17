#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
	T key;
	Node<T>* next;

public:
	Node(const T key) : key(key), next(nullptr) {}

	T get_key() const { return this->key; }
	Node *get_next() const { return this->next; }
	void set_next(Node *new_next) { this->next = new_next; }
};

template<class T>
class Queue
{
private:
	Node<T>* head;
	Node<T>* tail;
	size_t size;

public:
	Queue() : head(nullptr), tail(nullptr), size(0) {}
	~Queue()
	{
		while (!isEmpty())
		{
			dequeue();
		}
	}

	bool isEmpty() { return this->head == nullptr; }
	void enqueue(T val)
	{
		Node<T>* new_node = new Node<T>(val);
		if (this->isEmpty())
		{
			this->head = new_node;
			this->tail = new_node;
		}
		else
		{
			this->tail->set_next(new_node);
			this->tail = new_node();
		}
		this->size++;
	}

	T dequeue()
	{
		if (this->isEmpty())
		{
			cerr << "The queue is empty";
			return -1;
		}
		else
		{
			Node<T>* tmp = this->head;
			this->head = this->head->get_next();

			if (this->isEmpty())
			{
				this->tail = nullptr;
			}

			T val_estratto = tmp->get_key();
			delete tmp;

			this->size--;
			return val_estratto;
		}
	}

	void stampa()
	{
		Node<T>* cur = this->head;
		cout << " head ->  ";
		while (cur != nullptr)
		{
			cout << cur->get_key() << " ";
			cur = cur->get_next();
		}

		cout << " <- tail" << endl;
	}
};

int main()
{
	Queue<int> coda;
	coda.enqueue(50);
	coda.enqueue(20);
	coda.enqueue(15);

	coda.stampa();

	int a = coda.dequeue();

	coda.stampa();
}
