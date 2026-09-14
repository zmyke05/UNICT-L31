#include "manuscript.h"

template <class T> class Shelf
{
private:
    T* objects;
    int size;
    int capacity;
public:
    Shelf(const int& capacity)
    { 
      this->capacity = capacity;
      this->size = 0;
      objects = new T[capacity];      
    }

    Shelf() { objects = NULL; size = 0; }

    bool add(const T *element)
    {
        if (size < capacity)
        {
            objects[size] = *element;
            size++;
            return true;
        }
        return false;
    }

    int getSize() const
    {
        return this->size;
    }

    int getCapacity() const
    {
        return this->capacity;
    }

    T* getElement(const int& pos)
    {
        if (pos <= capacity)
            return &(this->objects[pos]);
        return NULL;
    }

     void print();
};


template<class T> void Shelf<T> ::print()
{
    for (int i = 0; i < this->getCapacity(); i++)
        cout << *(this->getElement(i)) << endl;
};