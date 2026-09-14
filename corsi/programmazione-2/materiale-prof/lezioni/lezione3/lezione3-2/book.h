#include "manuscript.h"

class Book : public Manuscript
{
private:
	int year;
public:
	Book(string author, string title, int year) : Manuscript(author, title), year{ year } {}
	Book() = default;
	int getYear() const
	{ 
		return this->year;
	}

	void setYear(int year)
	{
		this->year = year;
	}

	string getLabel() const
	{
		return Manuscript::getLabel() + "Year: " + to_string(this->getYear())+". ";
	}

	bool is_equal(const Manuscript& other) const override
	{
		const Book* b = dynamic_cast<const Book*>(&other);
		if (!b)
			return false;
		return Manuscript::is_equal(other) && this->getYear() == b->getYear();
	}
	
};
