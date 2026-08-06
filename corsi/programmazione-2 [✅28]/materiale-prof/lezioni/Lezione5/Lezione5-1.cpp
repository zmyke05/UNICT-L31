#include <iostream>
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;


int main()
{
	LinkedNode<int>* n = new LinkedNode<int>(3);	
	cout << *n << endl;
	n->setNext(new LinkedNode<int>(9));
	cout << n->getNext()->getKey() << endl;
	n->removeNext();
	cout << ((n->getNext() == nullptr) ? "No next" : to_string(n->getNext()->getKey())) << endl;	
	cout << "Check List" << endl;
	LinkedList<int>* list = new LinkedList<int>();
	list->insertHead(new LinkedNode<int>(3));
	list->insertTail(new LinkedNode<int>(5));	
	list->insertTail(new LinkedNode<int>(9));
	list->insertHead(new LinkedNode<int>(1));
	cout << "Tail: " << *list->getTail() << endl;
	cout << "Head: " << *list->getHead() << endl;
	list->insertAfter(5, new LinkedNode<int>(7));
	list->insertAfter(9, new LinkedNode<int>(11));
	list->insertBefore(7, new LinkedNode<int>(6));
	list->insertBefore(1, new LinkedNode<int>(0));
	list->insertInOrder(new LinkedNode<int>(-1));
	list->insertInOrder(new LinkedNode<int>(12));
	list->insertInOrder(new LinkedNode<int>(4));
	cout << *list << endl;
	cout << "Pop: " << to_string(list->removeTail()->getKey()) << endl;
	cout << "Pop: " << to_string(list->removeTail()->getKey()) << endl;
	cout << "Pop Head: " << to_string(list->removeHead()->getKey()) << endl;
	cout << "Pop Head: " << to_string(list->removeHead()->getKey()) << endl;
	cout << "All elements" << endl;
	cout<< *list<<endl;
	cout << "Tail: " << ((list->getTail() == nullptr) ? "Null Tail" : to_string(list->getTail()->getKey())) << endl;
	cout << "Head: " << ((list->getHead() == nullptr) ? "Null Head" : to_string(list->getHead()->getKey())) << endl;
	cout << "Pop: " << to_string(list->removeHead()->getKey()) << endl;
	cout << "Tail: " << ((list->getTail() == nullptr) ? "Null Tail" : to_string(list->getTail()->getKey())) << endl;
	cout << "Head: " << ((list->getHead() == nullptr) ? "Null Head" : to_string(list->getHead()->getKey())) << endl; 
	cout<< *list<<endl;
	cout<<"Remove: " << list->remove(9)->getKey() << endl;
	cout << *list << endl;
	cout << "Remove: " << list->remove(3)->getKey() << endl;
	cout << *list << endl;
	cout << "Remove: " << list->remove(6)->getKey() << endl;
	cout << *list << endl;
	cout << "Remove: " << list->remove(5)->getKey() << endl;
	cout << *list << endl;
	cout << "Remove: " << list->remove(7)->getKey() << endl;
	cout << *list << endl;
	cout << "Remove: " << list->remove(4)->getKey() << endl;
	cout << *list << endl;
	cout << "Remove: 10" << endl;
	list->remove(10);
	cout << "Tail: " << ((list->getTail() == nullptr) ? "Null Tail" : to_string(list->getTail()->getKey())) << endl;
	cout << "Head: " << ((list->getHead() == nullptr) ? "Null Head" : to_string(list->getHead()->getKey())) << endl;
	cout<<*list<<endl;

	Stack<int>* stack = new Stack<int>();
	stack->push(new LinkedNode<int>(7));
	stack->push(new LinkedNode<int>(10));
	stack->push(new LinkedNode<int>(11));
	stack->pop();
	cout << *stack << endl;
	cout << stack->getSize() << endl;
	cout << stack->isEmpty() << endl;

	Queue<int>* queue = new Queue<int>();
	queue->enqueue(new LinkedNode <int>(5))->enqueue(new LinkedNode <int>(7))->enqueue(new LinkedNode <int>(3));
	cout << *queue << endl;
	return 0;
	
}