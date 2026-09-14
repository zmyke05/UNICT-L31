#include <iostream>

/*
  For the sake of simplicity, hearder and implementation are in the same file
*/

using namespace std;

class Book
{
private:
	string author;
	string title;

public:
	 Book(string author, string title) : author{ author }, title{ title } {};
     
	 /*
	 * Deafult constructor
	 */
	 //Book() : author{ "" }, title{ "" } {}; 
	 Book() = default; //default constructor
	 

	/*
	*   Override the default copy constructor
	*/
	Book(const Book& book) : author{ "Copied " + book.author }, title{ "Copied " + book.title} {}

	/*
	*   Override the default move constructor
	*/
	Book(Book &&book)
	{
		this->author = move(book.author); //book.author is now in a valid empty state
		this->title = move(book.title); //title.title is now in a valid empty state
	}
	
	/*
	*  Override the default destructor
	*/
	~Book() { cout << "object destructed" << endl; }

	const string getAuthor() const
	{
		return this->author;
	}

	const string getTitle() const
	{
		return this->title;
	}

	void setAuthor(const string& author)
	{
		this->author = author;
	}

	void setTitle(const string& title)
	{
		this->title = title;
	}
	
	void print();
};



