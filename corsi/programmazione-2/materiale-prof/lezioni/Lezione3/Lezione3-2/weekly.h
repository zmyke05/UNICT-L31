#include "periodical.h"

class Weekly : public Periodical
{
  public:
	  Weekly(string author, string title) : Periodical(author, title, 7) {}	  

};