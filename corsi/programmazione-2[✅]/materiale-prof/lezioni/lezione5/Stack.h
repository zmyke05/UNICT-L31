#include "LinkedList.h"


template<class T> class Stack : protected LinkedList<T>
{
	using LinkedList<T>::LinkedList;
private:
	size_t anotherSize;

public:
	Stack<T>* pop()
	{
		LinkedList<T>::removeHead();
		return this;
	}
		
	Stack* push(LinkedNode<T>* node)
	{		
	  LinkedList<T>::insertHead(node);	// return (Stack*) LinkedList<T>::insertHead(node);
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

	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack)
	{
		os << static_cast<LinkedList<T>>(stack);
		return os;
	}
};