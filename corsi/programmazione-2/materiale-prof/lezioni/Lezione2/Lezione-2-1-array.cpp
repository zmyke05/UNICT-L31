#include <iostream>

using namespace std;

int main()
{
	const size_t size=3;
	int arr[size] = {1,3,5};
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
		cout << arr[i] << endl;

	for (int i = 0; i < std::size(arr); i++)
		cout << arr[i] << endl;
	
	for (auto &i : arr)
		cout << i << endl;

	int matrix[2][4] = { { 1, 2, 3, 4 },  { 5, 6, 7, 8} };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}


	return 0;
}