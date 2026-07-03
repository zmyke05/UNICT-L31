#include <iostream>

using namespace std;


//Lomuto partition // vs Hoare
template<class T> size_t partition(T arr[], const size_t& begin, const size_t& end)
{
    size_t pivotIndex = begin;
    for (size_t i = begin; i < end; i++)
    {
        if (arr[i] <= arr[end])
        {
            swap(arr[pivotIndex], arr[i]);
            pivotIndex++;
        }
    }
    swap(arr[pivotIndex], arr[end]);
    return pivotIndex;
}

template<class T> void quickSort(T arr[], const size_t& begin, const size_t& end)
{
    if (begin >= end)
        return;
    size_t PIndex = partition(arr, begin, end);
    if (PIndex > 0) //due to the use of size_t, PIndex cannot be negative
       quickSort(arr, begin, PIndex - 1);
    if (PIndex < end)
       quickSort(arr, PIndex + 1, end);
    
}

template<class T> void quickSort(T arr[], const size_t& size)
{
    quickSort(arr, 0, size - 1);
}


int main()
{

    int arr[] = { 32, 10, 7, 4, 8, 59, 9, 1, 5 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    quickSort<int>(arr, n);
    cout << "The sorted array is: ";
    for (int i = 0; i < n; i++)    
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}