#include <iostream>
#include <algorithm>

using namespace std;

// ============================================================================
// FASE DI PARTIZIONAMENTO (Schema di Lomuto)
// ============================================================================

/**
 * Prende l'ultimo elemento come perno (pivot), posiziona tutti gli elementi
 * minori o uguali al pivot alla sua sinistra e tutti gli elementi maggiori
 * alla sua destra. Ritorna l'indice finale del pivot.
 */
template<class T> 
size_t partition(T arr[], const size_t& begin, const size_t& end)
{
    // Il pivot scelto è l'ultimo elemento dell'intervallo corrente
    T pivot = arr[end];
    
    // pivotIndex tiene traccia della posizione in cui dovrà andare il pivot
    size_t pivotIndex = begin;

    for (size_t i = begin; i < end; i++)
    {
        // Se l'elemento corrente è minore o uguale al pivot
        if (arr[i] <= pivot)
        {
            // Viene spostato nella zona degli elementi più piccoli
            swap(arr[pivotIndex], arr[i]);
            pivotIndex++;
        }
    }
    
    // Colloca il pivot nella sua posizione corretta definitiva
    swap(arr[pivotIndex], arr[end]);
    
    return pivotIndex;
}

// ============================================================================
// ALGORITMO DI ORDINAMENTO (Quick Sort Ricorsivo)
// ============================================================================

/**
 * Divide l'array posizionando un pivot e si auto-invoca ricorsivamente 
 * sulla parte sinistra (elementi più piccoli) e sulla parte destra (elementi più grandi).
 */
template<class T> 
void quickSort(T arr[], const size_t& begin, const size_t& end)
{
    // Caso base: se l'intervallo ha 0 o 1 elemento, è già ordinato
    if (begin >= end)
        return;

    // Ottiene l'indice del pivot dopo il partizionamento
    size_t PIndex = partition(arr, begin, end);

    // Ordina ricorsivamente la porzione sinistra (se esiste)
    if (PIndex > 0) 
       quickSort(arr, begin, PIndex - 1);

    // Ordina ricorsivamente la porzione destra (se esiste)
    if (PIndex < end)
       quickSort(arr, PIndex + 1, end);
}

// Interfaccia semplificata che accetta l'array e la sua dimensione totale
template<class T> 
void quickSort(T arr[], const size_t& size)
{
    if (size > 1)
        quickSort(arr, 0, size - 1);
}

// ============================================================================
// MAIN DI ESEMPIO
// ============================================================================

int main() 
{
    int array[] = {7, 2, 9, 4, 8, 1, 6, 3, 0, 5};
    size_t n = 10;

    cout << "Array originale: ";
    for (size_t i = 0; i < n; i++) cout << array[i] << " ";
    cout << "\n\n";

    // DOPO LA PARTITION: Invece di chiamare solo partition, 
    // chiamiamo l'interfaccia di ordinamento completo
    quickSort(array, n);

    cout << "Array completamente ordinato con Quick Sort: ";
    for (size_t i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

    return 0;
}