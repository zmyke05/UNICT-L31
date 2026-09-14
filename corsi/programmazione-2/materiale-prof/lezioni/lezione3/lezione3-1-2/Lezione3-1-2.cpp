#include <iostream>
#include "book.h"

using namespace std;

void Book::print()
{
	cout << "Title: " << this->getTitle() << "; author: " << this->getAuthor() << endl;
}


int main()
{
	Book b("Tolkien", "Lord of the Rings"); //Book b{ "Tolkien", "Lord of the Rings" };
	cout << b.getAuthor() << endl;
	cout << b.getTitle() << endl;

	b.setAuthor("J.R.R. Tolkien");
	cout << b.getAuthor() << endl;

	Book* b1 = new Book(b.getAuthor(), "The Silmarillion");
	cout << b1->getTitle() << endl;

	/*
	  Initialization by copy
	*/

	Book b2 = { b };
	Book b3 (b);
	
	b.setTitle("The Lord of the Rings");
	cout << "B title: "<< b.getTitle() << endl;
	cout << "B2 title: " << b2.getTitle() << endl;
	cout << "B2 author: " << b2.getAuthor() << endl;
	cout << "B3 title: " << b3.getTitle() << endl;
    Book b4; 
	cout << "Default constructor: " << b4.getAuthor() << endl;
	//Book b7(); //error,it looks like we defined a function
	Book b7 = { "Test", "Prova" }; 
	
	Book b5 {}; //default constructor
	cout << "B5 author: " <<  b5.getAuthor() << endl;
	
	Book b6 ("Another Great Author", "Another Great book");
	Book b8 = move(b6);
	cout << "B6 author: " << b6.getAuthor() << " ( should be empty)"<<endl;
	cout << "B8 author: " << b8.getAuthor() << endl;
	
}