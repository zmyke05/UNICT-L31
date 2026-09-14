#include <iostream>
#include "printable.h"


using namespace std;

//#pragma once
#ifndef MANUSCRIPT_H
#define MANUSCRIPT_H
class Manuscript : public Printable
{
private:
	string author;
	string title;

public:
	 Manuscript(string author, string title) : author{ author }, title{ title } {}
     
	 /*
	 * Deafult constructor
	 */
	 //Book() : author{ "" }, title{ "" } {}; 
	 Manuscript() = default; //default constructor
	 
   	
	/*
	*  Override the default destructor
	*/
	~Manuscript() { cout << "object destructed" << endl; }

	string getAuthor() const 
	{
		return this->author;
	}

	string getTitle() const 
	{
		return this->title;
	}

	void setAuthor(const string author)
	{
		this->author = author;
	}

	void setTitle(const string title)
	{
		this->title = title;
	}	

	string getLabel() const override
	{
		return "Author: " + this->getAuthor() + ". Title: " + this->getTitle() + ". ";
	}
	
	virtual bool is_equal(const Manuscript& other) const
	{
		const Manuscript* m = dynamic_cast<const Manuscript*>(&other);
		if (!m) 
			return false;
		return this->getAuthor() == m->getAuthor() && this->getTitle() == m->getTitle();
	}

	
	

	//<< overloading, friend and inline
	friend ostream& operator<<(ostream& os, const Manuscript& m)
	{
		os << m.getLabel();
		return os;
	}

	/*
	* For Manuscritpt << Manuscript;
	Manuscript& operator<<(const Manuscript& m)
	{
		this->author = m.getAuthor();
		this->title = m.getTitle();
		return *this;
	}	
	*/


	/*
     *  Override the default copy constructor

     Manuscript(const Manuscript& manu) : author{ "Copied " + manu.author }, title{ "Copied " + manu.title} {}

     *  Override the default move constructor

     Manuscript(Manuscript&& manu) : author{ "Move Source Author" + manu.author }, title{ "Moved Source Title" + manu.title } {}
    */

	/*
	//operators copy and move constructor overloading
	Manuscript& operator=(const Manuscript&) 
	{
		//do copy
		return *this; 
	}
	Manuscript& operator=(Manuscript&&) 
	{ 
		//do move
		return *this;
	}
	*/
};

#endif


