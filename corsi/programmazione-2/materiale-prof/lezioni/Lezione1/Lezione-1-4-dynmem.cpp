#include <iostream>

using namespace std;

static void printArray(const int* arr, const size_t size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;
}

static void reinitArray(int* arr, const size_t size)
{
	for (int i = 0; i < size; i++)
		arr[i] += 1;

}

int main()
{
	size_t size = 10;
	int* arr = new int[size];  
	if (arr != NULL) 
		cout<< arr << endl;
	cout << sizeof(arr) << endl; //size of the pointer	
	//init
	for (int i = 0; i < size; i++)
		arr[i] = i;
	//print
	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;

	reinitArray(arr, size);
	printArray(arr,size);

    delete [] arr;		

    return 0;
}