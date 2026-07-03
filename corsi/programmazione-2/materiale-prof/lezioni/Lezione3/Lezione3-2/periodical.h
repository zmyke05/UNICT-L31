#include "manuscript.h"

class Periodical : public Manuscript
{
private:
	int frequency;
public:
	Periodical(string author, string title, int frequency) : Manuscript(author, title),  frequency{frequency} {}
	int getFrequency() const
	{
		return this->frequency;
	}
	string getLabel() const override
	{
		return Manuscript::getLabel() + "Frequency: " + to_string(this->getFrequency()) + ". ";
	}

	bool is_equal(const Manuscript& other) const override 
	{
		const Periodical* m = dynamic_cast<const Periodical*>(&other);
		  if (!m) 
			  return false;
		return Manuscript::is_equal(other) && this->getFrequency()== m->getFrequency();
	}
};


bool operator==(const Manuscript& l1, const Manuscript& l2)
{
	return  l1.is_equal(l2);
}