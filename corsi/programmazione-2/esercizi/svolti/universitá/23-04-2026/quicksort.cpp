#include <iostream>
#include <fstream>

using namespace std;

template <class T>
size_t partition(T arr[], const size_t &begin, const size_t &end)
{
    size_t p = begin; // l'indice che deve scorrere fino a prima del pivot
    for (size_t i = begin; i < end; i++)
    {
        // core della partizione
        if (arr[i] <= arr[end]) // ricordiamoci che end é il pivot quindi l'ultimo elemento
        {
            swap(arr[i], arr[p]);
            p++;
        }
    }
    swap(arr[p], arr[end]);
    return p;
}

template <class T>
void quicksort(T arr[], const size_t &begin, const size_t &end)
{
    // devo scegliere il pivot
    if (begin <= end)
        return;
    size_t pivot_ind = partition(arr, begin, end);

    if (pivot_ind > begin)                    // si aggiunge per evitare le situazioni per cui l'indice negativo e avrebbe comportamento non definito poiché size_t puó leggere solo valori senza segno
        quicksort(arr, begin, pivot_ind - 1); // parte sinistra
    if (pivot_ind < end)
        quicksort(arr, pivot_ind + 1, end); // parte di destra
}

int main()
{
    int arr[5] = {7, 4, 2, 3, 1};
}
