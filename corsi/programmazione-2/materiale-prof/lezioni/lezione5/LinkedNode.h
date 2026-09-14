#pragma once
template<class T> class LinkedNode
{
 private:
	 LinkedNode* next;
	 T key;
 public:
	LinkedNode<T>() : next{ nullptr } {};
	LinkedNode<T>(T key) : key{ key }, next{ nullptr } { };
	
	LinkedNode<T>* getNext() const { return next; }
	T getKey() const { return key; }

	void setNext(LinkedNode* next) { this->next = next; }	
	void setKey(T& key) { this->key = key; }

	LinkedNode<T>* removeNext()
	{
		delete next;
		next = nullptr;
		return this;
	}

	LinkedNode<T>* clearNext()
	{
		next = nullptr;
		return this;
	}

	friend std::ostream& operator<<(std::ostream& os, const LinkedNode<T>& node)
	{
		os << node.getKey();
		return os;
	}
};