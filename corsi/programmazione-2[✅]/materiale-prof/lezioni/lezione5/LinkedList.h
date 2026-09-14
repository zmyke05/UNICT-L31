#include <iostream>
#include "LinkedNode.h"

#pragma once
template<class T> class LinkedList
{
private:
	LinkedNode<T>* tail;
	LinkedNode<T>* head;
public:
	LinkedList<T>(LinkedNode<T>* head) : head{ head }, tail{ head } {}
	LinkedList<T>() :  head{ nullptr }, tail{ nullptr } {}
	LinkedNode<T>* getHead() const { return head; }
	LinkedNode<T>* getTail() const { return tail; }	
	size_t getSize() const
	{		
		size_t num = 0;
		LinkedNode<T>* it = getHead();
		while (it != nullptr)
		{
			num++;			
			it=it->getNext();
		}
		return num;
	}
	
	bool isEmpty() const
	{
		return getHead()==nullptr && getTail()==nullptr;
	}

	LinkedList<T>* insertHead(LinkedNode<T>* node)
	{
		if (head != nullptr)
			node->setNext(head);
		else
			tail = node;
		head = node;
		return this;
	}

	LinkedList<T>* insertTail(LinkedNode<T>* node)
	{
		if (tail != nullptr)		
			tail->setNext(node);
		else
			head = node;
		tail = node;		
		return this;		
	}

	

	LinkedList<T>* insertAfter(const T& key, LinkedNode<T>* node)
	{
		if (head == nullptr)
		{
			insertHead(node);
			return this;
		}

		LinkedNode<T>* it = head;
		while (it != nullptr)
		{
			if (key == it->getKey())
			{				
				node->setNext(it->getNext());
				it->setNext(node);
				if(node->getNext()==nullptr)// more safe then if (it == tail)
				   tail = node;	
				break;
			}
			it = it->getNext();
		}
		return this;
	}

	LinkedList<T>* insertBefore(const T& key, LinkedNode<T>* node)
	{		
		if (head == nullptr)
		{			
			insertHead(node);
			return this;
		}
		LinkedNode<T>* prev = nullptr;
		LinkedNode<T>* it = head;		
		while (it != nullptr)
		{
			if (key == it->getKey())
			{				
				if (prev == nullptr)
				{					
					node->setNext(head);
					head = node;
				}
				else
				{					
					prev->setNext(node);
					node->setNext(it);
				}
				break;
			}
			prev = it;
			it = it->getNext();			
		}
		return this;
	}

	LinkedList<T>* insertInOrder(LinkedNode<T>* node)
	{
		if (head == nullptr)
		{
			insertHead(node);
			return this;
		}
		LinkedNode<T>* prev = nullptr;
		LinkedNode<T>* it = head;
		while (it != nullptr)
		{
			if (node->getKey() <= it->getKey())
			{
				if (prev == nullptr)
				{
					node->setNext(head);
					head = node;
				}
				else
				{
					prev->setNext(node);
					node->setNext(it);
				}
				break;
			}
			prev = it;
			it = it->getNext();
		}
		if (it == nullptr)
			insertTail(node);
		return this;
	}

	LinkedNode<T>* removeTail()
	{
		LinkedNode<T>* tmp = tail;
		if (tmp != nullptr)
		{
			LinkedNode<T>* it = head;
			LinkedNode<T>* prev = nullptr;
			while (it != nullptr)
			{
				if (it->getNext() == nullptr)
				{
					tail = prev;					
					if (prev == nullptr)					
						 head= nullptr;		
					else
						tail->clearNext();
					break;
				}
				prev = it;
				it = it->getNext();
			}
		}
		tmp->clearNext();
		return tmp;
	}

	LinkedNode<T>* removeHead()
	{
		LinkedNode<T>* tmp = head;
		if (head != nullptr)
		{
			if (head->getNext() == nullptr)
			{
				head = tail = nullptr;
			}
			else
				head = head->getNext();
			tmp->clearNext();
		}
		return tmp;
	}

	LinkedNode<T>* remove(const T& key)
	{
		if (head == nullptr)
			return nullptr;	
		LinkedNode<T>* prev = nullptr;
		LinkedNode<T>* it = head;
		while (it != nullptr)
		{
			if (it->getKey() == key)
			{
				if (prev == nullptr) //head
				{
					if (it->getNext() != nullptr)
					{
						head = it->getNext();
					}
					else
					{
						head = tail = nullptr;
					}
				}
				else
				{
					prev->setNext(it->getNext());
					if (it->getNext() == nullptr)
						tail = prev;
				}
				break;
			}
			prev = it;
			it = it->getNext();
		}
		if(it!=nullptr)
		   it->clearNext();
		return it;		
	}
	
	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
	{
		LinkedNode<T>* it = list.getHead();
		while (it != nullptr)
		{
			os << it->getKey() << " ";
			it = it->getNext();
		}
		return os;
	}
};


