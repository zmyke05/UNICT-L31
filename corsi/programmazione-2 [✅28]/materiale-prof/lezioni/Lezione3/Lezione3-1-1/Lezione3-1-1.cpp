#include <iostream>
#include "mybook.h"

using namespace std;


int main()
{
	MyBook m("Fodamenti di Programmazione in C++", "Luis Joyanes Aguilar");
	cout << m.getTitle() << endl;
	cout << m.getAuthor() << endl;
}