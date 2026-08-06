#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

int main()
{
	time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	const tm* date= put_time(std::localtime(&now), "")._M_tmb;
	cout << date->tm_year + 1900<<endl;
	cout << date->tm_mon + 1 << endl;
	cout << date->tm_mday << endl;
	return 0;
}