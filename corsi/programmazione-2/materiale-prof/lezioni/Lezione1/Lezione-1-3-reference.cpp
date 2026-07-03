#include <iostream>

using namespace std;

int main()
{
	int i = 45;
	int &ref = i;

	i = i + 1;

	cout << "i" << endl;
	cout << i << endl;
	cout << &i << endl;    

	cout << "Reference" << endl;

	cout << ref << endl;	
	cout << &ref << endl;
	
	int* pointer = &i;

	cout << "Pointer" << endl;
	cout << pointer << endl;
	cout << &pointer << endl;
	cout << *pointer << endl;

	return 0;
}