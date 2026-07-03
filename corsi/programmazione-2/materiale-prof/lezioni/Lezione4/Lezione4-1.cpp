#include <iostream>
#include "../Lezione3/Lezione3-2/book.h"

using namespace std;



template<class T> int compare(const T& left, const T& right)
{
    if constexpr (is_pointer<T>::value)
    {
        if (*left < *right)
            return -1;
        else if (*left > *right)
            return 1;
        return 0;
    }
    else
    {
        if (left < right)
            return -1;
        else if (left > right)
            return 1;
        return 0;
    }
  
}

/*
* This compiles but does not work with built-in datatypes, only for user-defined datatypes.
* You can't change the behavior of operators for build-in datatypes. 
* In any case,  return *left <= *right would result in infinite recursion
* 
template<class T> bool operator<= (const T& left, const T& right)
{   
    if constexpr (is_pointer<T>::value)
        return *left <= *right;
    return left <= right;
}
*/

/* SFINAE (Substitution Failure Is Not An Error)
template<class T> typename std::enable_if<is_pointer<T>::value, int>::type
compare(const T& begin, const T& end)
{
  if (*begin < *end)
       return -1;
  else if (*begin > *end)
      return 1;
  return 0;
}


template<class T> typename std::enable_if<!is_pointer<T>::value, int>::type
compare(const T& begin, const T& end)
{
    if (begin < end)
        return -1;
    else if (begin > end)
        return 1;
    return 0;
}
*/

/* Overloading does not work because compare(const T&, const T&) always matches
template<class T> int compare(const T& begin, const T& end)
{
    if (begin < end)
        return -1;
    else if (begin > end)
        return 1;
    return 0;
}

template<class T> int compare(const T* begin, const T* end)
{
    return compare(*begin, *end);
}
*/


template<class T> void merge(T array[], const size_t& begin,  const size_t& mid, const size_t &end)
{
    size_t const leftSize = mid - begin + 1;
    size_t const rightSize = end - mid;

    // Temps arrays
    T* leftArray = new T[leftSize];
    T* rightArray = new T[rightSize];

    // Copy arrays
    for (int i = 0; i < leftSize; i++)    
        leftArray[i] = array[begin + i];
            
    for (int i = 0; i < rightSize; i++)    
        rightArray[i] = array[mid + 1 + i];       
    

    size_t leftIndex = 0, // Index of first subarray
           rightIndex = 0; // Index of second subarray
    size_t mergedIndex = begin; // Merged array start index

    //Merge in array[left..right]
    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        //leftArray[startLeft] <= rightArray[startRight]
        if (compare(leftArray[leftIndex], rightArray[rightIndex]) <=0 )
        {
            array[mergedIndex] = leftArray[leftIndex];            
            leftIndex++;
        }
        else
        {
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }
    // Copy elements of left, if any
    while (leftIndex < leftSize)
    {
        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }
    // Copy elements of right, if any
    while (rightIndex < rightSize)
    {
        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
    delete[] leftArray;
    delete[] rightArray;
}


template<class T> void recursiveMergeSort(T array[], const size_t& begin, const size_t& end)
{
    if (begin >= end)
        return; 
    size_t mid = begin + (end - begin) / 2; //safe with int, ok (start + end) / 2
    recursiveMergeSort(array, begin, mid);
    recursiveMergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

template<class T> void recursiveMergeSort(T arr[],  const size_t& end)
{
    recursiveMergeSort(arr, 0, end - 1);
}

template<class T> void iterativeMergeSort(T arr[],  const size_t& end)
{
    size_t curr_size;  
    size_t left_start;
    // Merge subarrays in bottom up manner.
    for (curr_size = 1; curr_size < end ; curr_size = 2 * curr_size)
    {       
        for (left_start = 0; left_start < end - 1; left_start += 2 * curr_size)
        {            
            size_t mid = min(left_start + curr_size - 1, end - 1);
            size_t right_end = min(left_start + 2 * curr_size - 1, end - 1);
            if (mid < right_end)
              merge(arr, left_start, mid, right_end);
        }
    }
}

int main()
{    
    int arr[] = {80, 12, 11, 13, 5, 6, 7};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);       
    //recursiveMergeSort(arr, arr_size);
    iterativeMergeSort(arr, arr_size);
    for (int i = 0; i < arr_size; i++)
        cout << arr[i] << " ";
    cout << endl;
    Book* b1= new Book("A", "B", 1998);
    Book* b2=  new Book("A2", "B2", 1978);
    Book* b3 = new Book("A", "B", 1999);
    Book* arrBook[] = {b1, b2, b3 };
    size_t bookSize = sizeof(arrBook) / sizeof(arrBook[0]);
    recursiveMergeSort(arrBook, bookSize);
    for (int i = 0; i < bookSize; i++)
        cout << *arrBook[i] << "; ";
    cout << endl;
    return 0;
}

