#include<iostream>
#include<array>
#include<vector>
#include<iterator>

using namespace std;

int main()
{
  cout << "Static-Memory array" << endl;
  const size_t size = 8;
  array<int, size> myarr;
  cout<<"Array size: "<<myarr.size() << endl;  
  for (int i = 0; i < myarr.size(); i++)
	  //myarr[i] = i + 1;
	  myarr.at(i) = i + 1;
  cout << "Printing array" << endl;
  for (int i : myarr)
	  cout << i << endl;
  cout << "Printing array" << endl;
  for (array<int,8>::iterator it = myarr.begin(); it != myarr.end(); it++)
  {
	  cout << *it << " " << distance(myarr.begin(), it) << endl;
  }

  cout << "Dynamic-Memory Array" << endl;
  const size_t size2 = 8;
  array<int, size2>* dynarr = new array<int, size2>();
  cout << "Array Size: " << dynarr->size() << endl;
  for (int i = 0; i < dynarr->size(); i++)
  {
	  //(*dynarr)[i] = i + 3;
	  dynarr->at(i) = i + 3;
  }
  for (int i : *dynarr)
	  cout << i << endl;

  delete dynarr;
  size_t size3 = 8;
  vector<int> vect = vector<int>(size3);
  cout << vect.size() << endl;
  for (int i = 0; i < vect.size(); i++)
	  vect.at(i) = i;
  vect.push_back(39);
  vect.push_back(89);
  vect.insert(vect.begin() + 2, 66);
  cout << vect.size() << endl;
  cout << vect.at(0) << endl;
  
  for (vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
	  cout << *it << " "<< distance(vect.begin(), it) << endl;
  
  for (auto i : vect)
	  cout << i << endl;

  return 0;
}