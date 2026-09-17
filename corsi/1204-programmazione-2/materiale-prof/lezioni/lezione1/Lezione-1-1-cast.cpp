#include <iostream>

using namespace std;

int main()
{
	//implicit
	int i = 65;
	double d = i;
	cout << fixed << "Casting int to double: " << d << endl;

	char c = i;
	cout << "Casting int to char: " << c << endl;

	//explicit
	double d2 = 75;
	int i2 = int(d2);
	cout << fixed << "Casting double to int: " << i2 << endl;
	cout << fixed << "Casting double to int: " << static_cast<int>(i2) << endl;


	char c1 = 10;
	//int* i3 = &c1 //not allowed in C++
	//int* i3 = (int*)&c1; //allowed in C++	but unsafe
	//int* i3 = static_cast<int*>(&c1); //c++  compile-time error	
	int* i3 = reinterpret_cast<int*>(&c); //undefined behavior

	return 0;
}