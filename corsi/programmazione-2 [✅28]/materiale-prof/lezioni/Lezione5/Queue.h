#include "LinkedList.h"


template<class T> class Queue : protected LinkedList<T>
{
	using LinkedList<T>::LinkedList;
private:
	size_t anotherSize;

public:
	Queue<T>* enqueue(LinkedNode<T>* node)
	{
		LinkedList<T>::insertTail(node);
		return this;
	}

	Queue* dequeue()
	{
		LinkedList<T>::removeHead();
		return this;
	}

	bool isEmpty()
	{
		return LinkedList<T>::isEmpty();
	}

	size_t getSize()
	{
		return LinkedList<T>::getSize();
	}

	
	friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue)
	{
		os << static_cast<LinkedList<T>>(queue);
		return os;
	}
};