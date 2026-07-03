#include <iostream>
#include <type_traits>
#include <algorithm>

using namespace std;

// ============================================================================
// METODI DI COMPARAZIONE
// ============================================================================

/**
 * Compara due elementi. Grazie a 'if constexpr' (C++17), se T è un puntatore
 * viene dereferenziato automaticamente per confrontare i valori puntati.
 */
template<class T> 
int compare(const T& left, const T& right)
{
    if constexpr (is_pointer<T>::value)
    {
        if (*left < *right) return -1;
        if (*left > *right) return 1;
        return 0;
    }
    else
    {
        if (left < right) return -1;
        if (left > right) return 1;
        return 0;
    }
}

// ============================================================================
// FASE DI FUSIONE (MERGE)
// ============================================================================

/**
 * Unisce due sotto-array ordinati in un unico vettore ordinato.
 * Sotto-array sinistro: array[begin ... mid]
 * Sotto-array destro:   array[mid+1 ... end]
 */
template<class T> 
void merge(T array[], const size_t& begin, const size_t& mid, const size_t& end)
{
    size_t const leftSize = mid - begin + 1;
    size_t const rightSize = end - mid;

    // Allocazione degli array temporanei per salvare i dati correnti
    T* leftArray = new T[leftSize];
    T* rightArray = new T[rightSize];

    // Copia dei dati nei vettori temporanei
    for (size_t i = 0; i < leftSize; i++)    
        leftArray[i] = array[begin + i];
            
    for (size_t i = 0; i < rightSize; i++)    
        rightArray[i] = array[mid + 1 + i];       

    size_t leftIndex = 0;     // Indice per scorrere leftArray
    size_t rightIndex = 0;    // Indice per scorrere rightArray
    size_t mergedIndex = begin; // Indice per aggiornare l'array originale

    // Fusione dei due array basata sull'ordine stabilito da compare()
    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        if (compare(leftArray[leftIndex], rightArray[rightIndex]) <= 0)
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

    // Copia degli eventuali elementi rimanenti nel sotto-array sinistro
    while (leftIndex < leftSize)
    {
        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    // Copia degli eventuali elementi rimanenti nel sotto-array destro
    while (rightIndex < rightSize)
    {
        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }

    // Rilascio della memoria allocata dinamicamente
    delete[] leftArray;
    delete[] rightArray;
}

// ============================================================================
// ALGORITMI DI ORDINAMENTO (RECURSIVE & ITERATIVE)
// ============================================================================

/**
 * APPROCCIO TOP-DOWN (Ricorsivo)
 * Divide l'array a metà, si auto-invoca sulle due parti e infine le fonde.
 */
template<class T> 
void recursiveMergeSort(T array[], const size_t& begin, const size_t& end)
{
    if (begin >= end)
        return; 

    size_t mid = begin + (end - begin) / 2; // Previene overflow rispetto a (begin+end)/2
    
    recursiveMergeSort(array, begin, mid);       // Ordina la metà sinistra
    recursiveMergeSort(array, mid + 1, end);   // Ordina la metà destra
    merge(array, begin, mid, end);               // Fonde le due metà ordinate
}

// Interfaccia semplificata per la chiamata ricorsiva
template<class T> 
void recursiveMergeSort(T arr[], const size_t& end)
{
    if (end > 0)
        recursiveMergeSort(arr, 0, end - 1);
}

/**
 * APPROCCIO BOTTOM-UP (Iterativo)
 * Evita la ricorsione ordinando prima sotto-array di dimensione 1, poi 2, 4, 8...
 */
template<class T> 
void iterativeMergeSort(T arr[], const size_t& end)
{
    if (end <= 1) return;

    size_t curr_size;  
    size_t left_start;

    // curr_size varia: 1, 2, 4, 8, ...
    for (curr_size = 1; curr_size < end; curr_size = 2 * curr_size)
    {       
        // Identifica i blocchi adiacenti di dimensione 'curr_size' da fondere
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
    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int arr2[] = {38, 27, 43, 3, 9, 82, 10};

    size_t n = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Array originale:\n";
    for (size_t i = 0; i < n; i++)
        cout << arr1[i] << " ";
    cout << "\n\n";

    // Merge Sort ricorsivo
    recursiveMergeSort(arr1, n);

    cout << "Array ordinato (Merge Sort Ricorsivo):\n";
    for (size_t i = 0; i < n; i++)
        cout << arr1[i] << " ";
    cout << "\n\n";

    // Merge Sort iterativo
    iterativeMergeSort(arr2, n);

    cout << "Array ordinato (Merge Sort Iterativo):\n";
    for (size_t i = 0; i < n; i++)
        cout << arr2[i] << " ";
    cout << "\n";

    return 0;
}