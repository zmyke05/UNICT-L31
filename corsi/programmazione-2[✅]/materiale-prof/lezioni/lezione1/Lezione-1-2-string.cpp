#include<iostream>


using namespace std;

int main()
{
	string s = "Primo Messaggio";
	string s1 = "Secondo Messaggio";
	cout << s << endl;
	string s2 = s + " "+ s1;
	cout << s2 << endl;
	cout << s2.at(3) << endl;
	cout << s2.size() << endl;
	cout << s2.length() << endl;

	string s3 = s2;
	//strcpy(s3, s2);
	s2.resize(10);
	cout << s2 << endl;
	s2.clear();
	cout << s2 << endl;
	cout << s3 << endl;

	cout << s3.find("Messaggio") << endl;
	cout << s3 <<" Find M:" << s3.find('M') << endl;
	cout << "Substring:" << s3.substr(0, s3.find('M')) << endl;

	string s4(10, 'g');
	cout << s4 << endl;
	
	cout << "Insert a message (1)" << endl;
	string message;
	cin >> message; //read till space
	cout << message << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush
	cout << "Insert a message (2)" << endl;
	getline(cin, message); //read all input
	cout << message << endl;

	cout << "Insert a message (3)" << endl;
	char c;	
	do 
	{
	  cin.get(c);
	  cout << c << endl;	 
	} while (c != '\n');
	
}