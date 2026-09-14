#include <iostream>

using namespace std;

template <class T>
class Node
{
private:
    T key;
    Node<T>* next_1;
    Node<T>* next_2;

public:
    Node<T>* get_next_1() const { return this->next_1; }
    void set_next_1(Node<T>* next_1) { this->next_1 = next_1; } 

    Node<T>* get_next_2() const { return this->next_2; }
    void set_next_2(Node<T>* next_2) { this->next_2 = next_2; } 

    T get_key() const { return this->key; }
};

int main()
{

}